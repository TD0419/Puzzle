//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/SetWindow.h"

#include "CTitleBackGround.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;

void CTitleBackGround::Init()
{

}

void CTitleBackGround::Action()
{
	
}

void CTitleBackGround::Draw()
{
	// �e�X�g�p�̔w�i(���������Ă�������)---------------------------
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst;//�\���ʒu

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + (float)Window::GetWidth(); // �E�B���h�E�̕�
	dst.m_bottom = dst.m_top + (float)Window::GetHeight();// �E�B���h�E�̍���

	Draw::Draw(0, &dst, c, 0.0f);
	// -------------------------------------------------------------
}