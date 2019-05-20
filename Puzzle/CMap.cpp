//使用するヘッダーファイル
#include "CMap.h"
#include "GameL/SceneObjManager.h"
#include "GameHead.h"

#include "CEffect.h"

//使用するネームスペース
using namespace GameL;


CMap::CMap(float a)
{
	m_shift_x = MAP_SHIFT_X + a;
	nextblock_class_pos = a;

	CNextBlock* m_nextblockclass = new CNextBlock(nextblock_class_pos, this);
	Objs::InsertObj(m_nextblockclass, OBJ_NEXT_BLOCK, 1);

	//ブロックオブジェクト読み込み
	Cblock* p_block = new Cblock(100, m_shift_x + (MAP_X * 32.0f / 2), m_nextblockclass, this);
	Objs::InsertObj(p_block, OBJ_BLOCK, 1);
}

void CMap::Init()
{
	int map[MAP_Y][MAP_X] =
	{
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99,99,99,99,99,99,99,99,99,99,99, 99},
	};

	memcpy(m_map, map, sizeof(int) * MAP_Y * MAP_X);

	freezeblock_num = 0;
	delete_freezeblock = 0;
}

void CMap::Action()
{
	//// TCPでのデータの受け渡し方法の例
	//if (NetWork::GetConnectKind() == NetWork::ConnectKind::Server)
	//{
	//	int data = 100;
	//	NetWork::Send((char*)&data, sizeof(data));
	//}
	//else if(NetWork::GetConnectKind() == NetWork::ConnectKind::Client)
	//{
	//	int data = 0;
	//	RecvState State = NetWork::Recv((char*)&data, sizeof(data));

	//	// 切断されていないかの確認
	//	if (State == RecvState::Connect_Cut)
	//	{
	//		// 切断された
	//		// タイトルに戻す
	//		Scene::SetScene(new CSceneTitle);
	//	}
	//}
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
			dst.m_top = MAP_SHIFT_Y + y * 32.0f;
			dst.m_left = m_shift_x + x * 32.0f;
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
	//ここで使う関数
	bool right_delete_check = true;
	bool left_delete_check = true;

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
		//1つ下または、２つ下がマップ外の時、強制的にループを抜ける
		if (m_map[y + 1][x] == 99 || m_map[y + 2][x] == 99)
		{
			break;
		}

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
					//１マス上方向にお邪魔ブロックがあれば
					if (m_map[(y + m_del_under) - 1][x] == 8)
					{
						delete_freezeblock += 1;

						m_map[(y + m_del_under) - 1][x] = 0;
					}

					//１マス下方向にお邪魔ブロックがあれば
					if (m_map[(y + m_del_under) + 1][x] == 8)
					{
						delete_freezeblock += 1;

						m_map[(y + m_del_under) + 1][x] = 0;
					}

					//１マス左方向にお邪魔ブロックがあれば
					if (m_map[y + m_del_under][x - 1] == 8)
					{
						delete_freezeblock += 1;

						m_map[y + m_del_under][x - 1] = 0;
					}

					//１マス右方向にお邪魔ブロックがあれば
					if (m_map[y + m_del_under][x + 1] == 8)
					{
						delete_freezeblock += 1;

						m_map[y + m_del_under][x + 1] = 0;
					}


					m_map[y + m_del_under][x] = 0;

					freezeblock_num += 1;
				}
			}

			// エフェクトの表示位置
			RECT_F dst;
			dst.m_top = MAP_SHIFT_Y + y * 32.f;
			dst.m_left = m_shift_x + x * 32.f;
			dst.m_right = dst.m_left + 32.f;
			dst.m_bottom = MAP_SHIFT_Y + (y + m_search_under + 1) * 32.f;

			// エフェクトの生成
			CreateEffect(dst, 90.f);

			break;//同じ色の星型ブロックが消える条件下にあった場合、遠いほうを消えないようにするために脱出
		}
	}

	//置いたとこから右方向に調べる
	//m_search_right・・・同じブロックがあるかの検索、値の設定
	//m_del_right・・・ブロックを消すために回すfor文の変数
	//5つ先までを検索
	for (int m_search_right = 2; m_search_right < 5; m_search_right++)
	{
		//1つ右または、２つ右がマップ外の時、強制的にループを抜ける
		if (m_map[y][x + 1] == 99 || m_map[y][x + 2] == 99)
		{
			break;
		}

		//同じやつがあれば
		if (m_map[y][x + m_search_right] == id)
		{
			for (int a = 1; a < m_search_right; a++)
			{
				//検索先に空白（ブロックがない）なら全部消さない
				if (m_map[y][x + a] == 0)
				{
					right_delete_check = false;
					//break;//ループ脱出
				}
			}

			if (right_delete_check == true)
			{
				//あった場所までのブロックを消す
				for (int m_del_right = 0; m_del_right <= m_search_right; m_del_right++)
				{
					//途中に色の違う星ブロックがあれば
					if (m_map[y][x + m_del_right] >= 4 && m_map[y][x + m_del_right] != id)
					{
						;//スルー
					}
					else
					{
						//１マス上方向にお邪魔ブロックがあれば
						if (m_map[y - 1][x + m_del_right] == 8)
						{
							delete_freezeblock += 1;

							m_map[y - 1][x + m_del_right] = 0;
						}

						//１マス下方向にお邪魔ブロックがあれば
						if (m_map[y + 1][x + m_del_right] == 8)
						{
							delete_freezeblock += 1;

							m_map[y + 1][x + m_del_right] = 0;
						}

						//１マス左方向にお邪魔ブロックがあれば
						if (m_map[y][(x + m_del_right) - 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x + m_del_right) - 1] = 0;
						}

						//１マス右方向にお邪魔ブロックがあれば
						if (m_map[y][(x + m_del_right) + 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x + m_del_right) + 1] = 0;
						}

						m_map[y][x + m_del_right] = 0;

						freezeblock_num += 1;

					}
				}
			}
			// エフェクトの表示位置を設定
			RECT_F dst;
			dst.m_top = MAP_SHIFT_Y + y * 32.f;
			dst.m_left = m_shift_x + x * 32.f;
			dst.m_right = m_shift_x + (x + m_search_right + 1) * 32.f;
			dst.m_bottom = dst.m_top + 32.f;

			// エフェクトを生成
			CreateEffect(dst, 180.f);

			break;//同じ色の星型ブロックが消える条件下にあった場合、遠いほうを消えないようにするために脱出
		}
	}

	//置いたとこから左方向に調べる
	//m_search_left・・・同じブロックがあるかの検索、値の設定
	//m_del_left・・・ブロックを消すために回すfor文の変数
	//5つ先までを検索
	for (int m_search_left = 2; m_search_left < 5; m_search_left++)
	{
		//1つ左または、２つ左がマップ外の時、強制的にループを抜ける
		if (m_map[y][x - 1] == 99 || m_map[y][x - 2] == 99)
		{
			break;
		}

		//同じやつがあれば
		if (m_map[y][x - m_search_left] == id)
		{
			for (int a = 1; a < m_search_left; a++)
			{
				//検索先に空白（ブロックがない）なら全部消さない
				if (m_map[y][x - a] == 0)
				{
					left_delete_check = false;
					//break;//ループ脱出
				}
			}

			if (left_delete_check == true)
			{
				//あった場所までのブロックを消す
				for (int m_del_left = 0; m_del_left <= m_search_left; m_del_left++)
				{
					//途中に色の違う星ブロックがあれば
					if (m_map[y][x - m_del_left] >= 4 && m_map[y][x - m_del_left] != id)
					{
						;
					}
					else
					{
						//１マス上方向にお邪魔ブロックがあれば
						if (m_map[y - 1][x - m_del_left] == 8)
						{
							delete_freezeblock += 1;

							m_map[y - 1][x - m_del_left] = 0;
						}

						//１マス下方向にお邪魔ブロックがあれば
						if (m_map[y + 1][x - m_del_left] == 8)
						{
							delete_freezeblock += 1;

							m_map[y + 1][x - m_del_left] = 0;
						}

						//１マス左方向にお邪魔ブロックがあれば
						if (m_map[y][(x - m_del_left) - 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x - m_del_left) - 1] = 0;
						}

						//１マス右方向にお邪魔ブロックがあれば
						if (m_map[y][(x - m_del_left) + 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x - m_del_left) + 1] = 0;
						}

						m_map[y][x - m_del_left] = 0;

						freezeblock_num += 1;
					}
				}
			}

			// エフェクトの表示位置を設定
			RECT_F dst;
			dst.m_top = MAP_SHIFT_Y + y * 32.f;
			dst.m_left = m_shift_x + (x - m_search_left) * 32.f;
			dst.m_right = m_shift_x + (x + 1) * 32.f;
			dst.m_bottom = dst.m_top + 32.f;

			// エフェクトを生成
			CreateEffect(dst, 0.f);

			break;//同じ色の星型ブロックが消える条件下にあった場合、遠いほうを消えないようにするために脱出
		}
	}

	freezeblock_num += delete_freezeblock / 2;//お邪魔ブロック生成の総数に消えたお邪魔ブロックの半数を追加する

	delete_freezeblock = 0;
	
	return;
}

bool CMap::FreezeBlock_Check()
{
	//if (freezeblock_num != 0)
	//{
	//	return true;
	//}

	return false;
}

//お邪魔ブロック生成
int CMap::FreezeBlock_Generate()
{
	//お邪魔ブロックが沸いた下のブロックがどこにあるか調べる用関数
	int y_num = 0;

	//お邪魔ブロックの数が０じゃなかったら
	if (freezeblock_num != 0)
	{
		//お邪魔ブロックの数分回す
		for (int freeze_x = 0; freeze_x < freezeblock_num; freeze_x++)
		{
			//下列にある一番上のブロックの位置を調べる
			for (int y = 0; y < 18; y++)
			{
				if (m_map[y][freeze_x + 1] != 0)
				{
					if (y_num < y)
					{
						//今までの数字より大きいならそれにする
						y_num = y;

						break;
					}
				}
			}

			//お邪魔ブロック出現
			CFreezeblock* p_fblock = new CFreezeblock(freeze_x + 1,0,8);
			Objs::InsertObj(p_fblock, OBJ_FREEZE_BLOCK, 1);

		}

		//お邪魔ブロックの数をなくす
		freezeblock_num = 0;
	}

	//お邪魔ブロックが落下するフレーム数を返す
	return y_num * 32 / 4;
}

// エフェクトを生成する
// 引数1 RECT_F : エフェクトの表示位置
// 引数2 float  : エフェクトの角度(度数法)
void CMap::CreateEffect(RECT_F dst, float fRotation)
{
	// エフェクトの切り取り位置
	RECT_F src;
	src.m_top = 0.f;
	src.m_left = 0.f;
	src.m_right = 512.f;
	src.m_bottom = 512.f;
	float fWhiteColor[4] = { 1.f,1.f,1.f,1.f };			// 白色
	float fTranslucentColor[4] = { 1.f,1.f,1.f,0.5f };  // 半透明

	// エフェクトを表示するシステム
	CEffectSystem* pEffectSystem = new CEffectSystem(new CExEffect(11, &src, &dst, 15, fTranslucentColor, fWhiteColor, fRotation));
	CSceneObjManager::InsertObj(pEffectSystem, 100, 10);
	// 次に表示したいエフェクトを追加
	pEffectSystem->AddNextEffect(new CExEffect(12, &src, &dst, 20, fWhiteColor, fWhiteColor, fRotation));
	pEffectSystem->AddNextEffect(new CExEffect(13, &src, &dst, 15, fWhiteColor, fTranslucentColor, fRotation));
}