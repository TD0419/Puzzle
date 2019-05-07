#include "NetWork.h"

#include <assert.h>

using namespace GameL;

void Client::Init()
{
	WSADATA wsaData;

	// winsock2の初期化
	int nError = WSAStartup(MAKEWORD(2, 2), &wsaData);

	assert(nError == 0);
}

void Client::Delete()
{
	// Winsock2の終了処理
	WSACleanup();
}

// サーバーに接続
// 戻り値 bool : 接続が成功したかどうか
bool Client::Connect()
{
	// ソケット作成
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;				// IPv4
	addr.sin_addr.s_addr = inet_addr(IP);	// 通信するIPアドレス
	addr.sin_port = htons(PORT);			// 使用するポート設定
	
	// ここでサーバーに接続する
	if (connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr)) == 0)
	{
		// 接続成功
		return true;
	}

	// 接続失敗
	return false;
}

// データを送る
// 引数1 char* : 送りたいデータ
// 引数2 int   : 送りたいデータの大きさ
// 戻り値 bool : 送信成功したかどうか
bool Client::Send(char* pData, int nDataLen)
{
	if (send(m_Socket, (const char*)pData, nDataLen, 0) > 0)
	{
		// 送信成功
		return true;
	}

	// 送信失敗
	return false;
}

// データを受け取る
// 引数1 char* : 受け取りたいデータ
// 引数2 int   : 受け取りたいデータの大きさ
// 戻り値 bool : 受け取り成功したかどうか
bool Client::Recv(char* pData, int nDataLen)
{
	if (recv(m_Socket, pData, nDataLen, 0) > 0)
	{
		// データ受け取り成功
		return true;
	}

	// データ受け取り失敗
	return false;
}

// サーバーとの接続遮断
void Client::Close()
{
	closesocket(m_Socket);
}