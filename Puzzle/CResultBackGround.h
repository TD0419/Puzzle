#pragma once

// �g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

// �g�p����l�[���X�y�[�X
using namespace GameL;

// �N���X�I�u�W�F�N�g�F���U���g��ʔw�i
class CResultBackGround : public CObj
{
public:
	CResultBackGround() {};
	~CResultBackGround() {};
	void Init();
	void Action();
	void Draw();
};