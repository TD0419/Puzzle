//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "CNextBlock.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CNextBlock::Init()
{
	m_Px = 608.0f;
	m_Py = 0.0f;

	m_block_num = rand() % 6;
}

void CNextBlock::Action()
{

}

void CNextBlock::Draw()
{
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = 0.0f + m_Py;
	dst.m_left = 0.0f + m_Px;
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	Draw::Draw(15, &src, &dst, c, 0);
}