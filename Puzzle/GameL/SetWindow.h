#pragma once
#include <crtdbg.h>
#include <Windows.h>

namespace GameL
{
	//ウィンドウ作成
	typedef class LSetWindow
	{
		public:
			static void NewWindow(int w,int h,wchar_t* name,HINSTANCE hInstance, bool bFullScreen);
			static void DeleteWindow();
			static HWND GethWnd()	{return m_hWnd;}
			static int GetWidth() { return m_width; }
			static int GetHeight() { return m_height; }
		private:
			static HWND m_hWnd;			//ウィンドウハンドル
			static int  m_width;
			static int  m_height;
	}Window;

};