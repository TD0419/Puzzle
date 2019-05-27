//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/WinInputs.h"
#include "GameL/SceneManager.h"
#include "GameL/SetWindow.h"
#include "GameL/NetWork.h"
#include "GameL/Audio.h"

#include "CSceneConnect.h"
#include "CTitleBackGround.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CTitleBackGround::Init()
{

}

void CTitleBackGround::Action()
{
	// ���̃V�[���J�ڏ���(�摜���ł�����A������ς��Ă�������)--
	if (Input::GetVKeyDown('Z') == true)
	{
		// �l�b�g���[�N�ڑ���ʂ�
		CSceneManager::SetScene(new CSceneConnect(NetWork::ConnectKind::Server));

		Audio::Start(0);
	}
	else if (Input::GetVKeyDown('X') == true)
	{
		// �l�b�g���[�N�ڑ���ʂ�
		CSceneManager::SetScene(new CSceneConnect(NetWork::ConnectKind::Client));

		Audio::Start(0);
	}
	// ----------------------------------------------------------
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

	// �^�C�g����ʂƕ�����悤�ɕ�����`��
	Font::StrDraw(L"�W���E�I�E�f", 0.f, 0.f, 200.f, c);

	// �J�ڕ��@��\��
	Font::StrDraw(L"��������� ZKey", 0.f, 400.f, 120.f, c);

	Font::StrDraw(L"�����ɓ��� XKey", 0.f, 520.f, 120.f, c);
}