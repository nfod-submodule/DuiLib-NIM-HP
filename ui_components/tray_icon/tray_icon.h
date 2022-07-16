#pragma once

#include "public_define.h"

NS_UI_COMP_BEGIN

//-- ����ͼ���¼�����ӿ�
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

//-- ����ͼ�������
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
	 * ��ʼ����ͼ��
	 * @param[in] pDelegate		����ͼ���¼�����ӿ�
	 * @param[in] lpClassName	��������
	 * @param[in] lpWindowName	������
	 * @param[in] lpStrRegWnd	��ע����Ϣ������
	 * @return void	�޷���ֵ
	**/
	void Init(
		TrayIconDelegate* pDelegate,
		LPCWSTR lpClassName,
		LPCWSTR lpWindowName,
		LPCWSTR lpStrRegWnd);

	/**
	 * ��������ͼ��
	 * @return void	�޷���ֵ
	**/
	void Destroy();

	/**
	 * ��������ͼ�����ʾ�ı�
	 * @param[in] hIcon		����ͼ����
	 * @param[in] wstrTip	������ʾ�ı�
	 * @return TRUE=�ɹ� FALSE=ʧ��
	**/
	BOOL SetTrayIcon(
		HICON hIcon,
		const std::wstring& wstrTip);

private:
	/**
	 * �����ڲ�������Ϣ
	 * @param[in] hWnd		���ھ��
	 * @param[in] uMsg		��Ϣֵ
	 * @param[in] wParam	���Ӳ���
	 * @param[in] lParam	���Ӳ���
	 * @return LRESULT ��Ϣ������
	**/
	static LRESULT CALLBACK WndProc(
		HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

	void Proc(LPARAM lParam);

	/**
	 * �ָ�����ͼ��
	 * @return TRUE=�ɹ� FALSE=ʧ��
	**/
	BOOL RestoreTrayIcon();

	/**
	 * �޸�����ͼ��
	 * @param[in] uID		����ID
	 * @param[in] dwMsg		ָ�����ڽ���������Ϣ�Ļص���Ϣֵ
	 * @param[in] hIcon		����ͼ����
	 * @param[in] wstrTip	������ʾ�ı�
	 * @return TRUE=�ɹ� FALSE=ʧ��
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