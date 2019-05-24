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
	// 背景オブジェクトの代わりの画像(差し換えてください(涙))
	Draw::LoadImageW(L"side_block.png", 0, TEX_SIZE_32);

	// リザルト画面背景オブジェクト
	CResultBackGround* pResultBackGround = new CResultBackGround(m_pMap);
	Objs::InsertObj(pResultBackGround, OBJ_RESULT_BACK_GROUND, 0);

	Audio::LoadAudio(0, L"Asset\\Sound\\Decision.wav", EFFECT);
}

//実行中メソッド
void CSceneResult::Scene()
{

}