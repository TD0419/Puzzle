#pragma once

//�g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�N���X�I�u�W�F�N�g�F�u���b�N
class Cblock : public CObj
{
	public:
		Cblock() {};
		~Cblock() {};
		void Init();
		void Action();
		void Draw();
	private:
		float m_fPx;//�ʒuX
		float m_fPy;//�ʒuY
		float m_fVx;//X�x�N�g��
		float m_fVy;//Y�x�N�g��

		bool m_bStop_flag;//�u���b�N��~�t���O
		bool m_a_key_push;//a�L�[�̒��������͖h�~�t���O
		bool m_d_key_push;//d�L�[�̒��������͖h�~�t���O

		int m_bColornum;//�u���b�N�̐F
};