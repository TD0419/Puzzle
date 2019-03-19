#pragma once

//使用するヘッダー
#include"GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//クラスオブジェクト：ブロック
class Cblock : public CObj
{
	public:
		Cblock() {};
		~Cblock() {};
		void Init();
		void Action();
		void Draw();
	private:
		float m_fPx;
		float m_fPy;
		float m_fVx;
		float m_fVy;

		bool m_bStop_flag;
};