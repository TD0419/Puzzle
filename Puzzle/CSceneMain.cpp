//STL�f�o�b�N�@�\��OFF����
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "CSceneMain.h"
#include "GameHead.h"

#include <vector>

//�R���X�g���N�^
CSceneMain::CSceneMain()
{

}

//�f�X�g���N�^
CSceneMain::~CSceneMain()
{
	
}

//���������\�b�h
void CSceneMain::InitScene()
{
	//�O���t�B�b�N�ǂݍ���
	//�����ŃG���[���o���̂�LoadImageW��wchar_t*��const�����Ċm���߂�
	//��X�C�����K�v
	Draw::LoadImageW(L"block.png", 0, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_block.png", 1, TEX_SIZE_32);
	
	Draw::LoadImageW(L"side_block.png", 2, TEX_SIZE_32);

	//�u���b�N�I�u�W�F�N�g�ǂݍ���
	Cblock* p_block = new Cblock();
	Objs::InsertObj(p_block, OBJ_BLOCK, 1);

	//�}�b�v�I�u�W�F�N�g�ǂݍ���
	CMap* p_map = new CMap();
	Objs::InsertObj(p_map, OBJ_MAP, 1);
}

//���s�����\�b�h
void CSceneMain::Scene()
{
	
}