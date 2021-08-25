#include "stdafx.h"
#include "Util.h"

//****************************/
//-- class Util
//****************************/
//////////////////////////////////////////////////////////////////////////

std::string Util::GetAppDirA()
{
	static std::string sAppDir;
	if (sAppDir.empty())
	{
		CHAR pBuf[MAX_PATH + 1] = { 0 };
		DWORD dwModLen = ::GetModuleFileNameA((HMODULE)ATL::_AtlBaseModule.GetModuleInstance(), pBuf, MAX_PATH + 1);
		if (dwModLen > 0 && dwModLen < MAX_PATH) {
			CHAR* pDirEnd = strrchr(pBuf, L'\\');
			if (pDirEnd != NULL) {
				pBuf[pDirEnd + 1 - pBuf] = '\0';
				sAppDir = pBuf;
			}
		}
	}
	return sAppDir;
}

std::wstring Util::GetAppDirW()
{
	static std::wstring sAppDir;
	if (sAppDir.empty())
	{
		WCHAR pBuf[MAX_PATH + 1] = { 0 };
		DWORD dwModLen = ::GetModuleFileNameW((HMODULE)ATL::_AtlBaseModule.GetModuleInstance(), pBuf, MAX_PATH + 1);
		if (dwModLen > 0 && dwModLen < MAX_PATH) {
			WCHAR* pDirEnd = wcsrchr(pBuf, L'\\');
			if (pDirEnd != NULL) {
				pBuf[pDirEnd + 1 - pBuf] = '\0';
				sAppDir = pBuf;
			}
		}
	}
	return sAppDir;
}
