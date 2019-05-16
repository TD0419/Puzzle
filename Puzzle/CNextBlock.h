#pragma once

//�g�p����w�b�_�[�t�@�C��
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���̃u���b�N�\��
class CNextBlock : public CObj
{
	public:
		CNextBlock(float a,int b);
		//CNextBlock() {};
		~CNextBlock() {};
		void Init();
		void Action();
		void Draw();
		void Setblock_fall(bool a) { m_generate_block_flag = a; }

	private:
		float m_Px;
		float m_Py;

		bool m_generate_block_flag;

		int m_block_num;
		int m_freeze_block_late;
		int m_map_LR_judg;
};