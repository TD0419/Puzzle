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
CSceneConnect::CSceneConnect()
{

}

//�f�X�g���N�^
CSceneConnect::~CSceneConnect()
{

}

//���������\�b�h
void CSceneConnect::InitScene()
{
	// �w�i�I�u�W�F�N�g�̑���̉摜(���������Ă�������(��))
	Draw::LoadImageW(L"block.png", 0, TEX_SIZE_32);

	// �l�b�g���[�N�ڑ���ʔw�i�I�u�W�F�N�g
	CConnectBackGround* pConnectBackGround = new CConnectBackGround;
	Objs::InsertObj(pConnectBackGround, OBJ_RESULT_BACK_GROUND, 0);
}

//���s�����\�b�h
void CSceneConnect::Scene()
{

}