#include "NetWork.h"

using namespace GameL;

SendData g_SendData;

NetWorkStandard* NetWork::m_NetWork = 0;
NetWork::ConnectKind NetWork::m_ConnectKind;
bool NetWork::m_isNetWorkConnect = false;

// 引数1 ConnectKind : 自分がサーバー側かクライアント側か
void NetWork::Init(ConnectKind connectkind)
{
	// サーバーオブジェクトまたは、クライアントオブジェクトをすでに生成していれば、作り直す
	if (m_NetWork != 0)
	{
		m_NetWork->Close();
		m_NetWork->Delete();

		delete m_NetWork;
		m_NetWork = 0;
	}

	// 接続方法によって変える
	switch (connectkind)
	{
	case ConnectKind::Server:
		m_NetWork = new Server;
		break;
	case ConnectKind::Client:
		m_NetWork = new Client;
		break;
	default:
		break;
	}

	m_NetWork->Init();
	m_ConnectKind = connectkind; // 自分はサーバーかクライアントかを調べる用の情報
}

void NetWork::Delete()
{
	if (m_NetWork != 0)
	{
		m_NetWork->Delete();
		delete m_NetWork;
		m_NetWork = 0;
	}
}

// 接続関数を実行
// 戻り値 bool : 接続が成功したかどうか
bool NetWork::Connect()
{
	// 接続情報を入れる
	m_isNetWorkConnect = m_NetWork->Connect();
	return m_isNetWorkConnect;
}

// データを送る
// 引数1 char*		: 送りたいデータ
// 引数2 int		: 送りたいデータの大きさ
// 戻り値 SendState : 送信結果(サーバーとの接続切れもここで調べる)
SendState NetWork::Send(char* pData, int nDataLen)
{ 
	return m_NetWork->Send(pData, nDataLen);
}

// データを受け取る
// 引数1 char* : 受け取りたいデータ
// 引数2 int   : 受け取りたいデータの大きさ
// 戻り値 bool : 受け取り結果(サーバーとの接続切れもここで調べる)
RecvState NetWork::Recv(char* pData, int nDataLen)
{ 
	return m_NetWork->Recv(pData, nDataLen);
}

// 接続を閉じる関数を実行
void NetWork::Close()
{
	m_NetWork->Close();
}