#include "CEffect.h"

using namespace GameL;

// CEffect----------------------------------------------------------------------------

// ����1 int	  : �G�t�F�N�g�Ɏg���摜ID
// ����2 RECT_F*  : �摜�̐؂���ʒu
// ����3 RECT_F*  : �摜�̕\���ʒu
// ����4 int	  : �G�t�F�N�g�̕\������
CEffect::CEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime)
{
	float fColor[4] = { 1.f, 1.f, 1.f, 1.f };
	m_nId = nId;
	m_RectSrc = *pRectSrc;
	m_RectDst = *pRectDst;
	m_nLiveTime = nLiveTime;
	m_nElapsedTime = 0;
	m_fRotation = 0.f;
	memcpy_s(m_fColor, sizeof(m_fColor), fColor, sizeof(float) * 4);
}

// ����1 int	  : �G�t�F�N�g�Ɏg���摜ID
// ����2 RECT_F*  : �摜�̐؂���ʒu
// ����3 RECT_F*  : �摜�̕\���ʒu
// ����4 int	  : �G�t�F�N�g�̕\������ 
// ����5 float    : �摜��](�x���@)
// ����6 float[4] : �F���
CEffect::CEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime, float fRotation, float fColor[4])
{
	m_nId = nId;
	m_RectSrc = *pRectSrc;
	m_RectDst = *pRectDst;
	m_nLiveTime = nLiveTime;
	m_nElapsedTime = 0;
	m_fRotation = fRotation;
	memcpy_s(m_fColor, sizeof(m_fColor), fColor, sizeof(float) * 4);
}

void CEffect::Action()
{
	if (m_nElapsedTime >= m_nLiveTime)
	{
		// �G�t�F�N�g�̐������Ԃ��߂��Ă�����폜
		SetStatus(false);
	}
	else
	{
		// �o�ߎ��Ԃ𑝂₷
		m_nElapsedTime++;
	}
}

void CEffect::Draw()
{
	// �摜�`��
	Draw::Draw(m_nId, &m_RectSrc, &m_RectDst, m_fColor, m_fRotation);
}

// ---------------------------------------------------------------------------------------

// CExEffect�N���X-------------------------------------------------------------------------------

// ����1 int	  : �G�t�F�N�g�Ɏg���摜��ID
// ����2 RECT_F*  : �摜�̐؂���ʒu
// ����3 RECT_F*  : �摜�̕\���ʒu
// ����4 int	  : �G�t�F�N�g�̕\������ 
// ����5 float    : �摜��](�x���@)
// ����6 float[4] : �G�t�F�N�g���������ꂽ���̐F���
// ����7 float[4] : �G�t�F�N�g�̎������s�������̐F���
CExEffect::CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
	float fFirstColor[4], float fLastColor[4])
	: CEffect(nId, pRectSrc, pRectDst, nLiveTime)
{
	memcpy_s(m_fFirstColor, sizeof(m_fFirstColor), fFirstColor, sizeof(float) * 4);
	memcpy_s(m_fLastColor, sizeof(m_fLastColor), fLastColor, sizeof(float) * 4);

	m_RectFirst = *pRectDst;
	m_RectLast = *pRectDst;
}

// ����1 int	  : �G�t�F�N�g�Ɏg���摜ID
// ����2 RECT_F*  : �摜�̐؂���ʒu
// ����3 RECT_F*  : �摜�̕\���ʒu
// ����4 int	  : �G�t�F�N�g�̕\������ 
// ����5 float    : �摜��](�x���@)
// ����6 float[4] : �G�t�F�N�g���������ꂽ���̐F���
// ����7 float[4] : �G�t�F�N�g�̎������s�������̐F���
// ����8 RECT_F*  : �G�t�F�N�g�̎������s�������̕\���ʒu
CExEffect::CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
	float fFirstColor[4], float fLastColor[4], RECT_F* pRectDstLast)
	: CEffect(nId, pRectSrc, pRectDst, nLiveTime)
{
	memcpy_s(m_fFirstColor, sizeof(m_fFirstColor), fFirstColor, sizeof(float) * 4);
	memcpy_s(m_fLastColor, sizeof(m_fLastColor), fLastColor, sizeof(float) * 4);

	m_RectFirst = *pRectDst;
	m_RectLast = *pRectDstLast;
}

void CExEffect::Action()
{
	CEffect::Action();

	// �ω��ʂ����߂�
	float fChange = (float)m_nElapsedTime / (float)m_nLiveTime;
	
	// �F������ω�������
	m_fColor[0] = m_fFirstColor[0] + (m_fLastColor[0] - m_fFirstColor[0]) * fChange;
	m_fColor[1] = m_fFirstColor[1] + (m_fLastColor[1] - m_fFirstColor[1]) * fChange;
	m_fColor[2] = m_fFirstColor[2] + (m_fLastColor[2] - m_fFirstColor[2]) * fChange;
	m_fColor[3] = m_fFirstColor[3] + (m_fLastColor[3] - m_fFirstColor[3]) * fChange;
	
	// �\���ʒu��ω�������
	m_RectDst.m_top	   = m_RectFirst.m_top    + (m_RectLast.m_top	 - m_RectFirst.m_top)	 * fChange;
	m_RectDst.m_left   = m_RectFirst.m_left   + (m_RectLast.m_left   - m_RectFirst.m_left)	 * fChange;
	m_RectDst.m_right  = m_RectFirst.m_right  + (m_RectLast.m_right  - m_RectFirst.m_right)  * fChange;
	m_RectDst.m_bottom = m_RectFirst.m_bottom + (m_RectLast.m_bottom - m_RectFirst.m_bottom) * fChange;
}

// -----------------------------------------------------------------------------------------------------

// CEffectSystem-------------------------------------------------------------------------------

// ����1 CEffect* : �ŏ��ɕ\������G�t�F�N�g�I�u�W�F�N�g
CEffectSystem::CEffectSystem(CEffect* pEffect)
{
	AddNextEffect(pEffect);
	CSceneObjManager::InsertObj(pEffect, GetName(), GetPrio());
}

CEffectSystem::~CEffectSystem()
{
	// SceneObjManager�ɓo�^���Ă��Ȃ��I�u�W�F�N�g�������ō폜����(�X�b�L����������ł͂Ȃ��̂ŁA��ɏC���\��)
	for (int i = 1; i < (int)m_vecEffects.size(); i++)
	{
		delete m_vecEffects[i];
	}
}

void CEffectSystem::Action()
{
	// �\�����Ă����G�t�F�N�g���폜����Ă�����A
	if (m_vecEffects[0]->GetStatus() == false)
	{
		// �x�N�^�[����O��
		m_vecEffects.erase(m_vecEffects.begin());

		// �\������G�t�F�N�g���Ȃ��Ȃ����̂ŁA�폜
		if (m_vecEffects.size() == 0)
		{
			SetStatus(false);
			return;
		}

		// ���̃G�t�F�N�g�\�����邽�߂ɃI�u�W�F�N�g�}�l�[�W���[�ɒǉ�
		CSceneObjManager::InsertObj(m_vecEffects[0], GetName(), GetPrio());
	}
}

// ���ݓo�^����Ă���G�t�F�N�g�̕\�����I����Ă���\���������G�t�F�N�g��ǉ�
// ����1 CEffect* : �ǉ�����G�t�F�N�g�I�u�W�F�N�g
void CEffectSystem::AddNextEffect(CEffect* pEffect)
{
	m_vecEffects.push_back(pEffect);
}

// --------------------------------------------------------------------------------------------