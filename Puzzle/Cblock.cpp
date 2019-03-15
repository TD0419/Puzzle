//�g�p����w�b�_�[�t�@�C��
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneManager.h"
#include"GameL/WinInputs.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void Cblock::Init()
{
	m_f_px = 400.0f;
	m_f_py = 32.0f;
	m_f_vx = 0.0f;
	m_f_vy = 0.0f;
}

//�A�N�V����
void Cblock::Action()
{
	//�ړ��x�N�g��������
	m_f_vy = 1.0f;
	m_f_vx = 0.0f;

	//A����������
	// XBOX�R�� �g�p�� if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		m_f_vx = -3.0f;//���ɓ���
	}
	//D����������
	else if (Input::GetVKey('D') == true)
	{
		m_f_vx = 3.0f;//�E�ɓ���
	}

	//�ړ��x�N�g�����Z
	m_f_px += m_f_vx;
	m_f_py += m_f_vy;
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

	dst.m_top = 0.0f + m_f_py;
	dst.m_left = 0.0f + m_f_px;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	Draw::Draw(0, &src, &dst, c, 0.0f);
}