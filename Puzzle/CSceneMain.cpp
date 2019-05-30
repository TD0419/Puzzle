//STLデバック機能をOFFする
#define _SECURE_SCL (0)
#define _HAS_IETRATOR_DEBUGGING (0)

//GameLで使用するヘッダー
#include "GameL\SceneObjManager.h"
#include "GameL\DrawTexture.h"
#include "GameL\Audio.h"

//使用するネームスペース
using namespace GameL;

//使用ヘッダー
#include "CSceneMain.h"
#include "GameHead.h"

#include <vector>
#include "GameL/WinInputs.h"
#include "GameL/NetWork.h"

//extern SendData g_SendData;

//コンストラクタ
CSceneMain::CSceneMain()
{

}

//デストラクタ
CSceneMain::~CSceneMain()
{
	
}

//初期化メソッド
void CSceneMain::InitScene()
{
	LoadGraphic();
	LoadAudio();

	////ブロックオブジェクト読み込み
	//Cblock* p_block = new Cblock(100,LEFT_MAP);
	//Objs::InsertObj(p_block, OBJ_BLOCK, 1);

	//Cblock* p_block_2 = new Cblock(100, RIGHT_MAP);
	//Objs::InsertObj(p_block_2, OBJ_BLOCK_2, 1);

	//マップオブジェクト読み込み
	CMap* p_map = new CMap(0);
	Objs::InsertObj(p_map, OBJ_MAP, 1);

	CMap* p_map_2 = new CMap(620);
	Objs::InsertObj(p_map_2, OBJ_MAP_PLAY2, 1);

	//CNextBlock* p_next = new CNextBlock(0);
	//Objs::InsertObj(p_next, OBJ_NEXT_BLOCK, 1);

	//CNextBlock* p_next_2 = new CNextBlock(620);
	//Objs::InsertObj(p_next_2, OBJ_NEXT_BLOCK_2, 1);
}

//実行中メソッド
void CSceneMain::Scene()
{
	// ネットワークテスト中なので、消さないで
	//// 押した瞬間
	//if (Input::GetVKeyDown('A') == true)
	//{
	//	g_SendData.m_player_operation = 'A';
	//}
	//else if (Input::GetVKeyDown('D') == true)
	//{
	//	g_SendData.m_player_operation = 'D';
	//}
	//else
	//{
	//	g_SendData.m_player_operation = 0;
	//}

	//while (1)
	//{
	//	SendState send_state = NetWork::Send((char*)&g_SendData, sizeof(g_SendData));
	//	// 対戦相手のデータ送信成功
	//	if (send_state == SendState::Send_Successful)
	//	{
	//		break;
	//	}
	//	// 対戦相手の通信が途絶えた場合
	//	else if (send_state == SendState::Connect_Cut)
	//	{
	//		// タイトルに戻る
	//		Scene::SetScene(new CSceneTitle);

	//		// 対戦相手の通信が途絶えた場合
	//		MessageBox(NULL, L"対戦相手との通信が途絶えました", L"通信エラー", MB_OK);

	//		return;
	//	}
	//}

	//while (1)
	//{
	//	int nTime = 0;
	//	RecvState recv_state = NetWork::Recv((char*)&g_SendData, sizeof(g_SendData));
	//			
	//	// 対戦相手のデータ受け取り成功
	//	if (recv_state == RecvState::Recv_Successful || recv_state == RecvState::Recv_NoSend)
	//	{
	//		break;
	//	}
	//	// 対戦相手の通信が途絶えた場合
	//	else if (recv_state == RecvState::Connect_Cut)
	//	{
	//		// タイトルに戻る
	//		Scene::SetScene(new CSceneTitle);

	//		// 対戦相手の通信が途絶えた場合
	//		MessageBox(NULL, L"対戦相手との通信が途絶えました", L"通信エラー", MB_OK);

	//		return;
	//	}
	//	else
	//	{
	//		if (nTime == 1)
	//		{
	//			break;
	//		}
	//		nTime++;
	//	}
	//}
}

// 画像読み込み
void CSceneMain::LoadGraphic()
{
	//グラフィック読み込み
	//ここでエラーが出たのでLoadImageWのwchar_t*にconstをつけて確かめた
	//後々修正が必要
	Draw::LoadImageW(L"orange_block.png", 0, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_block.png", 1, TEX_SIZE_32);

	Draw::LoadImageW(L"yellow_block.png", 2, TEX_SIZE_32);

	Draw::LoadImageW(L"orange_star_block.png", 3, TEX_SIZE_32);

	Draw::LoadImageW(L"blue_star_block.png", 4, TEX_SIZE_32);

	Draw::LoadImageW(L"yellow_star_block.png", 5, TEX_SIZE_32);

	Draw::LoadImageW(L"freeze_block.png", 8, TEX_SIZE_32);

	Draw::LoadImageW(L"side_block.png", 10, TEX_SIZE_32);

	Draw::LoadImageW(L"Effect1_1.png", 11, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_2.png", 12, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_3.png", 13, TEX_SIZE_512);

	Draw::LoadImageW(L"Effect1_4.png", 14, TEX_SIZE_512);

	Draw::LoadImageW(L"next_block_space.png", 15, TEX_SIZE_64);

	Draw::LoadImageW(L"Cross.png", 16, TEX_SIZE_32);
}

// 音楽読み込み
void CSceneMain::LoadAudio()
{
	Audio::LoadAudio(0, L"Effect_SE.wav", EFFECT);

	Audio::LoadAudio(1, L"Game_BGM.wav", BACK_MUSIC);

	// ゲームBGMを流す
	Audio::Start(1);
}