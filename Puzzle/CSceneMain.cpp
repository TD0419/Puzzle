//STLデバック機能をOFFする
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "CSceneMain.h"
#include "GameHead.h"

#include <vector>
#include "GameL/WinInputs.h"
#include "GameL/NetWork.h"


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
	// グラフィック読み込み
	LoadGraphic();

	// サウンド読み込み
	LoadAudio();

	//マップオブジェクト読み込み
	CMap* p_map = new CMap(0);
	Objs::InsertObj(p_map, OBJ_MAP, 1);

	CMap* p_map_2 = new CMap(620);
	Objs::InsertObj(p_map_2, OBJ_MAP_PLAY2, 1);
}

//実行中メソッド
void CSceneMain::Scene()
{
	
}

// 画像読み込み
void CSceneMain::LoadGraphic()
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

	Draw::LoadImageW(L"Effect1_1.png", 11, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_2.png", 12, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_3.png", 13, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_4.png", 14, TEX_SIZE_512);

	Draw::LoadImageW(L"next_block_space.png", 15, TEX_SIZE_64);

	Draw::LoadImageW(L"Cross.png", 16, TEX_SIZE_32);
}

// 音楽読み込み
void CSceneMain::LoadAudio()
{
	Audio::LoadAudio(0, L"Effect_SE.wav", EFFECT);

	Audio::LoadAudio(1, L"Game_BGM.wav", BACK_MUSIC);

	// ゲームBGMを流す
	Audio::Start(1);
}