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
CSceneConnect::CSceneConnect()
{

}

//デストラクタ
CSceneConnect::~CSceneConnect()
{

}

//初期化メソッド
void CSceneConnect::InitScene()
{
	// 背景オブジェクトの代わりの画像(差し換えてください(涙))
	Draw::LoadImageW(L"block.png", 0, TEX_SIZE_32);

	// ネットワーク接続画面背景オブジェクト
	CConnectBackGround* pConnectBackGround = new CConnectBackGround;
	Objs::InsertObj(pConnectBackGround, OBJ_RESULT_BACK_GROUND, 0);
}

//実行中メソッド
void CSceneConnect::Scene()
{

}