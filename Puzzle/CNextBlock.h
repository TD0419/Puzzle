#pragma once

//使用するヘッダーファイル
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：次のブロック表示
class CNextBlock : public CObj
{
	public:
		CNextBlock() {};
		~CNextBlock() {};
		void Init();
		void Action();
		void Draw();

	private:
		float m_Px;
		float m_Py;

		int m_block_num;
};