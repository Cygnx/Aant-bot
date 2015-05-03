#include <stdio.h>
#include <Windows.h>
#include "mspackets.h"
#include "aobscan.h"
#include "Addresses.h"
SENDPACKET SendPacket;

char* Buffer = NULL;
//----------------------------------------------------------
//byte SendAob[30] = {0xB8, '?', '?', '?', 0, 0xE8, '?', '?', '?', 0, 0x51, 0x56, 0x57, 0x8B, 0xF9, 0x8D, 0x77, '?', 0x8B, 0xCE, 0x89, '?', '?', 0xE8, '?', '?', '?', '?', 0x8B, 0x47 };
//byte ClassAob[28] = { 0x8b, 0x0d, '?', '?', '?', '?', 0x83, 0x65, '?', '?', 0x8d, 0x45, '?', 0x50, 0xe8, '?', '?', '?', '?', 0x83, 0x4d, '?', '?', 0x8d, 0x4d, '?', 0xc7, 0x46 };
//-------------Defining Some Addys and Other Stuff----------

//DWORD SendAddy = (DWORD)ScanAOB(SendAob, (byte*)0x00400000, 0x600000, 30);//0x004866AC;	//B8 ? ? ? 00 E8 ? ? ? 00 51 56 57 8B F9 8D 77 ? 8B CE 89 ? ? E8 ? ? ? ? 8B 47 ?
//DWORD ClassAddy = (DWORD)ScanAOB(ClassAob, (byte*)0x00400000, 0x600000, 28);//0x0046B20D;	//8b 0d ? ? ? ? 83 65 ? ? 8d 45 ? 50 e8 ? ? ? ? 83 4d ? ? 8d 4d ? c7 46
DWORD SendAddy = SendAddyAddy;
DWORD ClassAddy = ClassAddyAddy;
DWORD PESendJmp = SendAddy + 5;
DWORD PEClass = *(DWORD*)&Buffer[ClassAddy+2];

//----------------------------------------------------------

inline char* atohx(char* dst, const char * src)
{	

}
void eraseAllBlanks(char *src)
{

}
//-------------Sending Packet Functions --------------------
void WINAPI msSendPacketA(__in LPCSTR lpPacketStr)
{

}

void WINAPI msSendBuffer(__inout LPVOID lpPacket, __in SIZE_T cb)
{

}

BOOL WINAPI IsPacketSniffed()
{

}
void SendP(char *pack)
{

}
char *StrToHex(char *str)
{
} 
int GetLen(char* MyString)
{

}