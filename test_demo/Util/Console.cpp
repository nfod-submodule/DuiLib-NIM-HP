#include "stdafx.h"
#include "Console.h"
#include <ShlObj.h>
#include <locale.h>

namespace NS_Console {
	// ����̨�Ƿ��
	bool  m_bOpened = false;
	// ����̨���ļ���
	FILE* m_pStream = NULL;
	// ����̨���ھ��
	HWND m_hWnd = NULL;
}
using namespace NS_Console;

//****************************/
//-- class Console
//****************************/
//////////////////////////////////////////////////////////////////////////

bool Console::IsOpened()
{
	return m_bOpened;
}

bool Console::Open()
{
	if (m_bOpened) {
		return true;
	}

	BOOL bAlloced = AllocConsole();
	if (!bAlloced) {
		return false;
	}
	HWND hWnd = GetConsoleWindow();
	if (!hWnd) {
		FreeConsole();
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);
	BringWindowToTop(hWnd);
	HMENU hMenu = GetSystemMenu(hWnd, FALSE);
	if (hMenu) {
		DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	setlocale(LC_ALL, "chs");
	freopen_s(&m_pStream, "CONIN$",  "r+t", stdin);
	freopen_s(&m_pStream, "CONOUT$", "w+t", stdout);
	freopen_s(&m_pStream, "CONOUT$", "w+t", stderr);

	m_bOpened = true;
	m_hWnd = hWnd;
	return true;
}

void Console::Close()
{
	if (m_bOpened) {
		ShowWindow(m_hWnd, SW_HIDE);
		FreeConsole();
		fclose(m_pStream);
		m_bOpened = false;
		m_pStream = NULL;
		m_hWnd = NULL;
	}
}