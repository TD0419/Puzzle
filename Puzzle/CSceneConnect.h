#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"
#include "GameL\NetWork.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

// �V�[�� : �l�b�g���[�N�ڑ����
class CSceneConnect : public CScene
{
public:
	CSceneConnect(ConnectKind connectkind);
	~CSceneConnect() {}
	void InitScene();//���������\�b�h
	void Scene();	 //���s�����\�b�h
private:
};