//STLデバック機能をOFFする
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"

//コンストラクタ
CSceneTitle::CSceneTitle()
{

}

//デストラクタ
CSceneTitle::~CSceneTitle()
{

}

//初期化メソッド
void CSceneTitle::InitScene()
{
	// 背景オブジェクトの代わりの画像(差し換えてください(涙))
	//Draw::LoadImageW(L"block.png", 0, TEX_SIZE_32);

	// タイトル背景オブジェクト
	CTitleBackGround* pTitleBackGround = new CTitleBackGround;
	Objs::InsertObj(pTitleBackGround, OBJ_TITLE_BACK_GROUND, 0);
}

//実行中メソッド
void CSceneTitle::Scene()
{

}