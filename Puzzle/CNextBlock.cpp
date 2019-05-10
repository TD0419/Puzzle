//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "CNextBlock.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

void CNextBlock::Init()
{
	m_Px = 608.0f;
	m_Py = 0.0f;

	freeze_block_late = 0;
	generate_block_flag = false;


	m_block_num = 0;
}

void CNextBlock::Action()
{
	//マップオブジェクト取得
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);
	//ブロックオブジェクト取得
	Cblock* obj_block = (Cblock*)Objs::GetObj(OBJ_BLOCK);

	//ブロッククラスのm_block_fall_okを持ってくる
	generate_block_flag = obj_block->Getblock_fall();

	//FreezeBlock_Generateの戻り値をとってくる
	int freeze_time = obj_map->FreezeBlock_Generate();
	
	//freeze_timeがじゃなかったら
	if (freeze_time != 0)
	{
		//freeze_timeに代入する
		freeze_block_late = freeze_time;
	}

	//下に落ちた時のフラグがtrueなら
	if (generate_block_flag == true)
	{
		//freeze_block_lateが0じゃなかったら
		if (freeze_block_late > 0)
		{
			//1減らす
			freeze_block_late--;
		}
		else
		{
			//ブロックの数値を決める
			m_block_num = rand() % 6;

			//新しく降らせる・数値も渡す
			Cblock* p_block = new Cblock(m_block_num);
			Objs::InsertObj(p_block, OBJ_BLOCK, 1);

			//落下フラグを変える
			generate_block_flag = false;
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
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	Draw::Draw(15, &src, &dst, c, 0);
}