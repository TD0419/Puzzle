#pragma once

//�g�p����w�b�_�[
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�萔
#define MAP_Y 18
#define MAP_X 14

//�I�u�W�F�N�g�F�}�b�v
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