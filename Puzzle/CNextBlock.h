#pragma once

//�g�p����w�b�_�[�t�@�C��
#include "GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���̃u���b�N�\��
class CNextBlock : public CObj
{
	public:
		CNextBlock() {};
		~CNextBlock() {};
		void Init();
		void Action();
		void Draw();
		void Setblock_fall(bool a) { a = generate_block_flag; };

	private:
		float m_Px;
		float m_Py;

		bool generate_block_flag;

		int m_block_num;
		int freeze_block_late;
};