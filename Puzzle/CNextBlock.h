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

	private:
		float m_Px;
		float m_Py;

		int m_block_num;
};