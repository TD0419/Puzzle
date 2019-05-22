//使用するヘッダーファイル
#include"CFreezeblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameHead.h"


//使用するネームスペース
using namespace GameL;


CFreezeblock::CFreezeblock(int x,int y,int id, CMap* pMap)
{
	if (pMap->GetName() == OBJ_MAP)
	{
		m_fPx = x * 32.0f + MAP_SHIFT_X;
	}
	else if (pMap->GetName() == OBJ_MAP_PLAY2)
	{
		m_fPx = x * 32.0f + MAP_SHIFT_X + 620.0f;
	}

	m_fPy = y * 32.0f + MAP_SHIFT_Y;
	m_bColornum = id;
	m_elementX_storage = x;
	m_elementY_storage = y;

	m_pMap = pMap;
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
	//停止なら
	if (m_bStop_flag == true)
	{
		//マップのデータがブロックの消去で無くなっていたら
		if (m_pMap->GetMap(m_elementX_storage, m_elementY_storage) == 0)
		{
			this->SetStatus(false);//ブロック消す
		}

		//下にブロックがあって、消える処理で消えていたら
		if (m_pMap->GetMap(m_elementX_storage, m_elementY_storage + 1) == 0)
		{
			//停止フラグを切って、再落下させる
			m_bStop_flag = false;
			//m_Again_fall_on = true;
			m_pMap->SetMap(m_elementX_storage, m_elementY_storage, 0);

			return;
		}

		return;//とりあえず何もしない
	}


	//移動ベクトル設定
	m_fVy = 4.0f;

	//ベクトル加算
	m_fPy += m_fVy;

	int x = (int)((m_fPx - m_pMap->GetShiftX()) / 32.f);
	int y = (int)((m_fPy - 192) / 32.f);

	//ブロックが一番下に着いたら止める
	if (m_pMap->GetMap(x, y + 1) != 0)
	{
		//停止したブロックの要素番号を保存する
		m_elementX_storage = x;
		m_elementY_storage = y;

		//マップに停止したブロックの情報を入れる
		m_pMap->SetMap(x, y, m_bColornum);

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