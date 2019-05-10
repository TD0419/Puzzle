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
	Draw::LoadImageW(L"orange_block.png", 0, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_block.png", 1, TEX_SIZE_32);

	Draw::LoadImageW(L"yellow_block.png", 2, TEX_SIZE_32);

	Draw::LoadImageW(L"orange_star_block.png", 3, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_star_block.png", 4, TEX_SIZE_32);

	Draw::LoadImageW(L"yellow_star_block.png", 5, TEX_SIZE_32);

	Draw::LoadImageW(L"freeze_block.png", 8, TEX_SIZE_32);
	
	Draw::LoadImageW(L"side_block.png", 10, TEX_SIZE_32);

	Draw::LoadImageW(L"TestEffect.png", 11, TEX_SIZE_64);

	Draw::LoadImageW(L"next_block_space.png", 15, TEX_SIZE_64);

	//�u���b�N�I�u�W�F�N�g�ǂݍ���
	Cblock* p_block = new Cblock(100);
	Objs::InsertObj(p_block, OBJ_BLOCK, 1);

	//�}�b�v�I�u�W�F�N�g�ǂݍ���
	CMap* p_map = new CMap();
	Objs::InsertObj(p_map, OBJ_MAP, 1);

	CNextBlock* p_next = new CNextBlock();
	Objs::InsertObj(p_next, OBJ_NEXT_BLOCK, 1);
}

//���s�����\�b�h
void CSceneMain::Scene()
{
	
}