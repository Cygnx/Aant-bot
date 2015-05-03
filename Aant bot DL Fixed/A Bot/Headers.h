#include <windows.h>
#include "resource.h"
#include "Addresses.h"
#include "mspackets.h"
#include "aobscan.h"
#include <commctrl.h>
#include <stdio.h>
#pragma comment(lib, "comctl32.lib")
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define _CRT_SECURE_NO_WARNINGS 1
#define JMP(frm, to) (int)(((int)to - (int)frm) - 5); 
//#include "Keys.h"
#ifndef resource_H
#define resource_H
DWORD WINAPI MainWin( HMODULE hModule);
extern char buf[5000];
extern BOOL PressingKey;
extern BOOL CALLBACK Dlg1Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg2Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg3Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg4Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg5Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg6Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg7Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg8Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK Dlg9Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK DlgVac(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK DlgSetting(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CALLBACK KeyConfig(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern BOOL CheckInGame();
extern void Key_Config_Keys(HWND hWnd);
extern void DispPointers(HWND hWnd);
extern void AtChannel();
extern void AtLoginScreen();
extern void SetTopLeft(HWND DlghWnd);
extern void SendKey(UINT uCode);
extern void TypeString(__in_z LPCTSTR lpcszMessage);
extern void AutoAttack();
extern void AutoSkill_1();
extern void AutoSkill_2();
extern void AutoLoot();
extern void AutoJump();
extern void HealHp();
extern void HealMp();
extern void AutoChat();
extern void AutoClick();
extern void CcNow();
extern void AutoCc_People();
extern void AutoCc_Attack();
extern void AutoCc_Delay();
extern void UnlimitedAttack();
extern void UnlimitedAttack_MoveUA();
extern void UnlimitedAttack_ItemUA();
extern void CCFUNC();
extern void AutoLogin();
extern void SuperTubi();
extern void DemVac();
extern void CSVAC();
extern void SuspendAll();
extern void ResumeAll();
extern void PlayerDetection();
extern BOOL StatHook();
extern void Stat();
void SevenMissGodMode();
extern int dwCurHP,dwCurMP,dwCurExp,dwMaxHP,dwMaxMP,dwMaxExp; 
extern float HpPercent,MpPercent,ExpPercent;
extern void FixMem(DWORD addy);
extern void WaitAndGet(LPCTSTR Section,HWND hWnd,int Ctrl);
extern void SaveEditSettingsToIni(LPCTSTR Section,HWND hWnd,int DLGITEM);
extern void LoadSettingsFromIni(LPCTSTR Section,HWND hWnd,int DLGITEM);
extern void SaveCheckSettingsToIni(LPCTSTR Section,HWND hWnd,int DLGITEM);
extern BOOL CheckIntSectionFromIni(LPCTSTR Section,int DLGITEM);
extern BOOL LoadCheckSettingsFromIni(LPCTSTR Section,HWND hWnd,int DLGITEM);
//extern void LoadCheckSettingsFromIni(LPCTSTR Section,HWND hWnd,int DLGITEM,void* Func);
extern HANDLE AutoAttackThread;
extern HANDLE AutoPot_HPThread;
extern HANDLE AutoPot_MPThread;
extern HANDLE MoveUAThread;
extern HANDLE ItemUAThread;
extern HANDLE AutoChatThread;
extern HANDLE AutoClickThread;
extern HANDLE AutoLoginThread;
extern HANDLE GodModeThread;
extern HANDLE TubiThread;
extern HANDLE DemVacThread;
extern HANDLE AutoJumpThread;
extern HANDLE AutoLootThread;
extern HANDLE AutoSkillThread_1;
extern HANDLE AutoSkillThread_2;
extern HANDLE AutoCCThread_PPL;
extern HANDLE AutoCCThread_ATT;
extern HANDLE AutoCCThread_Delay;
extern HMODULE MAINMODULE;
extern HWND DLG1;
extern HWND DLG2;
extern HWND DLG3;
extern HWND DLG4;
extern HWND DLG5;
extern HWND DLG6;
extern HWND DLG7;
extern HWND DLG8;
extern HWND DLG8;
extern HWND DLG9;
extern HWND DLGVAC;
extern HWND DLGSETTINGS;
extern HWND KEYCONFIG;
extern BOOL PressingKey;
BOOL WINAPI PM(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
__inline ULONG_PTR ReadPointer(ULONG_PTR* ulBase, INT nOffset);
//
extern char Other_Connection_Window_Title[MAX_PATH];
//
const int DllLoaded = WM_USER + 1;
const int EXEMsg = WM_USER + 2;
const int DLLMsg = WM_USER + 3;
#endif