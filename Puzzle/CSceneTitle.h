#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

// シーン : タイトル画面
class CSceneTitle : public CScene
{
public:
	CSceneTitle();
	~CSceneTitle();
	void InitScene();//初期化メソッド
	void Scene();	 //実行中メソッド
private:
};