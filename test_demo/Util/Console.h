#pragma once

//****************************/
//-- class Console
//****************************/
class Console
{
public:
	/* 控制台是否打开
	 * @return true=已打开，false=未打开
	**/
	static bool IsOpened();

	/* 打开控制台
	 * @return true=成功，false=失败
	**/
	static bool Open();

	/* 关闭控制台
	 * @return 无
	**/
	static void Close();
};