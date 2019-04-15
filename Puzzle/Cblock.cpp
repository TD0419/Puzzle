//使用するヘッダーファイル
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneManager.h"
#include"GameL/WinInputs.h"
#include"GameL/SetWindow.h"
#include"GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void Cblock::Init()
{
	m_fPx = 416.0f;
	m_fPy = 32.0f;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bColornum = rand() % 2;

	m_bStop_flag = false;
}

//アクション
void Cblock::Action()
{
	//停止なら
	if (m_bStop_flag == true)
	{
		return;
	}


	//移動ベクトル初期化
	m_fVy = 3.0f;
	m_fVx = 0.0f;

	//Aを押したら
	// XBOXコン 使用例 if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		if (m_fPx - 32.0f <= 160.0f)
		{
			;
		}
		else
		{
			m_fVx = -32.0f;//左に動く
		}
	}
	//Dを押したら
	else if (Input::GetVKey('D') == true)
	{
		if (m_fPx + 32.0f >= 576.0f)
		{
			;
		}
		else
		{
			m_fVx = 32.0f;//右に動く
		}
	}

	//移動ベクトル加算
	m_fPx += m_fVx;
	m_fPy += m_fVy;

	//ブロックが一番下に着いたら止める
	if (m_fPy == (float)Window::GetHeight() - 32.0f)
	{
		m_fVy = 0.0f;
		m_fVx = 0.0f;

		m_bStop_flag = true;

		//新しく降らせる
		Cblock* p_block = new Cblock();
		Objs::InsertObj(p_block, OBJ_BLOCK, 1);
	}



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

	dst.m_top = 0.0f + m_fPy;
	dst.m_left = 0.0f + m_fPx;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	if (m_bColornum == 0)
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

	else if (m_bColornum == 1)
	{
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
}