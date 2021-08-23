#pragma once

//****************************/
//-- class MainForm
//****************************/
class MainForm : public ui::WindowImplBase
{
public:
	MainForm();
	~MainForm();

	/**
	 * 以下三个接口是必须要覆写的接口，父类会调用这三个接口来构建窗口
	 * GetSkinFolder		接口设置要绘制的窗口皮肤资源路径
	 * GetSkinFile			接口设置要绘制的窗口的 xml 描述文件
	 * GetWindowClassName	接口设置窗口唯一的类名称
	 */
	virtual std::wstring GetSkinFolder() override;
	virtual std::wstring GetSkinFile() override;
	virtual std::wstring GetWindowClassName() const override;

	/**
	 * 收到 WM_CREATE 消息时该函数会被调用，通常做一些控件初始化的操作
	 */
	virtual void InitWindow() override;

	/**
	 * 收到 WM_CLOSE 消息时该函数会被调用
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	/**
	 * 处理所有控件的所有消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnNotify(ui::EventArgs* msg);

	/**
	 * 处理所有控件单击消息
	 * @param[in] msg 消息的相关信息
	 * @return bool true 继续传递控件消息，false 停止传递控件消息
	 */
	bool OnClicked(ui::EventArgs* msg);

private:
	ui::Button*	m_btn_logout;
	ui::Button*	m_btn_exit;
};

