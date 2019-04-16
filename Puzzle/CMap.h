#pragma once

//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define MAP_Y 13
#define MAP_X 14

//オブジェクト：マップ
class CMap : public CObj
{
	public:
		CMap() {};
		~CMap() {};
		void Init();
		void Action();
		void Draw();


	private:
		int m_map[MAP_Y][MAP_X];

};