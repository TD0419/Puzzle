#pragma once

//使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"

//使用するネームスペース
using namespace GameL;

//定数
#define MAP_Y 18
#define MAP_X 12

#define MAP_SHIFT_X 96.0f
#define MAP_SHIFT_Y 192.0f

#define LEFT_MAP 1000
#define RIGHT_MAP 2000

struct SendAndReceive
{
	// 
};

//オブジェクト：マップ
class CMap : public CObj
{
	public:
		CMap(float a);
		//CMap() {};
		~CMap() {};
		void Init();
		void Action();
		void Draw();
		int GetMap(int x, int y);
		void SetMap(int x, int y, int id);
		void confirmblock(int x, int y, int id);
		int FreezeBlock_Generate();
		bool FreezeBlock_Check();
		float GetShiftX() { return m_shift_x; }

	private:
		void CreateEffect(RECT_F dst, float fRotation);

	private:
		int m_map[MAP_Y][MAP_X];
		float m_shift_x;
		float nextblock_class_pos;

		int freezeblock_num;
		int delete_freezeblock;

		int m_mapLR_judg;

		//CNextBlock* m_nextblockclass;
};