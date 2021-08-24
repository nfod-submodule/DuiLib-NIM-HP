#pragma once

#include "resource.h"

bool OnInit();
void OnExit();

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
	 * �麯������ʼ�����߳�
	 * @return void	�޷���ֵ
	 */
	virtual void Init() override;

	/**
	 * �麯�������߳��˳�ʱ����һЩ������
	 * @return void	�޷���ֵ
	 */
	virtual void Cleanup() override;
};