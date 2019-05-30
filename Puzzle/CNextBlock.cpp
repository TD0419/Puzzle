//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/SceneManager.h"

#include "CNextBlock.h"
#include "GameHead.h"
#include <time.h>

//使用するネームスペース
using namespace GameL;

extern bool g_isNetWorkCut;

CNextBlock::CNextBlock(float a,CMap* pMap)
{
	m_Px = MAP_X * 32.0f + MAP_SHIFT_X + a;

	m_pMap = pMap;
}

void CNextBlock::Init()
{
	m_Py = MAP_SHIFT_Y;

	m_freeze_block_late = 0;
	m_generate_block_flag = false;

	// 乱数を変える
	if (NetWork::GetConnectKind() == NetWork::ConnectKind::Server)
	{
		srand((unsigned int)time(NULL));
	}
	else
	{
		srand((unsigned int)(time(NULL) + (unsigned int)1000));
	}

	// このタイミングではGetNameでは判定できないので、GetShiftXを使用している。
	if (m_pMap->GetShiftX() == 96)
	{
		m_block_num = rand() % 100;

		if (m_block_num < 40)
		{
			m_block_num = (rand() % 3) + 3;
		}
		else
		{
			m_block_num = rand() % 3;
		}

		// 生成するブロック情報を送る
		SendNextBlock(m_block_num);
	}
	else
	{
		// 対戦相手の次のブロック情報を受け取る
		m_block_num = RecvNextBlock();
	}

	Cblock* p_block = new Cblock(m_block_num, m_Px - 192.f, this, m_pMap);
	Objs::InsertObj(p_block, OBJ_BLOCK_2, 1);

	freeze_time = 0;
}

void CNextBlock::Action()
{
	if (m_generate_block_flag == true)
	{
		//FreezeBlock_Generateの戻り値をとってくる	
		freeze_time = m_pMap->FreezeBlock_Generate();
	}

	//freeze_timeがじゃなかったら
	if (freeze_time != 0)
	{
		//freeze_timeに代入する
		m_freeze_block_late = freeze_time;
	}

	//下に落ちた時のフラグがtrueなら
	if (m_generate_block_flag == true)
	{
		//freeze_block_lateが0じゃなかったら
		if (m_freeze_block_late > 0)
		{
			//1減らす
			m_freeze_block_late--;
		}
		else
		{
			Cblock* p_block = new Cblock(m_block_num, m_Px - 192.f,this, m_pMap);
			Objs::InsertObj(p_block, OBJ_BLOCK_2, 1);

			if (m_pMap->GetName() == OBJ_MAP)
			{
				//ブロックの数値を決める
				m_block_num = rand() % 100;

				if (m_block_num < 60)
				{
					m_block_num = (rand() % 3) + 3;
				}
				else
				{
					m_block_num = rand() % 3;
				}

				// 生成するブロック情報を送る
				SendNextBlock(m_block_num);
			}
			else
			{
				// 対戦相手の次のブロック情報を受け取る
				m_block_num = RecvNextBlock();
			}

			//落下フラグを変える
			m_generate_block_flag = false;

			freeze_time = 0;
		}
	}

}

void CNextBlock::Draw()
{
	//カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//切り取り位置
	RECT_F dst;//表示位置

	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = 0.0f + m_Py;
	dst.m_left = 0.0f + m_Px;
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 96.0f;

	Draw::Draw(15, &src, &dst, c, 0);



	//切り取り位置の設定
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	dst.m_top = 0.0f + m_Py + 32.0f;
	dst.m_left = 0.0f + m_Px + 32.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	//色決め
	if (m_block_num == 0)
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);//オレンジ
	}

	else if (m_block_num == 1)
	{
		Draw::Draw(1, &src, &dst, c, 0.0f);//水色
	}

	else if (m_block_num == 2)
	{
		Draw::Draw(2, &src, &dst, c, 0.0f);//黄色
	}

	else if (m_block_num == 3)
	{
		Draw::Draw(3, &src, &dst, c, 0.0f);//オレンジ星
	}

	else if (m_block_num == 4)
	{
		Draw::Draw(4, &src, &dst, c, 0.0f);//水色星
	}

	else if (m_block_num == 5)
	{
		Draw::Draw(5, &src, &dst, c, 0.0f);//黄色星
	}
}

// ネットワークを使用した、次のブロック情報を送る
// 引数1 int : 送りたい情報
void CNextBlock::SendNextBlock(int nNextBlock)
{
	g_SendData.m_generate_block = (char)nNextBlock;

	// 生成するブロック情報を送る
	while (1)
	{
		SendState send_state = NetWork::Send((char*)&g_SendData, sizeof(g_SendData));

		if (send_state == SendState::Send_Successful)
		{
			return;
		}
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
}

// ネットワークを使用した、次のブロック情報を受け取る
// 戻り値 int : 受け取ったデータを返す データがなければ、-1を返す
int CNextBlock::RecvNextBlock()
{
	int nTime = 0;
	// 生成するブロック情報が来るまで待つ
	while (1)
	{
		RecvState recv_state = NetWork::Recv((char*)&g_SendData, sizeof(g_SendData));
		if (recv_state == RecvState::Recv_Successful || recv_state == RecvState::Recv_NoSend)
		{
			break;
		}
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

			return -1;
		}
	}

	return (int)g_SendData.m_generate_block;
}