#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

// シーン : ネットワーク接続画面
class CSceneConnect : public CScene
{
public:
	CSceneConnect();
	~CSceneConnect();
	void InitScene();//初期化メソッド
	void Scene();	 //実行中メソッド
private:
};