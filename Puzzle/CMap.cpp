//使用するヘッダーファイル
#include "CMap.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameHead.h"

#include "CEffect.h"

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
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99,99},
	};

	memcpy(m_map, map, sizeof(int) * MAP_Y * MAP_X);

	//// エフェクト使用例
	//RECT_F src, dst, dst2;
	//src.m_top = 0.f;
	//src.m_left = 0.f;
	//src.m_right = 64.f;
	//src.m_bottom = 64.f;
	//dst.m_top = 32.f;
	//dst.m_left = 32.f;
	//dst.m_right = 64.f;
	//dst.m_bottom = 64.f;
	//dst2.m_top = 0.f;
	//dst2.m_left = 0.f;
	//dst2.m_right = 96.f;
	//dst2.m_bottom = 96.f;
	//float c1[4] = { 1.f,1.f,1.f,0.5f };
	//float c2[4] = { 1.f,1.f,1.f,1.f };
	//float c3[4] = { 1.f,1.f,1.f,0.f };
	//// エフェクトを表示するシステム
	//CEffectSystem* pEffectSystem = new CEffectSystem(new CExEffect(11, &src, &dst, 50, c1, c2, &dst2));
	//CSceneObjManager::InsertObj(pEffectSystem, 100, 10);
	//// 次に表示したいエフェクトを追加
	//pEffectSystem->AddNextEffect(new CExEffect(11, &src, &dst2, 10, c2, c3));
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
				Draw::Draw(10, &src, &dst, c, 0.0f);
			}
		}
	}
}


//移動できるようにx,yの値が正しい値か調べる関数
int CMap::GetMap(int x, int y)
{
	//x,yが例外な値の場合、-1を返す
	if (x < 0)
	{
		return -1;
	}

	if (y < 0)
	{
		return -1;
	}

	if (x >= MAP_X)
	{
		return -1;
	}

	if (y >= MAP_Y)
	{
		return -1;
	}

	//要素を返す
	return m_map[y][x];
}

//動かなくなったブロックをマップに格納する関数
void CMap::SetMap(int x, int y, int id)
{
	//x,yが例外な値の場合、-1を返す
	if (x < 0)
	{
		return ;
	}

	if (y < 0)
	{
		return ;
	}

	if (x >= MAP_X)
	{
		return ;
	}

	if (y >= MAP_Y)
	{
		return ;
	}

	m_map[y][x] = id;

	return;
}

//右・左・下に同じブロックがあるか調べる
void CMap::confirmblock(int x, int y, int id)
{
	//ブロックが星型じゃなかったら
	if (id <= 3)
	{
		return;//調べず終了
	}

	//置いたとこから下方向に調べる
	//m_search_under・・・同じブロックがあるかの検索、値の設定
	//m_del_under・・・ブロックを消すために回すfor文の変数
	//5つ先までを検索
	for (int m_search_under = 2; m_search_under < 5; m_search_under++)
	{
		//同じやつがあれば
		if (m_map[y + m_search_under][x] == id)
		{
			//あった場所までのブロックを消す
			for (int m_del_under = 0; m_del_under <= m_search_under; m_del_under++)
			{
				//途中に色の違う星ブロックがあれば
				if (m_map[y + m_del_under][x] >= 4 && m_map[y + m_del_under][x] != id)
				{
					;//スルー
				}
				else
				{
					m_map[y + m_del_under][x] = 0;
				}
			}

			break;//2つ以上あった場合、消えないようにするために脱出
		}
	}

	//置いたとこから右方向に調べる
	//m_search_right・・・同じブロックがあるかの検索、値の設定
	//m_del_right・・・ブロックを消すために回すfor文の変数
	//5つ先までを検索
	for (int m_search_right = 2; m_search_right < 5; m_search_right++)
	{
		//同じやつがあれば
		if (m_map[y][x + m_search_right] == id)
		{
			//あった場所までのブロックを消す
			for (int m_del_right = 0; m_del_right <= m_search_right; m_del_right++)
			{
				//検索先に空白（ブロックがない）なら全部消さない
				if (m_map[y][x + m_del_right + 1] == 0 || m_map[y][x + m_del_right + 2] == 0 || m_map[y][x + m_del_right + 3] == 0)
				{
					break;//ループ脱出
				}

				//途中に色の違う星ブロックがあれば
				if (m_map[y][x + m_del_right] >= 4 && m_map[y][x + m_del_right] != id)
				{
					;//スルー
				}
				else
				{
					m_map[y][x + m_del_right] = 0;
				}
			}

			break;//2つ以上あった場合、消えないようにするために脱出
		}
	}

	//置いたとこから左方向に調べる
	//m_search_left・・・同じブロックがあるかの検索、値の設定
	//m_del_left・・・ブロックを消すために回すfor文の変数
	//5つ先までを検索
	for (int m_search_left = 2; m_search_left < 5; m_search_left++)
	{
		//同じやつがあれば
		if (m_map[y][x - m_search_left] == id)
		{
			//あった場所までのブロックを消す
			for (int m_del_left = 0; m_del_left <= m_search_left; m_del_left++)
			{
				//検索先に空白（ブロックがない）なら全部消さない
				if (m_map[y][x - m_del_left - 1] == 0 || m_map[y][x - m_del_left - 2] == 0 || m_map[y][x - m_del_left - 3] == 0)
				{
					break;//ループ脱出
				}

				//途中に色の違う星ブロックがあれば
				if (m_map[y][x - m_del_left] >= 4 && m_map[y][x - m_del_left] != id)
				{
					;
				}
				else
				{
					m_map[y][x - m_del_left] = 0;
				}
			}

			break;//2つ以上あった場合、消えないようにするために脱出
		}
	}

	return;
}