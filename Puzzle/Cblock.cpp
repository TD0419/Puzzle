//使用するヘッダーファイル
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneManager.h"
#include"GameL/WinInputs.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void Cblock::Init()
{
	m_f_px = 400.0f;
	m_f_py = 32.0f;
	m_f_vx = 0.0f;
	m_f_vy = 0.0f;
}

//アクション
void Cblock::Action()
{
	//移動ベクトル初期化
	m_f_vy = 1.0f;
	m_f_vx = 0.0f;

	//Aを押したら
	// XBOXコン 使用例 if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		m_f_vx = -3.0f;//左に動く
	}
	//Dを押したら
	else if (Input::GetVKey('D') == true)
	{
		m_f_vx = 3.0f;//右に動く
	}

	//移動ベクトル加算
	m_f_px += m_f_vx;
	m_f_py += m_f_vy;
}

//ドロー
void Cblock::Draw()
{
	//カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	dst.m_top = 0.0f + m_f_py;
	dst.m_left = 0.0f + m_f_px;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);
}