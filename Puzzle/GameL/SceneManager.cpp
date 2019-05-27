#include <stdio.h>
#include <wchar.h>
#include "DirectXDevice.h"
#include "DrawTexture.h"
#include "DrawFont.h"
#include "Audio.h"
#include "SceneObjManager.h"
#include "SceneManager.h"
#include "HitBoxManager.h"
#include "MultiThread.h"
#include "WinInputs.h"

using namespace GameL;

#define SAFE_DELETE(p) { if(p){ delete (p);    (p)=nullptr;  }  }

//FPS�\���ݒ�
#ifdef _DEBUG
	#define HIT_DRAW	(true)	//�����蔻��\��(�f�o�b�N�p)
	#define DRAW_FPS	(true)	//FPS�\��
#else
	#define HIT_DRAW	(false)	//�����蔻���\��(�����[�X�p)
	#define DRAW_FPS	(false)	//FPS��\��
#endif

CScene*			CSceneManager::m_NewScene;			//�V�����V�[�����
CScene*			CSceneManager::m_Scene;				//���݂̃V�[�����
unsigned long	CSceneManager::m_TimeStart;
unsigned long	CSceneManager::m_TimeEnd;
unsigned long	CSceneManager::m_Time;
int				CSceneManager::m_TimeCount;


//�o�^���Ă�V�[�������s����
void CSceneManager::GameLoop()
{
	CDirectXDeviec::ViewClear();
	CDirectXDeviec::ViewDraw2D();

	Swap();			//�V�[���؂�ւ�
	SceneAction();	//�V�[���A�N�V�������s
	SceneDraw();	//�V�[���`��

	Input::Update(); // ���͏��X�V
	
	//FPS----------------
	// �f�o�b�O���̂ݕ\��
	#ifdef _DEBUG
	{
		static wchar_t  c[256];
		static float cl[4] = { 1.0f,1.0f,1.0f,1.0f };
		m_TimeEnd = timeGetTime();
		// 1�b�o�߂������ǂ����𒲂ׂ�
		if (timeGetTime() - m_TimeStart > 1000)
		{
			// 1�b�o��

			// ��񏉊���
			m_TimeStart = timeGetTime();
			m_Time = m_TimeCount;
			m_TimeCount = 0;
		}
		else
		{
			// 1�b���o��
			m_TimeCount++;
		}

		swprintf_s(c, L"FPS : %lu", m_Time);
		CDrawFont::StrDraw(c, 0, 0, 32, cl);
	}
	#endif
	//-------------------

	CDirectXDeviec::ViewFlip();		//�X���b�v
}

void CSceneManager::SceneAction()
{
	if(m_Scene!=NULL) 
		m_Scene->Scene(); //�V�[���̐i�s
	//�V�[���̒��ɂ���I�u�W�F�N�g���	
	CSceneObjManager::ObjAction();
	//�����蔻����s
	CHitBoxManager::AllHitCheck();
}

void CSceneManager::SceneDraw()
{
	//�V�[���̒��ɂ���`��I�u�W�F�N�g���
	CSceneObjManager::ObjDraw();
	//�����蔻��\��
	if(HIT_DRAW)
	{
		CHitBoxManager::DrawHitBox();
	}
}

//������
void CSceneManager::Init()
{
	m_TimeStart=m_TimeEnd=timeGetTime();
	m_Time		= 0;
    m_TimeCount	= 0;
	m_Scene		= nullptr;
	m_NewScene	= nullptr;
}

void CSceneManager::SetScene(CScene* scene)
{
	m_NewScene=scene;
}

CScene* CSceneManager::GetScene()
{
	return m_Scene;
}

void CSceneManager::Delete()
{
	SAFE_DELETE(m_Scene);
}

//�V�[���؂�ւ�
void CSceneManager::Swap()
{
	if(m_Scene == m_NewScene)
	{
		/*if(m_Scene == nullptr)
		{
			CMultiThread::End();
		}*/

		return;
	}

	if(m_Scene!=nullptr)
	{
		//�V�[���؂�ւ��ɂ��f�[�^�̔j��
		//�e�N�X�`���E�O���t�B�b�N�E�I�u�W�F�N�g�E�q�b�g�{�b�N�X���̍폜
		CHitBoxManager::DeleteAllListData();
		CSceneObjManager::ListDeleteSceneObj();
		CDrawTexture::DeleteImage(); 
		CAudio::DeleteAudio();
		CDrawFont::ListDelete();
		SAFE_DELETE(m_Scene);
	}

	if(m_NewScene==nullptr)
	{
		SAFE_DELETE(m_Scene);
		CMultiThread::End();
		return ;
	}
	m_Scene=m_NewScene;
	m_Scene->InitScene();		//�V�[���̏�����
}