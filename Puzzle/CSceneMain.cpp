//STL�f�o�b�N�@�\��OFF����
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameL�Ŏg�p����w�b�_�[
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�g�p�w�b�_�[
#include "CSceneMain.h"
#include "GameHead.h"

#include <vector>
#include "GameL/WinInputs.h"
#include "GameL/NetWork.h"


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
	// �O���t�B�b�N�ǂݍ���
	LoadGraphic();

	// �T�E���h�ǂݍ���
	LoadAudio();

	//�}�b�v�I�u�W�F�N�g�ǂݍ���
	CMap* p_map = new CMap(0);
	Objs::InsertObj(p_map, OBJ_MAP, 1);

	CMap* p_map_2 = new CMap(620);
	Objs::InsertObj(p_map_2, OBJ_MAP_PLAY2, 1);
}

//���s�����\�b�h
void CSceneMain::Scene()
{
	
}

// �摜�ǂݍ���
void CSceneMain::LoadGraphic()
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

	Draw::LoadImageW(L"Effect1_1.png", 11, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_2.png", 12, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_3.png", 13, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_4.png", 14, TEX_SIZE_512);

	Draw::LoadImageW(L"next_block_space.png", 15, TEX_SIZE_64);

	Draw::LoadImageW(L"Cross.png", 16, TEX_SIZE_32);
}

// ���y�ǂݍ���
void CSceneMain::LoadAudio()
{
	Audio::LoadAudio(0, L"Effect_SE.wav", EFFECT);

	Audio::LoadAudio(1, L"Game_BGM.wav", BACK_MUSIC);

	// �Q�[��BGM�𗬂�
	Audio::Start(1);
}