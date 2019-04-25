#pragma once

//使用するヘッダー
#include"GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：お邪魔(凍ってる)ブロック
class CFreezeblock : public CObj
{
	public:
		CFreezeblock(int x,int y,int id);
		~CFreezeblock() {};
		void Init();
		void Action();
		void Draw();

	private:
		float m_fPx;
		float m_fPy;
		float m_fVx;
		float m_fVy;

		bool m_bStop_flag;//ブロック停止フラグ

		int m_bColornum;//ブロックの色
		int m_elementX_storage;//ブロックの要素番号Xの保存
		int m_elementY_storage;//ブロックの要素番号Yの保存
};