#pragma once

//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

#include "CNextBlock.h"
#include "CMap.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�N���X�I�u�W�F�N�g�F�u���b�N
class Cblock : public CObj
{
	public:
		Cblock(int num,float fPosX, CNextBlock* pNextBlock, CMap* pMap);
		~Cblock() {};
		void Init();
		void Action();
		void Draw();
		bool Getblock_fall() { return m_block_fall_ok; };

		// �ړ�����
		void Move(int nKey_Code);

	protected:
		float m_fPx;//�ʒuX
		float m_fPy;//�ʒuY
		float m_fVx;//X�x�N�g��
		float m_fVy;//Y�x�N�g��

		bool m_bStop_flag;//�u���b�N��~�t���O
		bool m_Again_fall_on;
		bool m_block_fall_ok;

		int m_bColornum;//�u���b�N�̐F
		int m_elementX_storage;//�u���b�N�̗v�f�ԍ�X�̕ۑ�
		int m_elementY_storage;//�u���b�N�̗v�f�ԍ�Y�̕ۑ�

		CNextBlock* m_pNextBlock;
		CMap*		m_pMap;
};