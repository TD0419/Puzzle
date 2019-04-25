//使用するヘッダーファイル
#include"CFreezeblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameHead.h"

//使用するネームスペース
using namespace GameL;


CFreezeblock::CFreezeblock(int x,int y,int id)
{
	m_fPx = x * 32.0f + 160.0f;
	m_fPy = y * 32.0f;
	m_bColornum = 7;
	m_elementX_storage = x;
	m_elementY_storage = y;
}

//イニシャライズ
void CFreezeblock::Init()
{
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bStop_flag = false;
}

//アクション
void CFreezeblock::Action()
{
	//マップオブジェクト取得
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);

	//停止なら
	if (m_bStop_flag == true)
	{
		return;//とりあえず何もしない
	}


	//移動ベクトル設定
	m_fVy = 4.0f;

	//ベクトル加算
	m_fPy += m_fVy;

	int x = ((int)m_fPx - 160) / 32;
	int y = (int)m_fPy / 32;

	//ブロックが一番下に着いたら止める
	if (obj_map->GetMap(x, y + 1) != 0)
	{
		//停止したブロックの要素番号を保存する
		m_elementX_storage = x;
		m_elementY_storage = y;

		//マップに停止したブロックの情報を入れる
		obj_map->SetMap(x, y, m_bColornum);

		m_bStop_flag = true;//停止フラグON
	}
}

//ドロー
void CFreezeblock::Draw()
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

	//色決め
	Draw::Draw(8, &src, &dst, c, 0.0f);

}