#pragma once
#include <Windows.h>

namespace GameL
{
	// XBoxボタン
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
		UP = 10000,
		LEFT,
		DOWN,
		RIGHT,
	};

	typedef class CWinInputs
	{
		public:
			static bool WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam);//ウィンドウプロジーシャーコールバック関数登録用
			static bool GetVKey(int v_key);
			static bool GetJoyButton(XBoxInput xBoxButton);
			static bool GetMouButtonL();
			static bool GetMouButtonR();
		
			static int GetPosX();
			static int GetPosY();

			static void Init();
		

		private:
			static int   m_x,m_y;		//マウス座標
			static bool  m_ButtonL;		//マウスクリック
			static bool  m_ButtonR;
			static BYTE m_KeyBoard[256];//キーボード配列
	}Input;
};