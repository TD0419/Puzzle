#pragma once

//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

constexpr auto PORT = (12345);
constexpr auto IP = ("127.0.0.1");
//constexpr auto IP = ("172.17.70.17");

namespace GameL
{
	// 送り合うデータ
	struct SendData
	{
		SendData()
		{
			m_generate_block = (char)-1;
			m_player_operation = (char)-1;
		}

		// 次に生成するブロック
		char m_generate_block;
		// プレイヤー操作(キー情報が入る)
		char m_player_operation;
	};

	// サーバーとネットワークのデータを送りあう用の変数
	static SendData g_SendData;

	// データ送信結果
	enum class SendState
	{
		Send_Successful, // 送信成功
		Send_Middle,	// 送信中
		Connect_Cut		// 相手との接続が切れる
	};

	// データ受け取り結果
	enum class RecvState
	{
		Recv_Successful, // 受け取り成功
		Recv_Middle,	 // 受け取り中
		Recv_NoSend,	 // データが送られていません
		Connect_Cut		 // 相手との接続が切れる
	};

	// ネットワークを使うために必要なもの
	class NetWorkStandard
	{
	public:
		virtual void Init() = 0;
		virtual bool Connect() = 0;								// サーバーに接続
		virtual SendState Send(char* pData, int nDataLen) = 0;	// データを送る
		virtual RecvState Recv(char* pData, int nDataLen) = 0;	// データを受け取る
		virtual void Close() = 0;								// 接続を遮断する
		virtual void Delete() = 0;
	};

	// サーバー情報
	class Server : public NetWorkStandard
	{
	public:
		void Init();
		bool Connect();								// クライアントに接続
		SendState Send(char* pData, int nDataLen);	// データを送る
		RecvState Recv(char* pData, int nDataLen);	// データを受け取る
		void Close();								// 接続を遮断する
		void Delete();

	private:
		SOCKET m_ServerSocket;			
		SOCKET m_ClientSocket;			
	};

	// クライアント情報
	class Client : public NetWorkStandard
	{
	public:
		void Init();
		bool Connect();								// サーバーに接続
		SendState Send(char* pData, int nDataLen);	// データを送る
		RecvState Recv(char* pData, int nDataLen);	// データを受け取る
		void Close();								// 接続を遮断する
		void Delete();

	private:
		SOCKET m_Socket;							// サーバーに接続するためのソケット
	};

	// ネットワークを管理するクラス(ネットワークを使用する際をこれを使う)
	class NetWork
	{
	public:
		// 役割の種類
		enum class ConnectKind
		{
			Server,
			Client,
		};

	public:
		static void Init(ConnectKind connectkind);
		static bool Connect();							  // 接続
		static SendState Send(char* pData, int nDataLen); // データを送る
		static RecvState Recv(char* pData, int nDataLen); // データを受け取る
		static void Close();							  // 接続を遮断する
		static void Delete();
		static ConnectKind GetConnectKind() { return m_ConnectKind;  }
		static bool GetisNetWorkConnect() { return m_isNetWorkConnect; }
		static void NetWorkCut() { m_isNetWorkConnect = false; } // ネットワーク接続が切れた時に呼ぶ関数

	private:
		static NetWorkStandard* m_NetWork;
		static ConnectKind m_ConnectKind;
		static bool m_isNetWorkConnect;			// ネットワーク接続せれているかどうか
	};
}