//使用するヘッダーファイル
#include "GameL/DrawTexture.h"
#include "GameL/DrawFont.h"
#include "GameL/SceneManager.h"
#include "GameL/SetWindow.h"
#include "GameL/WinInputs.h"
#include "GameL/Audio.h"

#include "CResultBackGround.h"
#include "CSceneTitle.h"

//使用するネームスペース
using namespace GameL;

void CResultBackGround::Init()
{

}

void CResultBackGround::Action()
{
	// 仮のシーン遷移処理(画像ができたら、処理を変えてください)--
	if (Input::GetVKeyDown('Z') == true)
	{
		// タイトル画面へ
		CSceneManager::SetScene(new CSceneTitle);

		Audio::Start(0);
	}
	// ----------------------------------------------------------
}

void CResultBackGround::Draw()
{
	// テスト用の背景(差し換えてください)---------------------------
	// カラー情報
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F dst;//表示位置

	dst.m_top = 0.0f;
	dst.m_left = 0.0f;
	dst.m_right = dst.m_left + (float)Window::GetWidth(); // ウィンドウの幅
	dst.m_bottom = dst.m_top + (float)Window::GetHeight();// ウィンドウの高さ

	Draw::Draw(0, &dst, c, 0.0f);
	// -------------------------------------------------------------

	// リザルト画面と分かるように文字を描画
	Font::StrDraw(L"Result", 0.f, 0.f, 360.f, c);

	// 遷移方法を表示
	Font::StrDraw(L"Next ZKey", 0.f, 400.f, 120.f, c);
}