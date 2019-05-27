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
#include "GameHead.h"

//�R���X�g���N�^
CSceneResult::CSceneResult(CMap* CMap)
{
	m_pMap = CMap;
}

//�f�X�g���N�^
CSceneResult::~CSceneResult()
{

}

//���������\�b�h
void CSceneResult::InitScene()
{
	// �w�i�摜
	Draw::LoadImageW(L"Result.jpg", 0, TEX_SIZE_512);

	// ���U���g��ʔw�i�I�u�W�F�N�g
	CResultBackGround* pResultBackGround = new CResultBackGround(m_pMap);
	Objs::InsertObj(pResultBackGround, OBJ_RESULT_BACK_GROUND, 0);

	Audio::LoadAudio(0, L"Decision_SE.wav", EFFECT);

	Audio::LoadAudio(1, L"Result_BGM.wav", BACK_MUSIC);

	// ���U���gBGM�𗬂�
	Audio::Start(1);
}

//���s�����\�b�h
void CSceneResult::Scene()
{

}