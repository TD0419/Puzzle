#pragma once

// �g�p����w�b�_�[
#include"GameL/SceneObjManager.h"

// �g�p����l�[���X�y�[�X
using namespace GameL;

// �N���X�I�u�W�F�N�g�F�l�b�g���[�N�ڑ���ʔw�i
class CConnectBackGround : public CObj
{
	// �l�b�g���[�N�ڑ���
	enum ConnectState
	{
		In_Connection,			// �ڑ���
		Connection_Successful,  // �ڑ�����
		Connection_failure,		// �ڑ����s
	};
public:
	CConnectBackGround() {};
	~CConnectBackGround() {};
	void Init();
	void Action();
	void Draw();

private:
	ConnectState m_ConnectState;	// �l�b�g���[�N�̐ڑ��󋵂�ۑ�����p
	int m_nFontAnimationFrame;	    // �����̕\���A�j���[�V�����Ǘ�
	unsigned int m_nGameStartTime;	// �Q�[���J�n����
};