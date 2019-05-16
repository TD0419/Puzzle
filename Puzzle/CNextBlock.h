#pragma once

//使用するヘッダーファイル
#include "GameL/SceneObjManager.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：次のブロック表示
class CNextBlock : public CObj
{
	public:
		CNextBlock(float a,int b);
		//CNextBlock() {};
		~CNextBlock() {};
		void Init();
		void Action();
		void Draw();
		void Setblock_fall(bool a) { m_generate_block_flag = a; }

	private:
		float m_Px;
		float m_Py;

		bool m_generate_block_flag;

		int m_block_num;
		int m_freeze_block_late;
		int m_map_LR_judg;
};