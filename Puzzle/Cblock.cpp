//使用するヘッダーファイル
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameL/SetWindow.h"
#include"GameHead.h"

//使用するネームスペース
using namespace GameL;

Cblock::Cblock(int num, float fPosX, CNextBlock* pNextBlock, CMap* pMap)
{
	if (num == 100)
	{
		m_bColornum = rand() % 6;
	}
	else
	{
		m_bColornum = num;
	}

	m_fPx = fPosX;

	m_pNextBlock = pNextBlock;
	m_pMap = pMap;
}

//イニシャライズ
void Cblock::Init()
{
	m_fPy = MAP_SHIFT_Y;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bStop_flag = false;

	m_elementX_storage = (int)((m_fPx - m_pMap->GetShiftX()) / 32.f);
	m_elementY_storage = (int)((m_fPy - 192.f) / 32.f);

	m_Again_fall_on = false;
	m_block_fall_ok = false;
}

//アクション
void Cblock::Action()
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
			m_Again_fall_on = true;
			m_pMap->SetMap(m_elementX_storage, m_elementY_storage, 0);

			return;
		}

		return;
	}

	if (m_pMap->GetName() == OBJ_MAP)
	{
		char nKeyCode = 0;
		//Aを押したら
		// XBOXコン 使用例 if (Input::GetJoyButton(XBoxInput::UP) == true)
		if (m_Again_fall_on == false)
		{
			// 押した瞬間
			if (Input::GetVKeyDown('A') == true)
			{
				nKeyCode = 'A';
			}
			else if (Input::GetVKeyDown('D') == true)
			{
				nKeyCode = 'D';
			}
		
			g_SendData.m_player_operation = nKeyCode;

			while (1)
			{
				SendState send_state = NetWork::Send((char*)&g_SendData, sizeof(g_SendData));
				// 対戦相手のデータ送信成功
				if (send_state == SendState::Send_Successful)
				{
					break;
				}
				// 対戦相手の通信が途絶えた場合
				else if (send_state == SendState::Connect_Cut)
				{
					if (NetWork::GetisNetWorkConnect() == true)
					{
						// タイトルに戻る
						Scene::SetScene(new CSceneTitle);

						// 対戦相手の通信が途絶えた場合
						MessageBox(NULL, L"対戦相手との通信が途絶えました", L"通信エラー", MB_OK);

						// 接続切れフラグを立てる
						NetWork::NetWorkCut();
					}
					return;
				}
			}

			Sleep(10);
		}

		// 移動させる
		Move((int)nKeyCode);
	}
	else
	{
		int nTime = 0;
		char nKeyCode = 0;
		if (m_Again_fall_on == false)
		{
			while (1)
			{
				RecvState recv_state = NetWork::Recv((char*)&g_SendData, sizeof(g_SendData));
				
				// 対戦相手のデータ受け取り成功
				if (recv_state == RecvState::Recv_Successful || recv_state == RecvState::Recv_NoSend)
				{
					break;
				}
				// 対戦相手の通信が途絶えた場合
				else if (recv_state == RecvState::Connect_Cut)
				{
					if (NetWork::GetisNetWorkConnect() == true)
					{
						// タイトルに戻る
						Scene::SetScene(new CSceneTitle);

						// 対戦相手の通信が途絶えた場合
						MessageBox(NULL, L"対戦相手との通信が途絶えました", L"通信エラー", MB_OK);

						// 接続切れフラグを立てる
						NetWork::NetWorkCut();
					}
					return;
				}
			}

			// 操作情報を保存
			nKeyCode = g_SendData.m_player_operation;
		}

		// 移動させる
		Move((int)nKeyCode);
	}

	//位置を32=1のようにする
	m_elementX_storage = (int)((m_fPx - m_pMap->GetShiftX()) / 32.f);
	m_elementY_storage = (int)((m_fPy - 192.f) / 32.f);

	//ブロックが一番下に着いたら止める
	if (m_pMap->GetMap(m_elementX_storage, m_elementY_storage +1) != 0)
	{
		//マップに停止したブロックの情報を入れる
		m_pMap->SetMap(m_elementX_storage, m_elementY_storage, m_bColornum + 1);

		m_pMap->confirmblock(m_elementX_storage, m_elementY_storage, m_bColornum + 1);

		m_bStop_flag = true;//停止フラグON
		
		if (m_pMap->GetMap(6, 0) != 0)
		{
			Scene::SetScene(new CSceneResult(m_pMap));
		}
		
		//再落下時に反応しないように
		if (m_Again_fall_on == false)
		{
			//落下おっけーのフラグを入れる
			m_block_fall_ok = true;
			
			//落下オッケーフラグが変わったら入れる
			m_pNextBlock->Setblock_fall(m_block_fall_ok);
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

// 移動処理をまとめた関数
void Cblock::Move(int nKeyCode)
{
	//移動ベクトル初期化
	m_fVy = 4.0f;
	m_fVx = 0.0f;

	//Aを押したら
	// XBOXコン 使用例 if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (nKeyCode == (int)'A')
	{
		//移動先が160fより小さくなるなら
		if (m_pMap->GetMap(m_elementX_storage - 1, m_elementY_storage + 1) != 0)
		{
			;//何もしない
		}
		else
		{
			m_fVx = -32.0f;//左に動く
		}
	}

	if (nKeyCode == (int)'D')
	{
		//移動先が576fより大きくなるから
		if (m_pMap->GetMap(m_elementX_storage + 1, m_elementY_storage + 1) != 0)
		{
			;//何もしない
		}
		else
		{
			m_fVx = 32.0f;//右に動く
		}
	}

	//移動ベクトル加算
	m_fPy += m_fVy;
	m_fPx += m_fVx;
}