#include "Headers.h"
HMODULE MAINMODULE;
HWND DLG1,DLG2,DLG3,DLG4,DLG5,DLG6,DLG7,DLG8,DLG9,DLGVAC,DLGSETTINGS,KEYCONFIG;
HANDLE AutoAttackThread,AutoPot_HPThread,AutoPot_MPThread,MoveUAThread,ItemUAThread,AutoChatThread,AutoClickThread,AutoLoginThread,GodModeThread,TubiThread,DemVacThread,AutoJumpThread,AutoLootThread,AutoSkillThread_1,AutoSkillThread_2,AutoCCThread_PPL,AutoCCThread_ATT,AutoCCThread_Delay;
HBRUSH g_hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
BOOL PressingKey = FALSE;
DWORD OldProtection = 0;
DWORD oldp2 = 0;
PDWORD oldprot2 = &oldp2;
char Other_Connection_Window_Title[MAX_PATH];

DWORD VPX = (DWORD)GetProcAddress(LoadLibrary("KERNEL32.DLL"), "VirtualProtectEx")+5;
__declspec(naked) BOOL WINAPI FixMemEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
{
	_asm
	{
		mov edi,edi
			push ebp
			mov ebp,esp
			jmp[VPX]
	}
} 
void FixMem(DWORD addy)
{
	FixMemEx(GetCurrentProcess(), (void*)addy, 0x1000, PAGE_EXECUTE_READWRITE, (DWORD*)oldprot2);
}
void SetTopLeft(HWND DlghWnd)
{
	RECT MainDlgRect;
	RECT DlgRect;
	GetWindowRect(DLG1,&MainDlgRect);
	GetWindowRect(DlghWnd,&DlgRect);
	int length = DlgRect.right - DlgRect.left;
	SetWindowPos(DlghWnd,HWND_TOPMOST,MainDlgRect.left - length - 13,MainDlgRect.top,NULL,NULL,SWP_NOSIZE | SWP_NOZORDER);
}
void SetTopRight(HWND DlghWnd)
{
	RECT MainDlgRect;
	RECT DlgRect;
	GetWindowRect(DLG1,&MainDlgRect);
	GetWindowRect(DlghWnd,&DlgRect);
	SetWindowPos(DlghWnd,HWND_TOPMOST,MainDlgRect.right+10,MainDlgRect.top,NULL,NULL,SWP_NOSIZE | SWP_NOZORDER);
}

DWORD WINAPI MainWin( HMODULE hModule){
	MAINMODULE = hModule;
	Sleep(500);
	DialogBox(hModule, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)Dlg1Proc);   //Creats the dialog
	ExitThread(0);
	return 0;
}
/*------------------------------------- Main Dialog -------------------------------------*/
BOOL STATLOADED = FALSE;
char MyWindowTitle[MAX_PATH];
BOOL CALLBACK Dlg1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(uMsg)
	{
	case EXEMsg:
		switch(LOWORD(wParam))
		{
		case 1://Saves Window title for later use.
			GlobalGetAtomName((ATOM)HIWORD(wParam),Other_Connection_Window_Title,sizeof(Other_Connection_Window_Title));
			break;
		case 2:// Set Pos
			SetWindowPos(hWnd,HWND_NOTOPMOST,HIWORD(wParam),lParam,0,0,SWP_NOSIZE);
			break;
		}
		break;
	case WM_INITDIALOG:	
		DLG1 = hWnd;
		GetWindowText(hWnd,MyWindowTitle,sizeof(MyWindowTitle));
		PM(FindWindow(0,"Aant Bot"),DllLoaded,GlobalAddAtom(MyWindowTitle),0);
		//----------------------------------------------------------------------------------

		RegisterHotKey(hWnd,IDC_BAutoAttack,0,VK_F1);
	
		DLG2 = CreateDialog(MAINMODULE, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)Dlg2Proc);
		ShowWindow(DLG2, SW_SHOW);
		
		break;
	case WM_HOTKEY:
		if(IsDlgButtonChecked(DLGSETTINGS, IDC_DisableHotkeys) == BST_CHECKED)
		{
			return 0;
		}
		switch(wParam)
		{
		case IDC_BAutoAttack:
			if(IsDlgButtonChecked(hWnd, IDC_BAutoAttack) == BST_UNCHECKED)
			{
				CheckDlgButton(hWnd,IDC_BAutoAttack,BST_CHECKED);
				AutoAttackThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoAttack, NULL, 0, NULL);
			}
			else
			{
				CheckDlgButton(hWnd,IDC_BAutoAttack,BST_UNCHECKED);
			}
			break;
		}
		SaveCheckSettingsToIni("Main",hWnd,wParam);
		break;
	case WM_COMMAND:
		switch(HIWORD(wParam))
		{
		case BN_CLICKED:
			SaveCheckSettingsToIni("Main",hWnd,LOWORD(wParam));
			switch(LOWORD(wParam))
			{
			case IDC_SAutoAttack:
				if(ShowWindow(DLG2,0) == NULL)
				{
					SetTopLeft(DLG2);
					ShowWindow(DLG2, SW_SHOW);
				}
				if (!IsWindow(DLG2))
				{
					DLG2 = CreateDialog(MAINMODULE, MAKEINTRESOURCE(IDD_DIALOG2), NULL, (DLGPROC)Dlg2Proc);
					ShowWindow(DLG2, SW_SHOW);
				}
				break;
			case IDC_BAutoAttack:
				AutoAttackThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoAttack, NULL, 0, NULL);
				break;
			}
			break;
		}
		break;
	case WM_PAINT:
		if(STATLOADED == FALSE)
		{
			ShowWindow(hWnd,SW_HIDE);
			LoadCheckSettingsFromIni("Main",hWnd,IDC_CStatBar);
			LoadCheckSettingsFromIni("Main",hWnd,IDC_BAutoAttack);
			STATLOADED = TRUE;
		}
		SendDlgItemMessage(DLG1, IDC_PHpBar,PBM_SETBARCOLOR,0,(COLORREF)RGB(255,0,0));
		SendDlgItemMessage(DLG1, IDC_PMpBar,PBM_SETBARCOLOR,0,(COLORREF)RGB(0,0,255));
		SendDlgItemMessage(DLG1, IDC_PExpBar,PBM_SETBARCOLOR,0,(COLORREF)RGB(255,255,0));
		break;
	case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
		break;
	case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)g_hbrBackground;
		}
		break;
	case WM_CLOSE:
		EndDialog((HWND)hWnd, 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return 0;
}
/*------------------------------------- Auto Attack -------------------------------------*/
BOOL AALoaded = FALSE;
BOOL CALLBACK Dlg2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch(uMsg)
	{
	case WM_INITDIALOG:	
		DLG2 = hWnd;
		SetTopLeft(hWnd);
		if(!CheckIntSectionFromIni("Auto Attack",IDC_EAutoAttackDelay))
		{
			SetDlgItemInt(hWnd,IDC_EAutoAttackDelay,100,FALSE);
		}
		break;
	case WM_HOTKEY:
		break;
	case WM_COMMAND:
		switch(HIWORD(wParam))
		{
		case EN_CHANGE:
			SaveEditSettingsToIni("Auto Attack",hWnd,LOWORD(wParam));
			break;
		case BN_CLICKED:
			SaveCheckSettingsToIni("Auto Attack",hWnd,LOWORD(wParam));
			switch(LOWORD(wParam))
			{
			case IDC_BAutoSkill_1:
				AutoSkillThread_1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoSkill_1, NULL, 0, NULL);
				break;
			case IDC_BAutoSkill_2:
				AutoSkillThread_2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoSkill_2, NULL, 0, NULL);
				break;
			case IDC_BAutoLoot:
				AutoLootThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoLoot, NULL, 0, NULL);
				break;
			case IDC_BAutoJump:
				AutoJumpThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AutoJump, NULL, 0, NULL);
				break;
			}
		}
		break;
	case WM_PAINT:
		if(AALoaded == FALSE)
		{
			ShowWindow(hWnd,SW_HIDE);
			LoadSettingsFromIni("Auto Attack",hWnd,IDC_EAutoAttackMob);
			LoadSettingsFromIni("Auto Attack",hWnd,IDC_EAutoAttackDelay);
			LoadSettingsFromIni("Auto Attack",hWnd,IDC_EAutoAttackSkill_1);
			LoadSettingsFromIni("Auto Attack",hWnd,IDC_EAutoAttackSkill_2);
			LoadSettingsFromIni("Auto Attack",hWnd,IDC_EAutoAttackLoot);
			LoadSettingsFromIni("Auto Attack",hWnd,IDC_EAutoAttackJump);
			LoadCheckSettingsFromIni("Auto Attack",hWnd,IDC_BAutoSkill_1);
			LoadCheckSettingsFromIni("Auto Attack",hWnd,IDC_BAutoSkill_2);
			LoadCheckSettingsFromIni("Auto Attack",hWnd,IDC_BAutoJump);
			LoadCheckSettingsFromIni("Auto Attack",hWnd,IDC_BAutoLoot);
			AALoaded = TRUE;
		}
		break;
	case WM_CTLCOLORDLG:
		return (LONG)g_hbrBackground;
		break;
	case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			SetTextColor(hdcStatic, RGB(255, 255, 255));
			SetBkMode(hdcStatic, TRANSPARENT);
			return (LONG)g_hbrBackground;
		}
		break;
	case WM_CLOSE:
		EndDialog((HWND)hWnd, 0);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return 0;
}
/*------------------------------------- Auto Pot -------------------------------------*/
BOOL APLoaded = FALSE;
BOOL CALLBACK Dlg3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
/*------------------------------------- Unlimited Att -------------------------------------*/
BOOL UALoaded = FALSE;
BOOL CALLBACK Dlg4Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	return 0;
}
/*------------------------------------- Auto CC -------------------------------------*/
BOOL AccLoaded = FALSE;
BOOL CALLBACK Dlg5Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
/*------------------------------------- Auto Chat -------------------------------------*/
BOOL ACLoaded = FALSE;
BOOL CALLBACK Dlg6Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
/*------------------------------------- Auto Click -------------------------------------*/
BOOL AclLoaded = FALSE;
BOOL CALLBACK Dlg7Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
/*------------------------------------- Item Filter -------------------------------------*/
BOOL ITFLoaded = FALSE;
BOOL CALLBACK Dlg8Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
/*------------------------------------- Auto Login -------------------------------------*/
BOOL PAINTED = FALSE;
BOOL ATLLoaded = FALSE;
BOOL CALLBACK Dlg9Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

/*------------------------------------- Vac Settings -------------------------------------*/
BOOL VacLoaded = FALSE;
BOOL CALLBACK DlgVac(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
/*------------------------------------- Settings -------------------------------------*/
BOOL SetLoaded =  FALSE;
BOOL CALLBACK DlgSetting(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

/*------------------------------------- Key Config -------------------------------------*/
BOOL KeyConfigLoaded =  FALSE;
BOOL CALLBACK KeyConfig(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return 0;
}
