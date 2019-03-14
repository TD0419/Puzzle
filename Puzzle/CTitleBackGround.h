#pragma once

// 使用するヘッダー
#include"GameL/SceneObjManager.h"

// 使用するネームスペース
using namespace GameL;

// クラスオブジェクト：タイトル背景
class CTitleBackGround : public CObj
{
public:
	CTitleBackGround() {};
	~CTitleBackGround() {};
	void Init();
	void Action();
	void Draw();
};