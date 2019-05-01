#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"
#include "GameL\NetWork.h"

//使用するネームスペース
using namespace GameL;

// シーン : ネットワーク接続画面
class CSceneConnect : public CScene
{
public:
	CSceneConnect(ConnectKind connectkind);
	~CSceneConnect() {}
	void InitScene();//初期化メソッド
	void Scene();	 //実行中メソッド
private:
};