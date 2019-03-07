#include "SetWindow.h"
using namespace GameL;

//削除されていないメモリを出力にダンプする
#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG
HWND LSetWindow:: m_hWnd;
int  LSetWindow:: m_width;
int  LSetWindow:: m_height;

//ウィンドウ作成
// 引数5 bool : bFullScreen フルスクリーンフラグ true : フルスクリーン false : 通常ウィンドウ
void LSetWindow::NewWindow(int w,int h,wchar_t* name,HINSTANCE hInstance, bool bFullScreen)
{
	// フルスクリーン化
	if (bFullScreen == true)
	{
		DEVMODE dmScreenSettings;

		// ディスプレイサイズ取得
		m_width = GetSystemMetrics(SM_CXSCREEN);
		m_height = GetSystemMetrics(SM_CYSCREEN);

		// 全画面の場合、画面をユーザーのデスクトップと32ビットの最大サイズに設定
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)m_width;
		dmScreenSettings.dmPelsHeight = (unsigned long)m_height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// 表示設定をフルスクリーンに変更
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// フルスクリーンウィンドウ作成
		if (!(m_hWnd = CreateWindowEx(WS_EX_APPWINDOW, name, name,
			WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
			CW_USEDEFAULT, 0, m_width, m_height, 0, 0, hInstance, 0)))
		{
			return;
		}
	}
	// 通常ウィンドウサイズ
	else
	{
		m_width = w;
		m_height = h;

		int width  = m_width + GetSystemMetrics(SM_CXDLGFRAME) * 2;
		int height = m_height + GetSystemMetrics(SM_CYDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION);

		//ウィンドウ作成
		if( !( m_hWnd = CreateWindow( name, name, 
			WS_OVERLAPPEDWINDOW & ~( WS_MAXIMIZEBOX | WS_SIZEBOX ),
			CW_USEDEFAULT, 0,  width, height, 0, 0, hInstance, 0) ) )
		{
			 return ;
		}
	}

	ShowWindow( m_hWnd, SW_SHOW );

}

//ウィンドウ破棄
void LSetWindow::DeleteWindow()
{

	DestroyWindow(m_hWnd);	// ウィンドウを破棄し登録を解除
}