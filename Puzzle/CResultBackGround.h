#pragma once

// 使用するヘッダー
#include"GameL/SceneObjManager.h"
#include "CMap.h"

// 使用するネームスペース
using namespace GameL;

// クラスオブジェクト：リザルト画面背景
class CResultBackGround : public CObj
{
public:
	CResultBackGround(CMap* CMap);
	~CResultBackGround() {};
	void Init();
	void Action();
	void Draw();

private:
	CMap* m_pMap;
	int m_objname;
};