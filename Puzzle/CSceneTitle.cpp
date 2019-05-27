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
	// 背景画像
	Draw::LoadImageW(L"Title.jpg", 0, TEX_SIZE_512);

	// タイトル背景オブジェクト
	CTitleBackGround* pTitleBackGround = new CTitleBackGround;
	Objs::InsertObj(pTitleBackGround, OBJ_TITLE_BACK_GROUND, 0);

	Audio::LoadAudio(0, L"Decision_SE.wav", EFFECT);
	
	Audio::LoadAudio(1, L"Title_BGM.wav", BACK_MUSIC);

	// タイトルBGMを流す
	Audio::Start(1);
}

//実行中メソッド
void CSceneTitle::Scene()
{

}