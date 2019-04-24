//使用するヘッダーファイル
#include"CFreezeblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameHead.h"

//使用するネームスペース
using namespace GameL;

//イニシャライズ
void CFreezeblock::Init()
{
	m_fPx = 0.0f;
	m_fPy = 0.0f;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bStop_flag = false;

	m_bColornum = 0;

	m_elementX_storage = 0;
	m_elementY_storage = 0;
}

//アクション
void CFreezeblock::Action()
{
	//マップオブジェクト取得
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);


	for (int y = 0; y < 18; y++)
	{
		for (int x = 0; x < 14; x++)
		{
			if (obj_map->GetMap(x, y) == 7)
			{
				m_elementX_storage = x;
				m_elementY_storage = y;
				m_bColornum = 7;
			}
		}
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
	Draw::Draw(0, &src, &dst, c, 0.0f);

}