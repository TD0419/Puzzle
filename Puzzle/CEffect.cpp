#include "CEffect.h"

using namespace GameL;

// CEffect----------------------------------------------------------------------------

// 引数1 int	  : エフェクトに使う画像ID
// 引数2 RECT_F*  : 画像の切り取り位置
// 引数3 RECT_F*  : 画像の表示位置
// 引数4 int	  : エフェクトの表示時間
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

// 引数1 int	  : エフェクトに使う画像ID
// 引数2 RECT_F*  : 画像の切り取り位置
// 引数3 RECT_F*  : 画像の表示位置
// 引数4 int	  : エフェクトの表示時間 
// 引数5 float    : 画像回転(度数法)
// 引数6 float[4] : 色情報
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
		// エフェクトの生存時間を過ぎていたら削除
		SetStatus(false);
	}
	else
	{
		// 経過時間を増やす
		m_nElapsedTime++;
	}
}

void CEffect::Draw()
{
	// 画像描画
	Draw::Draw(m_nId, &m_RectSrc, &m_RectDst, m_fColor, m_fRotation);
}

// ---------------------------------------------------------------------------------------

// CExEffectクラス-------------------------------------------------------------------------------

// 引数1 int	  : エフェクトに使う画像のID
// 引数2 RECT_F*  : 画像の切り取り位置
// 引数3 RECT_F*  : 画像の表示位置
// 引数4 int	  : エフェクトの表示時間 
// 引数5 float    : 画像回転(度数法)
// 引数6 float[4] : エフェクトが生成された時の色情報
// 引数7 float[4] : エフェクトの寿命が尽きた時の色情報
CExEffect::CExEffect(int nId, RECT_F* pRectSrc, RECT_F* pRectDst, int nLiveTime,
	float fFirstColor[4], float fLastColor[4])
	: CEffect(nId, pRectSrc, pRectDst, nLiveTime)
{
	memcpy_s(m_fFirstColor, sizeof(m_fFirstColor), fFirstColor, sizeof(float) * 4);
	memcpy_s(m_fLastColor, sizeof(m_fLastColor), fLastColor, sizeof(float) * 4);

	m_RectFirst = *pRectDst;
	m_RectLast = *pRectDst;
}

// 引数1 int	  : エフェクトに使う画像ID
// 引数2 RECT_F*  : 画像の切り取り位置
// 引数3 RECT_F*  : 画像の表示位置
// 引数4 int	  : エフェクトの表示時間 
// 引数5 float    : 画像回転(度数法)
// 引数6 float[4] : エフェクトが生成された時の色情報
// 引数7 float[4] : エフェクトの寿命が尽きた時の色情報
// 引数8 RECT_F*  : エフェクトの寿命が尽きた時の表示位置
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

	// 変化量を求める
	float fChange = (float)m_nElapsedTime / (float)m_nLiveTime;
	
	// 色を情報を変化させる
	m_fColor[0] = m_fFirstColor[0] + (m_fLastColor[0] - m_fFirstColor[0]) * fChange;
	m_fColor[1] = m_fFirstColor[1] + (m_fLastColor[1] - m_fFirstColor[1]) * fChange;
	m_fColor[2] = m_fFirstColor[2] + (m_fLastColor[2] - m_fFirstColor[2]) * fChange;
	m_fColor[3] = m_fFirstColor[3] + (m_fLastColor[3] - m_fFirstColor[3]) * fChange;
	
	// 表示位置を変化させる
	m_RectDst.m_top	   = m_RectFirst.m_top    + (m_RectLast.m_top	 - m_RectFirst.m_top)	 * fChange;
	m_RectDst.m_left   = m_RectFirst.m_left   + (m_RectLast.m_left   - m_RectFirst.m_left)	 * fChange;
	m_RectDst.m_right  = m_RectFirst.m_right  + (m_RectLast.m_right  - m_RectFirst.m_right)  * fChange;
	m_RectDst.m_bottom = m_RectFirst.m_bottom + (m_RectLast.m_bottom - m_RectFirst.m_bottom) * fChange;
}

// -----------------------------------------------------------------------------------------------------

// CEffectSystem-------------------------------------------------------------------------------

// 引数1 CEffect* : 最初に表示するエフェクトオブジェクト
CEffectSystem::CEffectSystem(CEffect* pEffect)
{
	AddNextEffect(pEffect);
	CSceneObjManager::InsertObj(pEffect, GetName(), GetPrio());
}

CEffectSystem::~CEffectSystem()
{
	// SceneObjManagerに登録していないオブジェクトをここで削除する(スッキリするやり方ではないので、後に修正予定)
	for (int i = 1; i < (int)m_vecEffects.size(); i++)
	{
		delete m_vecEffects[i];
	}
}

void CEffectSystem::Action()
{
	// 表示していたエフェクトが削除されていたら、
	if (m_vecEffects[0]->GetStatus() == false)
	{
		// ベクターから外す
		m_vecEffects.erase(m_vecEffects.begin());

		// 表示するエフェクトがなくなったので、削除
		if (m_vecEffects.size() == 0)
		{
			SetStatus(false);
			return;
		}

		// 次のエフェクト表示するためにオブジェクトマネージャーに追加
		CSceneObjManager::InsertObj(m_vecEffects[0], GetName(), GetPrio());
	}
}

// 現在登録されているエフェクトの表示が終わってから表示したいエフェクトを追加
// 引数1 CEffect* : 追加するエフェクトオブジェクト
void CEffectSystem::AddNextEffect(CEffect* pEffect)
{
	m_vecEffects.push_back(pEffect);
}

// --------------------------------------------------------------------------------------------