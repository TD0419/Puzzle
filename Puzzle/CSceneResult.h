#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"
#include "CMap.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

// �V�[�� : ���U���g���
class CSceneResult : public CScene
{
public:
	CSceneResult(CMap* CMap);
	~CSceneResult();
	void InitScene();//���������\�b�h
	void Scene();	 //���s�����\�b�h
private:

	CMap* m_pMap;
};