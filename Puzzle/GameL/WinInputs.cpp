#include "WinInputs.h"
using namespace GameL;

#define STICK_INITIAL_POSITION (32767)		// XBoxのスティックの初期位置(スティック移動判定用)

int   CWinInputs::m_x,CWinInputs::m_y;		//マウス座標
bool  CWinInputs::m_ButtonL;				//マウスクリック
bool  CWinInputs::m_ButtonR;
bool  CWinInputs::m_KeyCode[KEYCODE_MAX];	//キーコード配列
bool  CWinInputs::m_KeyCodeDown[KEYCODE_MAX];

void CWinInputs::Init()
{
	m_x=0;
	m_y=0;
	m_ButtonL=false;
	m_ButtonR=false;
	memset(m_KeyCode,0x00,sizeof(m_KeyCode));
	memset(m_KeyCodeDown, 0x00, sizeof(m_KeyCodeDown));
}

bool CWinInputs::WmInput(HWND hWnd,UINT* uMsg, LPARAM* lParam)
{
	if(*uMsg== WM_MOUSEMOVE )
	{
		POINT point={ LOWORD(*lParam), HIWORD((*lParam))};
		
		m_x = point.x;   // カーソルの x 座標
		m_y = point.y;   // カーソルの y 座標
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
	{
		m_KeyCode[v_key] = true;
		return true;
	}
	else
	{
		m_KeyCode[v_key] = false;
		return false;
	}
	
	return false;
}

// キーを押していない状態から押した時のキー入力を取得
// 引数1 int   : 調べたいキー
// 戻り値 bool : 押された瞬間 true  押されていないor押しっぱなし false
bool CWinInputs::GetVKeyDown(int v_key)
{
	// キーが押されているか確認
	if (GetVKey(v_key) == false)
	{
		m_KeyCode[v_key] = false;

		// 押されていない
		return false;
	}

	m_KeyCode[v_key] = true;
	// 押しっぱなしまたは、押した瞬間
	return !(m_KeyCodeDown[v_key]);
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

// xBoxのジョイコンのボタン入力を取得する
// 引数1 XBoxInput : 入力を確認したいボタン 
// 戻り値 bool : 押された瞬間 true  押されていないor押しっぱなし false
bool CWinInputs::GetJoyButton(XBoxInput xBoxButton)
{
	JOYINFOEX joyinfoex; // 入力情報取得
	MMRESULT mmresult;	 // ジョイコン入力関数成功確認用

	// ジョイコン入力取得
	// 詳しくは
	// https://docs.microsoft.com/ja-jp/windows/desktop/api/joystickapi/nf-joystickapi-joygetposex
	mmresult = joyGetPosEx(JOYSTICKID1, &joyinfoex);

	if (mmresult != JOYERR_NOERROR)
	{
		// ジョイコンが確認できません
		return false;
	}

	// 入力を確認したいボタンが押されていたら
	if ((int)joyinfoex.dwButtons == (int)xBoxButton)
	{
		// 押されている
		return true;
	}

	// スティック入力確認
	// 上
	if (xBoxButton == XBoxInput::UP &&
		joyinfoex.dwYpos < STICK_INITIAL_POSITION)
	{
		// 押されている
		return true;
	}
	// 左
	if (xBoxButton == XBoxInput::LEFT &&
		joyinfoex.dwXpos < STICK_INITIAL_POSITION)
	{
		// 押されている
		return true;
	}
	// 下
	if (xBoxButton == XBoxInput::DOWN &&
		joyinfoex.dwYpos > STICK_INITIAL_POSITION)
	{
		// 押されている
		return true;
	}
	// 右
	if (xBoxButton == XBoxInput::RIGHT &&
		joyinfoex.dwXpos > STICK_INITIAL_POSITION)
	{
		// 押されている
		return true;
	}

	// 押されていない
	return false;
}

// xBoxのジョイコンのボタン入力を取得する
// 引数1 XBoxInput : 入力を確認したいボタン 
// 戻り値 bool	   : 押されているかどうかを返す false : 押されていない、または押しっぱなし true : 押した瞬間
bool CWinInputs::GetJoyButtonDown(XBoxInput xBoxButton)
{
	// キーが押されているか確認
	if (GetJoyButton(xBoxButton) == false)
	{
		m_KeyCode[(int)xBoxButton] = false;

		// 押されていない
		return false;
	}
	else
	{
		m_KeyCode[(int)xBoxButton] = true;

		// 押しっぱなしまたは、押した瞬間
		return !(m_KeyCodeDown[(int)xBoxButton]);
	}
}

// キー入力情報更新する(押しっぱなし、押した瞬間を分けるため)
void CWinInputs::Update()
{
	for (int i = 0; i < 256; i++)
	{
		m_KeyCodeDown[i] = m_KeyCode[i];
	}
}