#pragma once
#include <Windows.h>

namespace GameL
{
	#define KEYCODE_MAX (256) // 使用できるキーコードの数

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
		UP,
		LEFT,
		DOWN,
		RIGHT,
	};

	typedef class CWinInputs
	{
		public:
			static bool WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam);// ウィンドウプロジーシャーコールバック関数登録用
			static bool GetVKey(int v_key);
			static bool GetVKeyDown(int v_key);						  // キーを押していない状態から押した時のキー入力を取得
			static bool GetJoyButton(XBoxInput xBoxButton);
			static bool GetJoyButtonDown(XBoxInput xBoxButton);		  // キーを押していない
			static bool GetMouButtonL();
			static bool GetMouButtonR();
			static void Update();									

			static int GetPosX();
			static int GetPosY();

			static void Init();
			

		private:
			static int   m_x,m_y;		//マウス座標
			static bool  m_ButtonL;		//マウスクリック
			static bool  m_ButtonR;
			static bool m_KeyCode[256]; // キーコード配列(押しっぱなしを検出する用)
	}Input;
};