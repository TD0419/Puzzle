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

	m_block_num = rand() % 6;
}

void CNextBlock::Action()
{

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