#pragma once

#include "public_define.h"

NS_UI_COMP_BEGIN

//-- 窗口基类
//****************************/
//-- class WindowEx
//****************************/
class WindowEx : public ui::WindowImplBase
{
protected:
	//-- 控制标记（CtrlFL）
	static CONST ULONG FL_NULL		= 0;
	static CONST ULONG FL_QUIT		= 1 << 0;	// 关闭窗口时退出程序
	static CONST ULONG FL_ESC_CLOSE = 1 << 1;	// 按ESC键关闭窗口
	static CONST ULONG FL_N_LAYERED	= 1 << 2;	// 非分层窗口（dwExStyle ^= WS_EX_LAYERED）

protected:
	WindowEx(
		const ULONG CtrlFL,
		const std::wstring& SkinFolder,
		const std::wstring& SkinFile,
		const std::wstring& ClassName,
		const std::wstring& WindowId)
	{
		m_CtrlFL     = CtrlFL;
		m_SkinFolder = SkinFolder;
		m_SkinFile   = SkinFile;
		m_ClassName  = ClassName;
		m_WindowId   = WindowId;
	}
	virtual ~WindowEx() {}

public:
	/**
	 * 以下三个接口是必须要覆写的接口，父类会调用这三个接口来构建窗口
	 * GetSkinFolder		要绘制的窗口皮肤资源路径
	 * GetSkinFile			要绘制的窗口的xml描述文件
	 * GetWindowClassName	窗口唯一的类名称
	 */
	virtual std::wstring GetSkinFolder() override { return m_SkinFolder; }
	virtual std::wstring GetSkinFile()   override { return m_SkinFile; }
	virtual std::wstring GetWindowClassName() const override { return m_ClassName; }

	/**
	 * 获取窗口id
	 */
	virtual std::wstring GetWindowId() const { return m_WindowId; };

	/**
	 * 关闭窗口
	 */
	virtual void Close(UINT nRet = IDOK);

	/**
	 * 创建窗口
	 * @param[in] hWndParent 父窗口句柄
	 * @param[in] pstrName 窗口名称
	 * @param[in] dwStyle 窗口样式
	 * @param[in] dwExStyle 窗口扩展样式
	 * @param[in] isLayeredWindow 是否创建分层窗口
	 * @param[in] rc 窗口位置
	 * @return HWND 窗口句柄
	 */
	virtual HWND Create(
		HWND hWndParent,
		LPCTSTR pstrName,
		DWORD dwStyle,
		DWORD dwExStyle,
		bool isLayeredWindow = true,
		const ui::UiRect& rc = ui::UiRect(0, 0, 0, 0)) override;

	/**
	 * 当收到窗口关闭消息时被调用
	 * @param[in] uMsg 消息类型
	 * @param[in] wParam 消息附加参数
	 * @param[in] lParam 消息附加参数
	 * @param[out] bHandled 返回 false 则继续派发该消息，否则不再派发该消息
	 * @return 返回消息处理结果
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	/**
	 * 处理窗口被销毁的消息
	 * @param[in] uMsg 消息类型
	 * @param[in] wParam 消息附加参数
	 * @param[in] lParam 消息附加参数
	 * @param[out] bHandled 返回 false 则继续派发该消息，否则不再派发该消息
	 * @return LRESULT 处理结果
	 */
	virtual LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	/**
	 * 窗口消息的派发函数
	 * @param[in] uMsg 消息类型
	 * @param[in] wParam 消息附加参数
	 * @param[in] lParam 消息附加参数
	 * @return LRESULT 处理结果
	 */
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

protected:
	ULONG        m_CtrlFL;		// 控制标记
	std::wstring m_SkinFolder;	// 资源路径
	std::wstring m_SkinFile;	// 描述文件
	std::wstring m_ClassName;	// 窗口类名
	std::wstring m_WindowId;	// 窗口id
};

NS_UI_COMP_END