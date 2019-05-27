//STLデバック機能をOFFする
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\NetWork.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "GameHead.h"

// 引数1 ConnectKind : クライアントorサーバー
CSceneConnect::CSceneConnect(NetWork::ConnectKind connectkind)
{
	// ネットワーク情報初期化
	NetWork::Init(connectkind);
}

//初期化メソッド
void CSceneConnect::InitScene()
{
	// 背景画像
	Draw::LoadImageW(L"ConnectBackGround.jpg", 0, TEX_SIZE_512);

	// ネットワーク接続画面背景オブジェクト
	CConnectBackGround* pConnectBackGround = new CConnectBackGround;
	Objs::InsertObj(pConnectBackGround, OBJ_RESULT_BACK_GROUND, 0);

	Audio::LoadAudio(0, L"Decision_SE.wav", EFFECT);
	Audio::LoadAudio(1, L"return_SE.wav", EFFECT);

	Audio::LoadAudio(2, L"Connect_BGM.wav", BACK_MUSIC);

	// ネットワーク接続画面BGMを流す
	Audio::Start(2);
}

//実行中メソッド
void CSceneConnect::Scene()
{
	
}