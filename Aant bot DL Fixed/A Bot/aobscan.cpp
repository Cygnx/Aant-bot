#include "aobscan.h"
#include <strsafe.h>

void __cdecl DebugPrintA(__in_z __format_string LPCSTR lpcszFormat, ...) 
{ 
	va_list pArguments; 
	char szDebugBuffer[1024];
	va_start(pArguments, lpcszFormat); 
	if (SUCCEEDED(StringCchVPrintfA(szDebugBuffer, _countof(szDebugBuffer), lpcszFormat, pArguments))) 
		OutputDebugStringA(szDebugBuffer); 
	va_end(pArguments); 
} 

BYTE* ScanAOB(BYTE* AOB, BYTE* memdump, unsigned long searchsize, int aobsize)
{
	unsigned long a = 0, i = 0;
	for(i = 0; i < searchsize; i++)
	{      
		while(AOB[a] == '?')
		{
			a++;
			i++;
		}
		if(memdump[i] == AOB[a])
		{
			if(a == (aobsize - 1))
			{
				return &memdump[i-a];				
			}
			a++;
		}
		else a = 0;
	}
	return 0;
}
