#pragma once

// 使用するヘッダー
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"

#include <vector>

// 使用するネームスペース
using namespace GameL;

// エフェクトオブジェクト(継承用)
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
	int m_nId;			// 使用したい画像のid
	int m_nLiveTime;    // エフェクトの生存時間
	int m_nElapsedTime; // エフェクトが生成されてからの経過時間
	RECT_F m_RectSrc;	// 画像の切り取り位置
	RECT_F m_RectDst;	// 画像の描画位置
	float m_fRotation;	// 画像の回転
	float m_fColor[4];	// 描画する色
};

// 時間によって色と大きさを変更できるエフェクト 
// First(生成時)→Last(削除時)の順番に色や大きさを変える
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
	RECT_F m_RectFirst;		 // エフェクトが生成された時の表示位置
	RECT_F m_RectLast;		 // エフェクトの寿命が尽きた時の表示位置
	float m_fFirstColor[4];  // エフェクトが生成された時の色
	float m_fLastColor[4];   // エフェクトの寿命が尽きた時の色
};

// 複数エフェクトをまとめて使いたい時に使うオブジェクト
class CEffectSystem : public CObj
{
public:
	CEffectSystem(CEffect* pEffect);
	~CEffectSystem();
	void Init() {}
	void Action();
	void Draw() {}
	// 現在登録されているエフェクトの表示が終わってから表示したいエフェクトを追加
	void AddNextEffect(CEffect* pEffect); 

private:
	std::vector<CEffect*> m_vecEffects;   // エフェクトを管理するベクター
};