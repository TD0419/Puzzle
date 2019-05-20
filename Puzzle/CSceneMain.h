#pragma once
//使用するヘッダーファイル
#include "GameL\SceneManager.h"

//使用するネームスペース
using namespace GameL;

// シーン : ゲーム画面
class CSceneMain : public CScene
{
	public:
		CSceneMain();
		~CSceneMain();
		void InitScene();//初期化メソッド
		void Scene();	 //実行中メソッド
	private:
		void LoadGraphic(); // 画像読み込み
		void LoadAudio();	// 音楽読み込み
};