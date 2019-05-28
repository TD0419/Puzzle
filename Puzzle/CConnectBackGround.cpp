//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/WinInputs.h"
#include "GameL/NetWork.h"
#include "GameL/SetWindow.h"
#include "GameL/Audio.h"

#include "CSceneMain.h"
#include "CSceneTitle.h"
#include "CConnectBackGround.h"

#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CConnectBackGround::Init()
{
	// �����e�N�X�`�����쐬
	Font::SetStrTex((wchar_t*)L"�ڑ���.�}�b�`���O���܂�����镔�������肹��ZKey��Title�ɖߑΐ� �b");

	m_ConnectState = In_Connection;
	m_nFontAnimationFrame = 0;
	m_nGameStartTime = (unsigned int)0;
}

void CConnectBackGround::Action()
{
	// �ڑ����̏���
	if (m_ConnectState == In_Connection)
	{
		if (NetWork::Connect() == true)
		{
			// �ڑ�����
			m_ConnectState = Connection_Successful;

			if (NetWork::GetConnectKind() == NetWork::ConnectKind::Server)
			{
				while (1)
				{
					// �Q�[�����n�܂�܂ł̎���(�҂����Ԃ�t����)
					// ����ɂ���ĊJ�n���Ԃ𓯊�������
					m_nGameStartTime = (unsigned int)time(NULL) + (unsigned int)5;

					if (NetWork::Send((char*)&m_nGameStartTime, sizeof(m_nGameStartTime))
						== true)
					{
						break;
					}
				}
			}
			else
			{
				while (1)
				{
					// �Q�[�����n�܂�܂ł̎��Ԃ��󂯎��
					if (NetWork::Recv((char*)&m_nGameStartTime, sizeof(m_nGameStartTime))
						== RecvState::Recv_Successful)
					{
						break;
					}
				}
			}
		}
		else
		{
			// �ڑ����s
			// �N���C�A���g�̏ꍇ
			if (NetWork::GetConnectKind() == NetWork::ConnectKind::Client)
			{
				m_ConnectState = Connection_failure;

				// �N���C�A���g���폜
				NetWork::Close();
				NetWork::Delete();
			}
			// �T�[�o�[�̏ꍇ
			else
			{
				if (Input::GetVKeyDown('Z') == true)
				{
					// �T�[�o�[���폜
					NetWork::Close();
					NetWork::Delete();

					Audio::Start(1);

					// �^�C�g����ʂ�
					Scene::SetScene(new CSceneTitle());
				}
			}
		}
	}
	// �ڑ�������̏���
	else if (m_ConnectState == Connection_Successful)
	{
		// �c�莞�Ԃ�0�b�ɂȂ�����
		if (m_nGameStartTime <= time(NULL))
		{
			// �Q�[����ʂ�
			Scene::SetScene(new CSceneMain());
		}
	}
	// �ڑ����s���̏���
	else if (m_ConnectState == Connection_failure)
	{
		if (Input::GetVKeyDown('Z') == true)
		{
			Audio::Start(0);

			// �^�C�g����ʂ�
			Scene::SetScene(new CSceneTitle());
		}
	}

	// �A�j���[�V�����^�C���𑝂₷
	m_nFontAnimationFrame++;

	// �A�j���[�V�������ő�܂ōs������A������
	const int nAnimationMaxTime = 240;

	if (m_nFontAnimationFrame >= nAnimationMaxTime)
	{
		m_nFontAnimationFrame = 0;
	}
}

void CConnectBackGround::Draw()
{
	// �w�i�`��
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst;//�\���ʒu

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = (float)Window::GetWidth(); // �E�B���h�E�̕�
	dst.m_bottom = (float)Window::GetHeight();// �E�B���h�E�̍���

	Draw::Draw(0, &dst, c, 0.f);

	if (m_ConnectState == In_Connection)
	{
		wchar_t szConnectMessage[256] = L"�ڑ���";
		const int nAnimationChangeNum = 60;		   // �A�j���[�V�����̕ω������l

		for (int i = 0; i < m_nFontAnimationFrame / nAnimationChangeNum; i++)
		{
			wcscat_s(szConnectMessage, 256, L"."); // �ڑ�����.�𑝂₵����A���炵���肷��A�j���[�V����
		}

		// �l�b�g���[�N�ڑ���ʂƕ�����悤�ɕ�����`��
		Font::StrDraw(szConnectMessage, 0.f, 0.f, 120.f, c);

		Font::StrDraw(L"Z Key��Title�ɖ߂�", 100.f, 400.f, 60.f, c);
	}
	else if (m_ConnectState == Connection_Successful)
	{
		// �ڑ����������Ƃ��ɕ\�����郁�b�Z�[�W
		Font::StrDraw(L"�}�b�`���O���܂���", 100.f, 400.f, 60.f, c);

		unsigned int nTime = m_nGameStartTime - (unsigned int)time(NULL);
		wchar_t szGameStartTime[256];
		swprintf_s(szGameStartTime, L"�ΐ�܂� %u�b", nTime);
		Font::StrDraw(szGameStartTime, 100.f, 600.f, 80.f, c);
	}
	else if (m_ConnectState == Connection_failure)
	{
		// �T�[�o�[���N������Ă��Ȃ����ɃN���C�A���g�𗧂��グ�Ă��܂����ꍇ�A
		Font::StrDraw(L"����镔��������܂���", 100.f, 200.f, 60.f, c);
		Font::StrDraw(L"Title�ɖ߂��Ă�������", 100.f, 400.f, 60.f, c);
		Font::StrDraw(L"Z Key��Title�ɖ߂�", 100.f, 600.f, 60.f, c);
	}
}