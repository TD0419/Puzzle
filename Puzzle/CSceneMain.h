#pragma once
//�g�p����w�b�_�[�t�@�C��
#include "GameL\SceneManager.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

// �V�[�� : �Q�[�����
class CSceneMain : public CScene
{
	public:
		CSceneMain();
		~CSceneMain();
		void InitScene();//���������\�b�h
		void Scene();	 //���s�����\�b�h
	private:
		void LoadGraphic(); // �摜�ǂݍ���
		void LoadAudio();	// ���y�ǂݍ���
};