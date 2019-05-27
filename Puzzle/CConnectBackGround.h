#pragma once

// 使用するヘッダー
#include"GameL/SceneObjManager.h"

// 使用するネームスペース
using namespace GameL;

// クラスオブジェクト：ネットワーク接続画面背景
class CConnectBackGround : public CObj
{
	// ネットワーク接続状況
	enum ConnectState
	{
		In_Connection,			// 接続中
		Connection_Successful,  // 接続成功
		Connection_failure,		// 接続失敗
	};
public:
	CConnectBackGround() {};
	~CConnectBackGround() {};
	void Init();
	void Action();
	void Draw();

private:
	ConnectState m_ConnectState;	// ネットワークの接続状況を保存する用
	int m_nFontAnimationFrame;	    // 文字の表示アニメーション管理
	unsigned int m_nGameStartTime;	// ゲーム開始時間
};