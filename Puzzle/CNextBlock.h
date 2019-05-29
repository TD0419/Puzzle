#pragma once

//使用するヘッダーファイル
#include "GameL/SceneObjManager.h"

#include "CMap.h"

//使用するネームスペース
using namespace GameL;

//オブジェクト：次のブロック表示
class CNextBlock : public CObj
{
	public:
		CNextBlock(float a, CMap* pMap);
		//CNextBlock() {};
		~CNextBlock() {};
		void Init();
		void Action();
		void Draw();
		void Setblock_fall(bool a) { m_generate_block_flag = a; }

	private:
		void SendNextBlock(int nNextBlock); // ネットワークを使用した、次のブロック情報を送る
		int RecvNextBlock();				// ネットワークを使用した、次のブロック情報を受け取る

	private:
		float m_Px;
		float m_Py;

		bool m_generate_block_flag;

		int m_block_num;
		int m_freeze_block_late;
		int freeze_time;

		CMap* m_pMap;
};