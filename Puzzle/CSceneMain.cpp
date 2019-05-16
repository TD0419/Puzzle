//STLデバック機能をOFFする
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "CSceneMain.h"
#include "GameHead.h"

#include <vector>

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{
	
}

//初期化メソッド
void CSceneMain::InitScene()
{
	//グラフィック読み込み
	//ここでエラーが出たのでLoadImageWのwchar_t*にconstをつけて確かめた
	//後々修正が必要
	Draw::LoadImageW(L"orange_block.png", 0, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_block.png", 1, TEX_SIZE_32);

	Draw::LoadImageW(L"yellow_block.png", 2, TEX_SIZE_32);

	Draw::LoadImageW(L"orange_star_block.png", 3, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_star_block.png", 4, TEX_SIZE_32);

	Draw::LoadImageW(L"yellow_star_block.png", 5, TEX_SIZE_32);

	Draw::LoadImageW(L"freeze_block.png", 8, TEX_SIZE_32);
	
	Draw::LoadImageW(L"side_block.png", 10, TEX_SIZE_32);

	Draw::LoadImageW(L"TestEffect.png", 11, TEX_SIZE_64);

	Draw::LoadImageW(L"next_block_space.png", 15, TEX_SIZE_64);

	//ブロックオブジェクト読み込み
	Cblock* p_block = new Cblock(100,LEFT_MAP);
	Objs::InsertObj(p_block, OBJ_BLOCK, 1);

	Cblock* p_block_2 = new Cblock(100, RIGHT_MAP);
	Objs::InsertObj(p_block_2, OBJ_BLOCK_2, 1);

	//マップオブジェクト読み込み
	CMap* p_map = new CMap(0);
	Objs::InsertObj(p_map, OBJ_MAP, 1);

	CMap* p_map_2 = new CMap(620);
	Objs::InsertObj(p_map_2, OBJ_MAP_PLAY2, 1);

	//CNextBlock* p_next = new CNextBlock(0);
	//Objs::InsertObj(p_next, OBJ_NEXT_BLOCK, 1);

	//CNextBlock* p_next_2 = new CNextBlock(620);
	//Objs::InsertObj(p_next_2, OBJ_NEXT_BLOCK_2, 1);
}

//実行中メソッド
void CSceneMain::Scene()
{
	
}