#include "WinInputs.h"
using namespace GameL;

#define STICK_INITIAL_POSITION (32767)		// XBox�̃X�e�B�b�N�̏����ʒu(�X�e�B�b�N�ړ�����p)

int   CWinInputs::m_x,CWinInputs::m_y;		//�}�E�X���W
bool  CWinInputs::m_ButtonL;				//�}�E�X�N���b�N
bool  CWinInputs::m_ButtonR;
bool  CWinInputs::m_KeyCode[KEYCODE_MAX];	//�L�[�R�[�h�z��

void CWinInputs::Init()
{
	m_x=0;
	m_y=0;
	m_ButtonL=false;
	m_ButtonR=false;
	memset(m_KeyCode,0x00,sizeof(m_KeyCode));
}

bool CWinInputs::WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam)
{
	if(*uMsg== WM_MOUSEMOVE )
	{
		POINT point={ LOWORD(*lParam), HIWORD((*lParam))};
		
		m_x = point.x;   // �J�[�\���� x ���W
		m_y = point.y;   // �J�[�\���� y ���W
		return true;
	}
	else if(*uMsg==WM_LBUTTONDOWN)
	{
		m_ButtonL=true;
	}
	else if(*uMsg==WM_LBUTTONUP)
	{
		m_ButtonL=false;
	}
	else if(*uMsg==WM_RBUTTONDOWN)
	{
		m_ButtonR=true;
	}
	else if(*uMsg==WM_RBUTTONUP)
	{
		m_ButtonR=false;
	}
	return false;
}

bool CWinInputs::GetVKey(int v_key)
{	
	if (GetAsyncKeyState(v_key))
		return true;
	else
		return false;
	
	return false;
}

// ����----------------------------------------------------------------------
// GetVKeyDown�֐��͘A���œ����L�[�𒲂ׂĂ��܂��ƁA�ŏ��̏����͐������������A
// ���̎�����̏����́A�������ςȂ����������Đ����������Ȃ����̎d�l��
// ��肪����΁A��蒼���܂��B
/* (��)
	   Z�L�[���������u��
	   if(GetVKeyDown('Z') == true)
	   {
			// �����ɓ���(����������);
	   }

	   if(GetVKeyDown('Z') == true)
	   {
			// �����ɓ���Ȃ�(�������Ȃ������A�������ςȂ����������Ă���);
	   }
*/
// --------------------------------------------------------------------------

// �L�[�������Ă��Ȃ���Ԃ��牟�������̃L�[���͂��擾
// ����1 int   : ���ׂ����L�[
// �߂�l bool : �����ꂽ�u�� true  ������Ă��Ȃ�or�������ςȂ� false
bool CWinInputs::GetVKeyDown(int v_key)
{
	// �L�[��������Ă��邩�m�F
	if (GetVKey(v_key) == false)
	{
		m_KeyCode[v_key] = false;

		// ������Ă��Ȃ�
		return false;
	}
	else
	{
		// �܂��L�[��������Ă��Ȃ�
		if (m_KeyCode[v_key] == false)
		{
			m_KeyCode[v_key] = true;

			// �������u��
			return true;
		}
		else
		{
			// �������ςȂ�
			return false;
		}
	}
}

bool CWinInputs::GetMouButtonL()
{
	return m_ButtonL;
}
bool CWinInputs::GetMouButtonR()
{
	return m_ButtonR;
}

int CWinInputs:: GetPosX()
{
	return m_x;
}

int CWinInputs::GetPosY()
{
	return m_y;
}

// xBox�̃W���C�R���̃{�^�����͂��擾����
// ����1 XBoxInput : ���͂��m�F�������{�^�� 
// �߂�l bool	   : ������Ă��邩�ǂ�����Ԃ� false : ������Ă��Ȃ� true : ������Ă���
bool CWinInputs::GetJoyButton(XBoxInput xBoxButton)
{
	JOYINFOEX joyinfoex; // ���͏��擾
	MMRESULT mmresult;	 // �W���C�R�����͊֐������m�F�p

	// �W���C�R�����͎擾
	// �ڂ�����
	// https://docs.microsoft.com/ja-jp/windows/desktop/api/joystickapi/nf-joystickapi-joygetposex
	mmresult = joyGetPosEx(JOYSTICKID1, &joyinfoex);

	if (mmresult != JOYERR_NOERROR)
	{
		// �W���C�R�����m�F�ł��܂���
		return false;
	}

	// ���͂��m�F�������{�^����������Ă�����
	if ((int)joyinfoex.dwButtons == (int)xBoxButton)
	{
		// ������Ă���
		return true;
	}

	// �X�e�B�b�N���͊m�F
	// ��
	if (xBoxButton == XBoxInput::UP &&
		joyinfoex.dwYpos < STICK_INITIAL_POSITION)
	{
		// ������Ă���
		return true;
	}
	// ��
	if (xBoxButton == XBoxInput::LEFT &&
		joyinfoex.dwXpos < STICK_INITIAL_POSITION)
	{
		// ������Ă���
		return true;
	}
	// ��
	if (xBoxButton == XBoxInput::DOWN &&
		joyinfoex.dwYpos > STICK_INITIAL_POSITION)
	{
		// ������Ă���
		return true;
	}
	// �E
	if (xBoxButton == XBoxInput::RIGHT &&
		joyinfoex.dwXpos > STICK_INITIAL_POSITION)
	{
		// ������Ă���
		return true;
	}

	// ������Ă��Ȃ�
	return false;
}

// xBox�̃W���C�R���̃{�^�����͂��擾����
// ����1 XBoxInput : ���͂��m�F�������{�^�� 
// �߂�l bool	   : ������Ă��邩�ǂ�����Ԃ� false : ������Ă��Ȃ� true : ������Ă���
bool CWinInputs::GetJoyButtonDown(XBoxInput xBoxButton)
{
	// �L�[��������Ă��邩�m�F
	if (GetJoyButton(xBoxButton) == false)
	{
		m_KeyCode[(int)xBoxButton] = false;

		// ������Ă��Ȃ�
		return false;
	}
	else
	{
		// �܂��L�[��������Ă��Ȃ�
		if (m_KeyCode[(int)xBoxButton] == false)
		{
			m_KeyCode[(int)xBoxButton] = true;

			// �������u��
			return true;
		}
		else
		{
			// �������ςȂ�
			return false;
		}
	}
}