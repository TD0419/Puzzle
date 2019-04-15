#pragma once

// 使用するヘッダー
#include"GameL/SceneObjManager.h"

// 使用するネームスペース
using namespace GameL;

// クラスオブジェクト：ネットワーク接続画面背景
class CConnectBackGround : public CObj
{
public:
	CConnectBackGround() {};
	~CConnectBackGround() {};
	void Init();
	void Action();
	void Draw();
};