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
	m_fPx = 400.0f;
	m_fPy = 32.0f;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bStop_flag = false;
}

//�A�N�V����
void Cblock::Action()
{
	//�ړ��x�N�g��������
	m_fVy = 3.0f;
	m_fVx = 0.0f;

	//A����������
	// XBOX�R�� �g�p�� if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		m_fVx = -3.0f;//���ɓ���
	}
	//D����������
	else if (Input::GetVKey('D') == true)
	{
		m_fVx = 3.0f;//�E�ɓ���
	}

	//�u���b�N����ԉ��ɒ�������~�߂�
	if (m_fPy == (float)Window::GetHeight() - 32.0f)
	{
		m_fVy = 0.0f;
		m_fVx = 0.0f;

		m_bStop_flag = true;
	}

	//�ړ��x�N�g�����Z
	m_fPx += m_fVx;
	m_fPy += m_fVy;

	//������������R�����g�A�E�g
	//if (m_bStop_flag == true)
	//{
	//	m_bStop_flag = false;

	//	//�V�����~�点��
	//	Cblock* p_block = new Cblock();
	//	Objs::InsertObj(p_block, OBJ_BLOCK, 1);
	//}
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

	Draw::Draw(0, &src, &dst, c, 0.0f);
}