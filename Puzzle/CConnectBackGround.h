#pragma once

// �g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

// �g�p����l�[���X�y�[�X
using namespace GameL;

// �N���X�I�u�W�F�N�g�F�l�b�g���[�N�ڑ���ʔw�i
class CConnectBackGround : public CObj
{
public:
	CConnectBackGround() {};
	~CConnectBackGround() {};
	void Init();
	void Action();
	void Draw();
};