//使用するヘッダーファイル
#include "CMap.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameHead.h"

//使用するネームスペース
using namespace GameL;

void CMap::Init()
{
	int map[MAP_Y][MAP_X] =
	{
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99,99},
	};

	memcpy(m_map, map, sizeof(int) * MAP_Y * MAP_X);
}

void CMap::Action()
{


}

void CMap::Draw()
{
	//カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;
	RECT_F dst;

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			dst.m_top = 0.0f + y * 32.0f;
			dst.m_left = 160.0f + x * 32.0f;
			dst.m_right = dst.m_left + 32.0f;
			dst.m_bottom = dst.m_top + 32.0f;

			if (m_map[y][x] == 99)
			{
				Draw::Draw(2, &src, &dst, c, 0.0f);
			}
		}
	}
}