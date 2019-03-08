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
		float m_f_px;
		float m_f_py;
		float m_f_vx;
		float m_f_vy;
};