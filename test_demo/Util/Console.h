#pragma once

//****************************/
//-- class Console
//****************************/
class Console
{
public:
	/* ����̨�Ƿ��
	 * @return true=�Ѵ򿪣�false=δ��
	**/
	static bool IsOpened();

	/* �򿪿���̨
	 * @return true=�ɹ���false=ʧ��
	**/
	static bool Open();

	/* �رտ���̨
	 * @return ��
	**/
	static void Close();
};