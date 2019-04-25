#pragma once

//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�I�u�W�F�N�g�F���ז�(�����Ă�)�u���b�N
class CFreezeblock : public CObj
{
	public:
		CFreezeblock(int x,int y,int id);
		~CFreezeblock() {};
		void Init();
		void Action();
		void Draw();

	private:
		float m_fPx;
		float m_fPy;
		float m_fVx;
		float m_fVy;

		bool m_bStop_flag;//�u���b�N��~�t���O

		int m_bColornum;//�u���b�N�̐F
		int m_elementX_storage;//�u���b�N�̗v�f�ԍ�X�̕ۑ�
		int m_elementY_storage;//�u���b�N�̗v�f�ԍ�Y�̕ۑ�
};