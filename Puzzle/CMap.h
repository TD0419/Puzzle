#pragma once

//使用するヘッダー
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//定数
#define MAP_Y 18
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
		int GetMap(int x, int y);
		void SetMap(int x, int y, int id);
		void confirmblock(int x, int y, int id);

	private:
		int m_map[MAP_Y][MAP_X];

};