//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/SetWindow.h"
#include "GameL/WinInputs.h"
#include "GameL/Audio.h"

#include "GameHead.h"
#include "CResultBackGround.h"
#include "CSceneTitle.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

CResultBackGround::CResultBackGround(CMap* CMap)
{
	m_pMap = CMap;
	m_objname = m_pMap->GetName();
}

void CResultBackGround::Init()
{
	// �����e�N�X�`�����쐬
	Font::SetStrTex((wchar_t*)L"ResultNx ZKeyPLAYE1Win!2");
}

void CResultBackGround::Action()
{
	// ���̃V�[���J�ڏ���(�摜���ł�����A������ς��Ă�������)--
	if (Input::GetVKeyDown('Z') == true)
	{
		// �^�C�g����ʂ�
		CSceneManager::SetScene(new CSceneTitle);

		Audio::Start(0);
	}
	// ----------------------------------------------------------
}

void CResultBackGround::Draw()
{
	// �e�X�g�p�̔w�i(���������Ă�������)---------------------------
	// �J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst;//�\���ʒu

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + (float)Window::GetWidth(); // �E�B���h�E�̕�
	dst.m_bottom = dst.m_top + (float)Window::GetHeight();// �E�B���h�E�̍���

	Draw::Draw(0, &dst, c, 0.0f);
	// -------------------------------------------------------------

	// ���U���g��ʂƕ�����悤�ɕ�����`��
	Font::StrDraw(L"Result", 0.f, 0.f, 360.f, c);

	// �J�ڕ��@��\��
	Font::StrDraw(L"Next ZKey", 0.f, 400.f, 120.f, c);

	if (m_objname == OBJ_MAP)
	{
		//Font::StrDraw(L"PLAYER2 is Win!", 0.f, 600.f, 150.f, c);
		Font::StrDraw(L"You Lose!", 0.f, 600.f, 150.f, c);
	}
	else if (m_objname == OBJ_MAP_PLAY2)
	{
		//Font::StrDraw(L"PLAYER1 is Win!", 0.f, 600.f, 150.f, c);
		Font::StrDraw(L"You Win!", 0.f, 600.f, 150.f, c);
	}
}