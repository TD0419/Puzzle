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
CSceneResult::CSceneResult(CMap* CMap)
{
	m_pMap = CMap;
}

//デストラクタ
CSceneResult::~CSceneResult()
{

}

//初期化メソッド
void CSceneResult::InitScene()
{
	// 背景画像
	Draw::LoadImageW(L"Result.jpg", 0, TEX_SIZE_512);

	// リザルト画面背景オブジェクト
	CResultBackGround* pResultBackGround = new CResultBackGround(m_pMap);
	Objs::InsertObj(pResultBackGround, OBJ_RESULT_BACK_GROUND, 0);

	Audio::LoadAudio(0, L"Decision_SE.wav", EFFECT);

	Audio::LoadAudio(1, L"Result_BGM.wav", BACK_MUSIC);

	// リザルトBGMを流す
	Audio::Start(1);
}

//実行中メソッド
void CSceneResult::Scene()
{

}