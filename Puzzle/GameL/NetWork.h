#pragma once

//STLデバッグ機能をOFFにする
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

constexpr auto PORT = (12345);
constexpr auto IP = ("127.0.0.1");

namespace GameL
{
	// データ受け取り結果
	enum class RecvState
	{
		Recv_Successful, // 受け取り成功
		Recv_Middle,	 // 受け取り中
		Connect_Cut		 // 相手との接続が切れる
	};

	// ネットワークを使うために必要なもの
	class NetWorkStandard
	{
	public:
		virtual void Init() = 0;
		virtual bool Connect() = 0;								// サーバーに接続
		virtual bool Send(char* pData, int nDataLen) = 0;		// データを送る
		virtual RecvState Recv(char* pData, int nDataLen) = 0;	// データを受け取る
		virtual void Close() = 0;								// 接続を遮断する
		virtual void Delete() = 0;
	};

	// サーバー情報
	class Server : public NetWorkStandard
	{
	public:
		void Init();
		bool Connect();							// クライアントに接続
		bool Send(char* pData, int nDataLen);	// データを送る
		RecvState Recv(char* pData, int nDataLen);	// データを受け取る
		void Close();							// 接続を遮断する
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
		bool Connect();							// サーバーに接続
		bool Send(char* pData, int nDataLen);	// データを送る
		RecvState Recv(char* pData, int nDataLen);	// データを受け取る
		void Close();							// 接続を遮断する
		void Delete();

	private:
		SOCKET m_Socket;						// サーバーに接続するためのソケット
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
		static bool Send(char* pData, int nDataLen);	  // データを送る
		static RecvState Recv(char* pData, int nDataLen); // データを受け取る
		static void Close();							  // 接続を遮断する
		static void Delete();
		static ConnectKind GetConnectKind() { return m_ConnectKind;  }

	private:
		static NetWorkStandard* m_NetWork;
		static ConnectKind m_ConnectKind;
	};
}