#include <Windows.h>
void __cdecl DebugPrintA(__in_z __format_string LPCSTR lpcszFormat, ...);
BYTE* ScanAOB(BYTE* AOB, BYTE* memdump, unsigned long searchsize, int aobsize);
