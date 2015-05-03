#include <Windows.h>
#define _CRT_SECURE_NO_WARNINGS 1

static const int KEYDOWN = WM_USER + 0;
static const int KEYUP = WM_USER + 1;
static const int KEYPRESS = WM_USER + 2;

void KeyDown (UINT Key);
void KeyUp (UINT Key);
void SendKeyA (UINT Key, int times);


void KeyDown (UINT Key)
{
	INPUT Input;
	ZeroMemory(&Input, sizeof(Input));
	Input.type = INPUT_KEYBOARD; // keyboard
	Input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
	Input.ki.wVk = Key; // Virtual Key
	SendInput(1, &Input, sizeof(INPUT)); 
}

void KeyUp (UINT Key)
{
	INPUT Input;
	ZeroMemory(&Input, sizeof(Input));
	Input.type = INPUT_KEYBOARD; // keyboard
	Input.ki.dwFlags = KEYEVENTF_KEYUP;
	Input.ki.wVk = Key; // Virtual Key
	PressingKey = FALSE;
	SendInput(1, &Input, sizeof(INPUT)); 
}

void SendKeyA (UINT Key, int times)
{
	for (int i=0;i<times;i++)
	{
		INPUT Input;
		ZeroMemory(&Input, sizeof(Input));
		Input.type = INPUT_KEYBOARD; // keyboard
		Input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
		Input.ki.wVk = Key; // Virtual Key
		SendInput(1, &Input, sizeof(INPUT)); 

		Input.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &Input, sizeof(INPUT)); 
	}
}