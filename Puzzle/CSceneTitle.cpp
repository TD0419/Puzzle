//STL�f�o�b�N�@�\��OFF����
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "GameHead.h"

//�R���X�g���N�^
CSceneTitle::CSceneTitle()
{

}

//�f�X�g���N�^
CSceneTitle::~CSceneTitle()
{

}

//���������\�b�h
void CSceneTitle::InitScene()
{
	// �w�i�I�u�W�F�N�g�̑���̉摜(���������Ă�������(��))
	//Draw::LoadImageW(L"block.png", 0, TEX_SIZE_32);

	// �^�C�g���w�i�I�u�W�F�N�g
	CTitleBackGround* pTitleBackGround = new CTitleBackGround;
	Objs::InsertObj(pTitleBackGround, OBJ_TITLE_BACK_GROUND, 0);
}

//���s�����\�b�h
void CSceneTitle::Scene()
{

}