#include "stdafx.h"
#include "Util.h"

//****************************/
//-- class Util
//****************************/
//////////////////////////////////////////////////////////////////////////

std::wstring Util::GetAppDir()
{
	static std::wstring wstrAppDir;
	if (wstrAppDir.empty())
	{
		WCHAR pBuf[MAX_PATH + 1] = { 0 };
		DWORD dwModLen = ::GetModuleFileNameW((HMODULE)ATL::_AtlBaseModule.GetModuleInstance(), pBuf, MAX_PATH + 1);
		if (dwModLen > 0 && dwModLen < MAX_PATH) {
			WCHAR* pDirEnd = wcsrchr(pBuf, L'\\');
			if (pDirEnd != NULL) {
				pBuf[pDirEnd + 1 - pBuf] = '\0';
				wstrAppDir = pBuf;
			}
		}
	}
	return wstrAppDir;
}
