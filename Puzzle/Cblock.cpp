//�g�p����w�b�_�[�t�@�C��
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneManager.h"
#include"GameL/WinInputs.h"
#include"GameL/SetWindow.h"
#include"GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void Cblock::Init()
{
	m_fPx = 416.0f;
	m_fPy = 32.0f;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bColornum = rand() % 2;

	m_bStop_flag = false;
}

//�A�N�V����
void Cblock::Action()
{
	//��~�Ȃ�
	if (m_bStop_flag == true)
	{
		return;
	}


	//�ړ��x�N�g��������
	m_fVy = 3.0f;
	m_fVx = 0.0f;

	//A����������
	// XBOX�R�� �g�p�� if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		if (m_fPx - 32.0f <= 160.0f)
		{
			;
		}
		else
		{
			m_fVx = -32.0f;//���ɓ���
		}
	}
	//D����������
	else if (Input::GetVKey('D') == true)
	{
		if (m_fPx + 32.0f >= 576.0f)
		{
			;
		}
		else
		{
			m_fVx = 32.0f;//�E�ɓ���
		}
	}

	//�ړ��x�N�g�����Z
	m_fPx += m_fVx;
	m_fPy += m_fVy;

	//�u���b�N����ԉ��ɒ�������~�߂�
	if (m_fPy == (float)Window::GetHeight() - 32.0f)
	{
		m_fVy = 0.0f;
		m_fVx = 0.0f;

		m_bStop_flag = true;

		//�V�����~�点��
		Cblock* p_block = new Cblock();
		Objs::InsertObj(p_block, OBJ_BLOCK, 1);
	}



}

//�h���[
void Cblock::Draw()
{
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	dst.m_top = 0.0f + m_fPy;
	dst.m_left = 0.0f + m_fPx;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	if (m_bColornum == 0)
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);
	}

	else if (m_bColornum == 1)
	{
		Draw::Draw(1, &src, &dst, c, 0.0f);
	}
}