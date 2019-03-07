#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

// シーン : リザルト画面
class CSceneResult : public CScene
{
public:
	CSceneResult();
	~CSceneResult();
	void InitScene();//初期化メソッド
	void Scene();	 //実行中メソッド
private:
};