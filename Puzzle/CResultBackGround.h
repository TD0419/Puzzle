#pragma once

// �g�p����w�b�_�[
#include"GameL/SceneObjManager.h"
#include "CMap.h"

// �g�p����l�[���X�y�[�X
using namespace GameL;

// �N���X�I�u�W�F�N�g�F���U���g��ʔw�i
class CResultBackGround : public CObj
{
public:
	CResultBackGround(CMap* CMap);
	~CResultBackGround() {};
	void Init();
	void Action();
	void Draw();

private:
	CMap* m_pMap;
	int m_objname;
};