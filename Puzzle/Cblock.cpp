//使用するヘッダーファイル
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
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

	m_bColornum = rand() % 6;//色決めのためのランダム

	m_bStop_flag = false;

	m_a_key_push = false;
	m_d_key_push = false;

	m_elementX_storage = 0;
	m_elementY_storage = 0;

	m_Again_fall_on = false;
}

//アクション
void Cblock::Action()
{
	//マップオブジェクト取得
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);

	//停止なら
	if (m_bStop_flag == true)
	{
		//マップのデータがブロックの消去で無くなっていたら
		if (obj_map->GetMap(m_elementX_storage, m_elementY_storage) == 0)
		{
			this->SetStatus(false);//ブロック消す
		}

		//下にブロックがあって、消える処理で消えていたら
		if (obj_map->GetMap(m_elementX_storage, m_elementY_storage + 1) == 0)
		{
			//停止フラグを切って、再落下させる
			m_bStop_flag = false;
			m_Again_fall_on = true;
			obj_map->SetMap(m_elementX_storage, m_elementY_storage, 0);

			return;
		}

		return;//とりあえず何もしない
	}


	//移動ベクトル初期化
	m_fVy = 2.0f;
	m_fVx = 0.0f;

	//位置を32=1のようにする
	int x = ((int)m_fPx - 160) / 32;
	int y = (int)m_fPy / 32;

	//Aを押したら
	// XBOXコン 使用例 if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		//長押し防止
		//再落下時に入らないように
		if (m_a_key_push == false && m_Again_fall_on == false)
		{
			//移動先が160fより小さくなるなら
			if (obj_map->GetMap(x - 1, y+1) != 0)
			{
				;//何もしない
			}
			else
			{
				m_fVx = -32.0f;//左に動く

				m_a_key_push = true;
			}
		}
	}
	else
	{
		m_a_key_push = false;
	}


	//Dを押したら
	if (Input::GetVKey('D') == true)
	{
		//長押し防止
		//再落下時に入らないように
		if (m_d_key_push == false && m_Again_fall_on == false)
		{
			//移動先が576fより大きくなるから
			if (obj_map->GetMap(x + 1, y+1) != 0)
			{
				;//何もしない
			}
			else
			{
				m_fVx = 32.0f;//右に動く

				m_d_key_push = true;
			}
		}
	}
	else
	{
		m_d_key_push = false;
	}



	//移動ベクトル加算
	m_fPx += m_fVx;
	m_fPy += m_fVy;

	//ブロックが一番下に着いたら止める
	if ( obj_map->GetMap(x,y+1) != 0/*383.0f-32.0f*//*(float)Window::GetHeight() - 32.0f*/)
	{
		//移動ベクトル停止
		//m_fVy = 0.0f;
		//m_fVx = 0.0f;

		//停止したブロックの要素番号を保存する
		m_elementX_storage = x;
		m_elementY_storage = y;

		//マップに停止したブロックの情報を入れる
		obj_map->SetMap(x, y, m_bColornum + 1);


		obj_map->confirmblock(x, y, m_bColornum + 1);

		m_bStop_flag = true;//停止フラグON

		//再落下時に反応しないように
		if (m_Again_fall_on == false)
		{
			//新しく降らせる
			Cblock* p_block = new Cblock();
			Objs::InsertObj(p_block, OBJ_BLOCK, 1);
		}
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

	//色決め
	if (m_bColornum == 0)
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);//オレンジ
	}

	else if (m_bColornum == 1)
	{
		Draw::Draw(1, &src, &dst, c, 0.0f);//水色
	}

	else if (m_bColornum == 2)
	{
		Draw::Draw(2, &src, &dst, c, 0.0f);//黄色
	}

	else if (m_bColornum == 3)
	{
		Draw::Draw(3, &src, &dst, c, 0.0f);//オレンジ星
	}

	else if (m_bColornum == 4)
	{
		Draw::Draw(4, &src, &dst, c, 0.0f);//水色星
	}

	else if (m_bColornum == 5)
	{
		Draw::Draw(5, &src, &dst, c, 0.0f);//黄色星
	}
}