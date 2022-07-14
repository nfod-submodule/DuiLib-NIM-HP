#pragma once

#include "public_define.h"

NS_UI_COMP_BEGIN

//-- 托盘图标事件处理接口
//****************************/
//-- class TrayIconDelegate
//****************************/
class TrayIconDelegate
{
public:
	virtual void OnLeftClick() = 0;
	virtual void OnLeftDoubleClick() = 0;
	virtual void OnRightClick() = 0;
	virtual void OnRightDoubleClick() = 0;
};

//-- 托盘图标管理类
//****************************/
//-- class TrayIcon
//****************************/
class TrayIcon
{
public:
	TrayIcon();
	virtual ~TrayIcon();

public:
	/**
	 * 初始托盘图标
	 * @param[in] pDelegate		托盘图标事件处理接口
	 * @param[in] lpClassName	窗口类名
	 * @param[in] lpWindowName	窗口名
	 * @param[in] lpStrRegWnd	被注册消息的名字
	 * @return void	无返回值
	**/
	void Init(
		TrayIconDelegate* pDelegate,
		LPCWSTR lpClassName,
		LPCWSTR lpWindowName,
		LPCWSTR lpStrRegWnd);

	/**
	 * 销毁托盘图标
	 * @return void	无返回值
	**/
	void Destroy();

	/**
	 * 设置托盘图标和提示文本
	 * @param[in] hIcon		托盘图标句柄
	 * @param[in] wstrTip	托盘提示文本
	 * @return TRUE=成功 FALSE=失败
	**/
	BOOL SetTrayIcon(
		HICON hIcon,
		const std::wstring& wstrTip);

private:
	/**
	 * 处理内部窗口消息
	 * @param[in] hWnd		窗口句柄
	 * @param[in] uMsg		消息值
	 * @param[in] wParam	附加参数
	 * @param[in] lParam	附加参数
	 * @return LRESULT 消息处理结果
	**/
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	void Proc(LPARAM lParam);

	/**
	 * 恢复托盘图标
	 * @return TRUE=成功 FALSE=失败
	**/
	BOOL RestoreTrayIcon();

	/**
	 * 修改托盘图标
	 * @param[in] uID		托盘ID
	 * @param[in] dwMsg		指定用于接收托盘消息的回调消息值
	 * @param[in] hIcon		托盘图标句柄
	 * @param[in] wstrTip	托盘提示文本
	 * @return TRUE=成功 FALSE=失败
	**/
	BOOL ModifyTrayIcon(
		UINT uID,
		DWORD dwMsg,
		HICON hIcon,
		const std::wstring& wstrTip);

private:
	HWND				m_hWnd;
	TrayIconDelegate*	m_pDelegate;
	UINT				m_uMsgID;
	BOOL				m_bAdded;
	HICON				m_hIcon;
	std::wstring		m_wstrTip;
};

NS_UI_COMP_END