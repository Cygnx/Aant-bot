#include "Headers.h"
#include "Keys.h"
int dwCurHP,dwCurMP,dwCurExp,dwMaxHP,dwMaxMP,dwMaxExp; 
char buf[5000];
BOOL MapleIsOpenedNow = FALSE;
//PostMessage Bypass
DWORD DLLFunc = (DWORD)GetProcAddress( LoadLibraryW(L"User32.dll" ), "PostMessageA" ) + 5; 
__declspec(naked) BOOL WINAPI PM(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) 
{ 
	__asm 
	{ 
		mov edi, edi
			push ebp
			mov ebp, esp
			jmp dword ptr ds:[DLLFunc]
	} 
}
__inline ULONG_PTR ReadPointer(ULONG_PTR* ulBase, INT nOffset)
{
	if ( !IsBadReadPtr((VOID*)ulBase, sizeof(ULONG_PTR)) )
		if ( !IsBadReadPtr((VOID*)((*(ULONG_PTR*)ulBase)+nOffset), sizeof(ULONG_PTR)) )
			return *(ULONG_PTR*)((*(ULONG_PTR*)ulBase)+nOffset);
	return 0;
}
void AtLoginScreen()
{
	BOOL Message_S = FALSE;
	while(*(DWORD*)LogInAddy != 3)
	{
		if(*(DWORD*)LogInAddy && !Message_S)
		{
			PM(FindWindow(0,Other_Connection_Window_Title),DLLMsg,MAKELPARAM(5,0),GlobalAddAtom("MapleStoryClass"));
			Message_S = TRUE;
			//return;
		}
		Sleep(100);
	}
	MapleIsOpenedNow = TRUE;
	return;
}
void AtChannel()
{
	BOOL WarnSeted = FALSE;
	while (!WarnSeted)
	{
		if(ReadPointer((ULONG_PTR*)(DWORD)(ChannelBase), (DWORD)(ChannelOffset)) > 0)
		{
			*(DWORD*)(*(DWORD*)CharWarnBase  + WarnMpOffset) = 20; 
			*(DWORD*)(*(DWORD*)CharWarnBase  + WarnHpOffset) = 20;
			WarnSeted = TRUE;
			return ;
		}
		Sleep(2);
	}
}
void DispPointers(HWND hWnd)
{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&AtLoginScreen, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)&AtChannel, hWnd, 0, 0);
	for(;;)
	{
		CheckInGame();
		SetDlgItemInt(hWnd,IDC_PCharX,ReadPointer((ULONG_PTR *)CharBase,CharXOffset),TRUE);
		SetDlgItemInt(hWnd,IDC_PCharY,ReadPointer((ULONG_PTR *)CharBase,CharYOffset),TRUE);
		SetDlgItemInt(hWnd,IDC_PMob,ReadPointer((ULONG_PTR *)MobBase,MobOffset),FALSE);
		SetDlgItemInt(hWnd,IDC_PPl,ReadPointer((ULONG_PTR *)PeopleBase,PeopleOffset),FALSE);
		SetDlgItemInt(hWnd,IDC_PItem,ReadPointer((ULONG_PTR *)ItemBase,ItemOffset),FALSE);
		SetDlgItemInt(hWnd,IDC_PAttack,ReadPointer((ULONG_PTR *)AttackBase,AttackOffset),FALSE);
		SetDlgItemInt(hWnd,IDC_PHp,ReadPointer((ULONG_PTR *)CharstatBase,HpOffset),FALSE);
		SetDlgItemInt(hWnd,IDC_PMp,ReadPointer((ULONG_PTR *)CharstatBase,MpOffset),FALSE);
		if(ReadPointer((ULONG_PTR*)(DWORD)(ChannelBase), (DWORD)(ChannelOffset)) > 0)
		{
			switch (ReadPointer((ULONG_PTR *)ServerBase,ServerOffset))
			{
			case 0:
				SetDlgItemText(DLG1,IDC_PServer,"Scania");
				break;
			case 1:
				SetDlgItemText(DLG1,IDC_PServer,"Bera");
				break;
			case 2:
				SetDlgItemText(DLG1,IDC_PServer,"Broa");
				break;
			case 3:
				SetDlgItemText(DLG1,IDC_PServer,"Windia");
				break;
			case 4:
				SetDlgItemText(DLG1,IDC_PServer,"Khaini");
				break;
			case 5:
				SetDlgItemText(DLG1,IDC_PServer,"Bellocan");
				break;
			case 6:
				SetDlgItemText(DLG1,IDC_PServer,"Mardia");
				break;
			case 7:
				SetDlgItemText(DLG1,IDC_PServer,"Kradia");
				break;
			case 8:
				SetDlgItemText(DLG1,IDC_PServer,"Yellonde");
				break;
			case 9:
				SetDlgItemText(DLG1,IDC_PServer,"Demethos");
				break;
			case 10:
				SetDlgItemText(DLG1,IDC_PServer,"Galicia");
				break;
			default:
				SetDlgItemInt(DLG1,IDC_PServer,ReadPointer((ULONG_PTR *)ServerBase,ServerOffset),FALSE);
				break;
			}
		}
		SetDlgItemInt(hWnd,IDC_PMap,ReadPointer((ULONG_PTR *)MapIDBase,MapIDOffset),FALSE);
		SetDlgItemInt(hWnd,IDC_PChannel,ReadPointer((ULONG_PTR *)ChannelBase,ChannelOffset) + 1,FALSE);
		if(IsDlgButtonChecked(DLG1, IDC_CStatBar) == BST_CHECKED)
		{
			float HpPercent = ((float)dwCurHP/dwMaxHP)*100;
			float MpPercent = ((float)dwCurMP/dwMaxMP)*100;
			float ExpPercent = ((float)dwCurExp/dwMaxExp)*100;
			SendDlgItemMessage(DLG1, IDC_PHpBar,PBM_SETPOS,HpPercent,0);
			SendDlgItemMessage(DLG1, IDC_PMpBar,PBM_SETPOS,MpPercent,0);
			SendDlgItemMessage(DLG1, IDC_PExpBar,PBM_SETPOS,ExpPercent,0);
			sprintf(buf,"%i",(int)(HpPercent + 0.5f));
			SetDlgItemText(hWnd,IDC_HpPer,buf);
			sprintf(buf,"%i",(int)(MpPercent + 0.5f));
			SetDlgItemText(hWnd,IDC_MpPer,buf);
			sprintf(buf,"%i",(int)(ExpPercent + 0.5f));
			SetDlgItemText(hWnd,IDC_ExpPer,buf);
		}
		Sleep(50);
	}
}
void AutoAttack()
{	
	while(IsDlgButtonChecked(DLG1, IDC_BAutoAttack) == BST_CHECKED)
	{
		char szString[MAX_PATH];
		//	GetWindowText(GetDlgItem(KEYCONFIG,IDC_CAttack_Key),szString,sizeof(szString));
		if(GetDlgItemInt(DLG2,IDC_EAutoAttackMob,NULL,FALSE) <= ReadPointer((ULONG_PTR *)MobBase,MobOffset)) // fix the 0 with mob pointer.
		{
			SendKey(0x011);
			//		TypeString(szString);
			Sleep(GetDlgItemInt(DLG2,IDC_EAutoAttackDelay,NULL,FALSE));
		}
		Sleep(1);
	}
}
void AutoSkill_1()
{
	while(IsDlgButtonChecked(DLG2, IDC_BAutoSkill_1) == BST_CHECKED)
	{
		if(IsDlgButtonChecked(DLG1, IDC_BAutoAttack) == BST_CHECKED)
		{
			SendKey(0x4F);
			Sleep(GetDlgItemInt(DLG2,IDC_EAutoAttackSkill_1,NULL,FALSE));
		}
		Sleep(1);
	}
}
void AutoSkill_2()
{
	while(IsDlgButtonChecked(DLG2, IDC_BAutoSkill_2) == BST_CHECKED)
	{
		if(IsDlgButtonChecked(DLG1, IDC_BAutoAttack) == BST_CHECKED)
		{
			SendKey(0x4A);
			Sleep(GetDlgItemInt(DLG2,IDC_EAutoAttackSkill_2,NULL,FALSE));
		}
		Sleep(1);
	}
}
void AutoLoot()
{
	while(IsDlgButtonChecked(DLG2, IDC_BAutoLoot) == BST_CHECKED)
	{
		if(IsDlgButtonChecked(DLG1, IDC_BAutoAttack) == BST_CHECKED)
		{
			SendKey(0x5A);
			Sleep(GetDlgItemInt(DLG2,IDC_EAutoAttackLoot,NULL,FALSE));
		}
		Sleep(1);
	}
}

void AutoJump()
{
	while(IsDlgButtonChecked(DLG2, IDC_BAutoJump) == BST_CHECKED)
	{
		if(IsDlgButtonChecked(DLG1, IDC_BAutoAttack) == BST_CHECKED)
		{
			SuspendThread(AutoAttackThread);
			for(int i = 0; i< 50;i++)
			{
				KeyDown(RIGHT); // go right
				Sleep(1);
			}
			KeyUp(RIGHT);
			for(int i = 0; i< 50;i++)
			{
				KeyDown(LEFT); // go right
				Sleep(1);
			}
			KeyUp(LEFT);
			ResumeThread(AutoAttackThread);
		}
		Sleep(GetDlgItemInt(DLG2,IDC_EAutoAttackJump,NULL,FALSE));
	}
}
void HealHp()
{
	while(IsDlgButtonChecked(DLG3, IDC_BHP) == BST_CHECKED)
	{
		if(IsDlgButtonChecked(DLG1, IDC_BAutoPot) == BST_CHECKED)
		{
			if(ReadPointer((ULONG_PTR*)CharstatBase,HpOffset) <= GetDlgItemInt(DLG3,IDC_EAutoPotHP,NULL,FALSE))
			{
				SendKey(0x39);
				Sleep(200);
			}
		}
		Sleep(1);
	}
}
void HealMp()
{
	while(IsDlgButtonChecked(DLG3, IDC_BMP) == BST_CHECKED)
	{
		if(IsDlgButtonChecked(DLG1, IDC_BAutoPot) == BST_CHECKED)
		{
			if(ReadPointer((ULONG_PTR*)CharstatBase,MpOffset) <= GetDlgItemInt(DLG3,IDC_EAutoPotMP,NULL,FALSE))
			{
				SendKey(0x30);
				Sleep(200);
			}
		}
		Sleep(1);
	}
}
void AutoChat()
{	

}
void AutoClick()
{
	
}
void CCFUNC()
{
	
}
void CcNow()
{
	
}
void AutoCc_People()
{	

}
void AutoCc_Attack()
{	

}
void AutoCc_Delay()
{	
}
void UnlimitedAttack_ItemUA()
{
	
}
void UnlimitedAttack_MoveUA()
{
}
void TypeString(__in_z LPCTSTR lpcszMessage) // credits to Irwin
{
	
}
void SendKey(UINT uCode)
{
	HWND MSHWND = FindWindow ("MapleStoryClass",0);
	PM(MSHWND, WM_KEYDOWN, uCode, (MapVirtualKey(uCode, 0) << 16) + 1);
	PM(MSHWND, WM_KEYUP, uCode, NULL);
}
//  && ReadPointer((ULONG_PTR *)CharBase,CharYOffset) && ReadPointer((ULONG_PTR *)MapIDBase,MapIDOffset) && ReadPointer((ULONG_PTR *)ServerBase,ServerOffset) && ReadPointer((ULONG_PTR *)ChannelBase,ChannelBase) 
void AutoLogin()
{
	
}
DWORD DecrypterCall = DecrypterCallAddy;
BOOL StatHook()
{
	return false;
}
char StatHookClean[9];
void Stat()
{

}
char TubiClean[2];
void SuperTubi()
{
	
}
int MissCount = 0;
DWORD SMGOrigJump = SevenMissGModeAddy_2;
DWORD SevenMissCleanRtn = SevenMissGModeAddy + 6;
BOOL  SevenMissGodModeHook()
{
	return false;
}
char SevenMissClean[6];
void SevenMissGodMode()
{

}
int MobX;
int MobY;
DWORD Dem_Item = CharBase;
DWORD Dem_Item_X = CharXOffset;
DWORD Dem_Item_Y = CharYOffset;
BOOL DemVacHook()
{
	return false;
}
char DemVacClean[12];
void DemVac()
{

}
void WaitAndGet(LPCTSTR Section,HWND hWnd,int Ctrl)
{
	//	Sleep(20);
	int sel;
	char sel_char[MAX_PATH];
	sel = SendDlgItemMessage(hWnd,Ctrl,CB_GETCURSEL,0,0);
	sprintf(sel_char,"%i",sel);
	sprintf(buf,"%i",Ctrl);
	WritePrivateProfileString(Section,buf,sel_char,"ABotSettings.ini");
}
void SaveEditSettingsToIni(LPCTSTR Section,HWND hWnd,int DLGITEM)
{
	char My_Key[MAX_PATH];
	sprintf(My_Key,"%i",DLGITEM);
	GetWindowText(GetDlgItem(hWnd,DLGITEM),buf,MAX_PATH);
	WritePrivateProfileString(Section,My_Key,buf,"ABotSettings.ini");
}
void SaveCheckSettingsToIni(LPCTSTR Section,HWND hWnd,int DLGITEM)
{
	char My_Key[MAX_PATH];
	sprintf(My_Key,"%i",DLGITEM);
	if(IsDlgButtonChecked(hWnd, DLGITEM) == BST_CHECKED)
	{
		WritePrivateProfileString(Section,My_Key,"1","ABotSettings.ini");
	}
	else
	{
		WritePrivateProfileString(Section,My_Key,"0","ABotSettings.ini");
	}
	Sleep(1);
}
void LoadSettingsFromIni(LPCTSTR Section,HWND hWnd,int DLGITEM)
{
	char My_Key[MAX_PATH];
	sprintf(My_Key,"%i",DLGITEM);
	GetPrivateProfileString(Section,My_Key,0,buf,sizeof(buf),"ABotSettings.ini");
	SetWindowText(GetDlgItem(hWnd,DLGITEM),buf);
	Sleep(1);
}
BOOL CheckIntSectionFromIni(LPCTSTR Section,int DLGITEM)
{
	// FALSE = Nothing Found . TRUE = Found
	char My_Key[MAX_PATH];
	sprintf(My_Key,"%i",DLGITEM);
	return GetPrivateProfileInt(Section,My_Key,0,"ABotSettings.ini");
}
BOOL LoadCheckSettingsFromIni(LPCTSTR Section,HWND hWnd,int DLGITEM)
{
	HANDLE MyThread;
	char My_Key[MAX_PATH];
	sprintf(My_Key,"%i",DLGITEM);
	int iValue = GetPrivateProfileInt(Section,My_Key,0,"ABotSettings.ini");
	if(iValue == 1)
	{
		CheckDlgButton(hWnd,DLGITEM,BST_CHECKED);
		SendMessage(hWnd, WM_COMMAND, MAKELONG(DLGITEM, BN_CLICKED), (LPARAM)GetDlgItem(hWnd,DLGITEM));
		return true;
	}
	else return false;
	Sleep(1);
}
void SuspendAll() 
{
	//SuspendThread(AutoAttackThread);
	//SuspendThread(AutoJumpThread);
	//SuspendThread(AutoLootThread);
	//SuspendThread(AutoSkillThread_1);
	//SuspendThread(AutoSkillThread_2);
	OutputDebugString("Suspending All");
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CAutoAttack_Off) == BST_CHECKED)
	{
		OutputDebugString("TRUE");
		SuspendThread(AutoAttackThread);
		SuspendThread(AutoJumpThread);
		SuspendThread(AutoLootThread);
		SuspendThread(AutoSkillThread_1);
		SuspendThread(AutoSkillThread_2);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CAutoPot_Off) == BST_CHECKED)
	{
		SuspendThread(AutoPot_HPThread);
		SuspendThread(AutoPot_MPThread);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CUnlimitedAttack_Off) == BST_CHECKED)
	{
		SuspendThread(MoveUAThread);
		SuspendThread(ItemUAThread);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CAutoChat_Off) == BST_CHECKED)
	{
		SuspendThread(AutoChatThread);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CAutoClick_Off) == BST_CHECKED)
	{
		SuspendThread(AutoClickThread);
	}
	//	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CAutoLogin_OFF) == BST_CHECKED)
	//	{
	//	SuspendThread(AutoLoginThread);
	//	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CGodMode_OFF) == BST_CHECKED)
	{
		SuspendThread(GodModeThread);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CTubi_OFF) == BST_CHECKED)
	{
		SuspendThread(TubiThread);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CVAC_OFF) == BST_CHECKED)
	{
		SuspendThread(DemVacThread);
	}
	if(IsDlgButtonChecked(DLGSETTINGS, IDC_CAutoCC_Off) == BST_CHECKED)
	{
		SuspendThread(AutoCCThread_PPL);
		SuspendThread(AutoCCThread_ATT);
		SuspendThread(AutoCCThread_Delay);
	}
}
void ResumeAll()
{
	ResumeThread(AutoAttackThread);
	ResumeThread(AutoPot_HPThread);
	ResumeThread(AutoPot_MPThread);
	ResumeThread(MoveUAThread);
	ResumeThread(ItemUAThread);
	ResumeThread(AutoChatThread);
	ResumeThread(AutoClickThread);
	ResumeThread(AutoLoginThread);
	ResumeThread(GodModeThread);
	ResumeThread(TubiThread);
	ResumeThread(DemVacThread);
	ResumeThread(AutoJumpThread);
	ResumeThread(AutoLootThread);
	ResumeThread(AutoSkillThread_1);
	ResumeThread(AutoSkillThread_2);
	ResumeThread(AutoCCThread_PPL);
	ResumeThread(AutoCCThread_ATT);
	ResumeThread(AutoCCThread_Delay);
}
void PlayerDetection()
{
	
}
void WalkTo(int x,int y)
{
	//Right UA
	while(signed(ReadPointer((ULONG_PTR*)CharBase, CharXOffset)) < signed int(x))
	{
		{
			KeyDown(0x27); // go right
			Sleep(1);
		}
		KeyUp(0x27);
		while(signed(ReadPointer((ULONG_PTR*)CharBase, CharXOffset)) > signed int(x))
		{
			KeyDown(0x25); // go left
			Sleep(1);
		}
		KeyUp(0x25);
	}
}
DWORD CSReturnx = 0x008C3D29 + 5;
DWORD CSReturny = 0x008C3D8E + 5;
BOOL CSVACXHook()
{
	return false;
}
BOOL CSVACYHook()
{
	return false;
}
char CSVACXClean[12];
char CSVACYClean[12];
void CSVAC()
{
	
}
BOOL CheckInGame()
{
	if(!ReadPointer((ULONG_PTR *)MapIDBase,MapIDOffset))
	{
		SuspendThread(AutoAttackThread);
		SuspendThread(AutoJumpThread);
		SuspendThread(AutoLootThread);
		SuspendThread(AutoSkillThread_1);
		SuspendThread(AutoSkillThread_2);
		SuspendThread(AutoPot_HPThread);
		SuspendThread(AutoPot_MPThread);
		SuspendThread(MoveUAThread);
		SuspendThread(ItemUAThread);
		SuspendThread(AutoChatThread);
		SuspendThread(AutoClickThread);
		SuspendThread(GodModeThread);
		SuspendThread(TubiThread);
		SuspendThread(DemVacThread);
		SuspendThread(AutoCCThread_PPL);
		SuspendThread(AutoCCThread_ATT);
		SuspendThread(AutoCCThread_Delay);
	}
	else
	{
		ResumeAll();
	}
	return TRUE;
	Sleep(1);
}
void Key_Config_Keys(HWND hWnd)
{
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"A");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"B");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"C");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"D");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"E");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"F");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"G");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"H");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"I");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"J");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"K");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"L");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"M");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"N");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"O");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"P");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Q");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"R");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"S");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"T");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"U");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"V");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"W");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"X");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Y");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Z");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"1");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"2");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"3");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"4");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"5");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"6");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"7");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"8");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"9");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"0");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Ctrl");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Alt");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Shift");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Esc");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Space");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Ins");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Delete");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Home");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Page Up");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Page Down");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"End");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Enter");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"Backspace");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"+");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"-");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)">");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"<");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"/");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"\"");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"[");
	SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)"]");
}