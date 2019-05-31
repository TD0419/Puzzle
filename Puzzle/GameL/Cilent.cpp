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
	addr.sin_addr.S_un.S_addr = inet_addr(IP);	// 通信するIPアドレス
	addr.sin_port = htons(PORT);			// 使用するポート設定

	// ノンブロッキングモードにする
	u_long val = 1;
	ioctlsocket(m_Socket, FIONBIO, &val);   // ソケットのI/Oモードを制御

	// ここでサーバーに接続する
	connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr));

	if (m_Socket == INVALID_SOCKET)
	{
		// 接続失敗
		return false;
	}

	Sleep(1000);

	// 正しくサーバーに接続できているかのテスト
	bool bData = false;

	while (1)
	{
		// 確認用データ取得
		RecvState ReState = Recv((char*)&bData, sizeof(bData));
		
		if (ReState == RecvState::Recv_Successful)
		{
			break;
		}
		else if(ReState == RecvState::Connect_Cut)
		{
			// サーバーが立ち上がっていません
			return false;
		}
	}

	// 接続成功
	return true;
}

// データを送る
// 引数1 char*		: 送りたいデータ
// 引数2 int		: 送りたいデータの大きさ
// 戻り値 SendState : 送信成功したかどうか
SendState Client::Send(char* pData, int nDataLen)
{
	if (send(m_Socket, (const char*)pData, nDataLen, 0) > 0)
	{
		// 送信成功
		return SendState::Send_Successful;
	}

	int nError = WSAGetLastError();
	if (nError == WSAEWOULDBLOCK || nError == 0)
	{
		// データ送信中
		return SendState::Send_Middle;
	}

	// データ送信失敗
	return SendState::Connect_Cut;
}

// データを受け取る
// 引数1 char*		: 受け取りたいデータ
// 引数2 int		: 受け取りたいデータの大きさ
// 戻り値 RecvState : 受け取った結果(サーバーとの接続切れもここで調べる)
RecvState Client::Recv(char* pData, int nDataLen)
{
	if (recv(m_Socket, pData, nDataLen, 0) > 0)
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

	// サーバーとの接続が切れている
	return RecvState::Connect_Cut;
}

// サーバーとの接続遮断
void Client::Close()
{
	closesocket(m_Socket);
}