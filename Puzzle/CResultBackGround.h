#pragma once

// 使用するヘッダー
#include"GameL/SceneObjManager.h"

// 使用するネームスペース
using namespace GameL;

// クラスオブジェクト：リザルト画面背景
class CResultBackGround : public CObj
{
public:
	CResultBackGround() {};
	~CResultBackGround() {};
	void Init();
	void Action();
	void Draw();
};