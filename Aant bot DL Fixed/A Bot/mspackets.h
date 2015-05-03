#include <stdio.h>
#include <Windows.h>
extern BOOL MapleIsOpenedNow;
struct PACKET {
	DWORD Null;
	LPVOID lpData;
	DWORD nSize;
	DWORD Null2;
};
/* Define your own packet structs here as you reverse ms packet structures */
struct CCPacket
{
  byte w26Header[2];
   byte ZeroBaseChannel[1];
   byte CC1[4];
};
struct mobTelePacket
{
	WORD w37Header;
	byte dwMobId[4];  // DWORD made sizeof(mobTelePacket) = 8 for some reason
};

typedef DWORD (__stdcall *SENDPACKET)(PACKET *Buffer);

char* atohx(char* dst, const char * src);
void WINAPI msSendPacketA(__in LPCSTR lpPacketStr);
void WINAPI msSendBuffer(__inout LPVOID lpPacket, __in SIZE_T cb);
BOOL WINAPI IsPacketSniffed();
void eraseAllBlanks(char *src);
void SendP(char *pack);
int GetLen(char* MyString);
char *StrToHex(char *str);