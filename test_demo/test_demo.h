#pragma once

#include "resource.h"

//****************************/
//-- class UIThread
//****************************/
class UIThread : public nbase::FrameworkThread
{
public:
	UIThread() : nbase::FrameworkThread("UIThread") {}
	virtual ~UIThread() {}

private:
	/**
	 * 虚函数，初始化主线程
	 * @return void	无返回值
	 */
	virtual void Init() override;

	/**
	 * 虚函数，主线程退出时，做一些清理工作
	 * @return void	无返回值
	 */
	virtual void Cleanup() override;
};