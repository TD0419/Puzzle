#pragma once

// �g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

// �g�p����l�[���X�y�[�X
using namespace GameL;

// �N���X�I�u�W�F�N�g�F�^�C�g���w�i
class CTitleBackGround : public CObj
{
public:
	CTitleBackGround() {};
	~CTitleBackGround() {};
	void Init();
	void Action();
	void Draw();
};