#include "NetWork.h"

#include <assert.h>

using namespace GameL;

void Server::Init()
{
	WSADATA wsadata;

	// winsock2の初期化
	int nError = WSAStartup(MAKEWORD(2, 2), &wsadata);

	assert(nError == 0);

	// ソケットの作成
	m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	// ソケット設定
	struct sockaddr_in addr;
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_ServerSocket, (struct sockaddr*)&addr, sizeof(addr));

	// TCPクライアントからの接続要求を待てる状態にする
	listen(m_ServerSocket, 1);

	// ノンブロッキングモードにする
	u_long val = 1;
	ioctlsocket(m_ServerSocket, FIONBIO, &val); // ソケットのI/Oモードを制御
}

void Server::Delete()
{
	// Winsock2の終了処理
	WSACleanup();
}

// クライアントに接続
// 戻り値 bool : 接続が成功したかどうか
bool Server::Connect()
{
	// TCPクライアントからの接続要求を受け付ける
	struct sockaddr_in client;
	int nClientSize = sizeof(client);
	m_ClientSocket = accept(m_ServerSocket, (struct sockaddr*)&client, &nClientSize);

	if (m_ClientSocket == INVALID_SOCKET)
	{
		// 接続失敗
		return false;
	}

	// 接続が成功したかどうかの確認用のデータを送る
	bool bData = true;
	Send((char*)&bData, sizeof(bData));

	int nError = WSAGetLastError();
	
	// データが送れているかどうかの確認
	if (nError == WSAEWOULDBLOCK || nError == 0)
	{
		// 接続成功
		return true;
	}

	return false;
}

// データを送る
// 引数1 char* : 送りたいデータ
// 引数2 int   : 送りたいデータの大きさ
// 戻り値 bool : 送信成功したかどうか
bool Server::Send(char* pData, int nDataLen)
{
	if (send(m_ClientSocket, (const char*)pData, nDataLen, 0) > 0)
	{
		// データ送信成功
		return true;
	}

	// データ送信失敗
	return false;
}

// データを受け取る
// 引数1 char* : 受け取りたいデータ
// 引数2 int   : 受け取りたいデータの大きさ
// 戻り値 bool : 受け取り成功したかどうか
RecvState Server::Recv(char* pData, int nDataLen)
{
	if(recv(m_ClientSocket, pData, nDataLen, 0) > 0)
	{
		// データ受け取り成功
		return RecvState::Recv_Successful;
	}

	int nError = WSAGetLastError();
	if (nError == WSAEWOULDBLOCK || nError == 0)
	{
		// データ受け取り中
		return RecvState::Recv_Middle;
	}

	// データ受け取り失敗
	return RecvState::Connect_Cut;
}

// サーバーとの接続遮断
void Server::Close()
{
	// TCPセッションの終了
	closesocket(m_ClientSocket);
}