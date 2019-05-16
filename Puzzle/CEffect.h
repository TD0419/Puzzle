#pragma once

// �g�p����w�b�_�[
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"

#include <vector>

// �g�p����l�[���X�y�[�X
using namespace GameL;

// �G�t�F�N�g�I�u�W�F�N�g(�p���p)
class CEffect : public CObj
{
public:
	CEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime, float fRotation, float fColor[4]);
	CEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime, float fRotation);
	CEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime);
	~CEffect() {}
	void Init() {}
	virtual void Action();
	void Draw();

protected:
	int m_nId;			// �g�p�������摜��id
	int m_nLiveTime;    // �G�t�F�N�g�̐�������
	int m_nElapsedTime; // �G�t�F�N�g����������Ă���̌o�ߎ���
	RECT_F m_RectSrc;	// �摜�̐؂���ʒu
	RECT_F m_RectDst;	// �摜�̕`��ʒu
	float m_fRotation;	// �摜�̉�]
	float m_fColor[4];	// �`�悷��F
};

// ���Ԃɂ���ĐF�Ƒ傫����ύX�ł���G�t�F�N�g 
// First(������)��Last(�폜��)�̏��ԂɐF��傫����ς���
class CExEffect : public CEffect
{
public:
	CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
		float fFirstColor[4], float fLastColor[4], RECT_F* pRectDstLast);

	CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
		float fFirstColor[4], float fLastColor[4]);

	CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
		float fFirstColor[4], float fLastColor[4], RECT_F* pRectDstLast, float fRotation);

	CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
		float fFirstColor[4], float fLastColor[4], float fRotation);
	~CExEffect() {}
	void Action();

private:
	RECT_F m_RectFirst;		 // �G�t�F�N�g���������ꂽ���̕\���ʒu
	RECT_F m_RectLast;		 // �G�t�F�N�g�̎������s�������̕\���ʒu
	float m_fFirstColor[4];  // �G�t�F�N�g���������ꂽ���̐F
	float m_fLastColor[4];   // �G�t�F�N�g�̎������s�������̐F
};

// �����G�t�F�N�g���܂Ƃ߂Ďg���������Ɏg���I�u�W�F�N�g
class CEffectSystem : public CObj
{
public:
	CEffectSystem(CEffect* pEffect);
	~CEffectSystem();
	void Init() {}
	void Action();
	void Draw() {}
	// ���ݓo�^����Ă���G�t�F�N�g�̕\�����I����Ă���\���������G�t�F�N�g��ǉ�
	void AddNextEffect(CEffect* pEffect); 

private:
	std::vector<CEffect*> m_vecEffects;   // �G�t�F�N�g���Ǘ�����x�N�^�[
};