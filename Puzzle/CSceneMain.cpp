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
	Draw::LoadImageW(L"block.png", 0, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_block.png", 1, TEX_SIZE_32);
	
	Draw::LoadImageW(L"side_block.png", 2, TEX_SIZE_32);

	//ブロックオブジェクト読み込み
	Cblock* p_block = new Cblock();
	Objs::InsertObj(p_block, OBJ_BLOCK, 1);

	//マップオブジェクト読み込み
	CMap* p_map = new CMap();
	Objs::InsertObj(p_map, OBJ_MAP, 1);
}

//実行中メソッド
void CSceneMain::Scene()
{
	
}