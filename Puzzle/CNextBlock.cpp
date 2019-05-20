//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "CNextBlock.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

CNextBlock::CNextBlock(float a,CMap* pMap)
{
	m_Px = MAP_X * 32.0f + MAP_SHIFT_X + a;

	m_pMap = pMap;
}

void CNextBlock::Init()
{
	//m_Px = MAP_X * 32.0f + MAP_SHIFT_X;
	m_Py = MAP_SHIFT_Y;

	m_freeze_block_late = 0;
	m_generate_block_flag = false;

	m_block_num = rand() % 6;

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

			//ブロックの数値を決める
			m_block_num = rand() % 6;


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