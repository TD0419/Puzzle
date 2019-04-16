#pragma once
#include <Windows.h>

namespace GameL
{
	#define KEYCODE_MAX (256) // �g�p�ł���L�[�R�[�h�̐�

	// XBox�{�^��
	enum class XBoxInput
	{
		A = 1,
		B,
		X = 4,
		Y = 8,
		LB = 16,
		RB = 32,
		BACK = 64,
		START = 128,
		UP,
		LEFT,
		DOWN,
		RIGHT,
	};

	typedef class CWinInputs
	{
		public:
			static bool WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam);// �E�B���h�E�v���W�[�V���[�R�[���o�b�N�֐��o�^�p
			static bool GetVKey(int v_key);
			static bool GetVKeyDown(int v_key);						  // �L�[�������Ă��Ȃ���Ԃ��牟�������̃L�[���͂��擾
			static bool GetJoyButton(XBoxInput xBoxButton);
			static bool GetJoyButtonDown(XBoxInput xBoxButton);		  // �L�[�������Ă��Ȃ�
			static bool GetMouButtonL();
			static bool GetMouButtonR();
			static void Update();									

			static int GetPosX();
			static int GetPosY();

			static void Init();
			

		private:
			static int   m_x,m_y;		//�}�E�X���W
			static bool  m_ButtonL;		//�}�E�X�N���b�N
			static bool  m_ButtonR;
			static bool m_KeyCode[256]; // �L�[�R�[�h�z��(�������ςȂ������o����p)
	}Input;
};