#pragma once

//STL�f�o�b�O�@�\��OFF�ɂ���
#define _SECURE_SCL	(0)  
#define _HAS_ITERATOR_DEBUGGING	(0)  

#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

constexpr auto PORT = (12345);
constexpr auto IP = ("127.0.0.1");

namespace GameL
{
	// �f�[�^�󂯎�茋��
	enum class RecvState
	{
		Recv_Successful, // �󂯎�萬��
		Recv_Middle,	 // �󂯎�蒆
		Connect_Cut		 // ����Ƃ̐ڑ����؂��
	};

	// �l�b�g���[�N���g�����߂ɕK�v�Ȃ���
	class NetWorkStandard
	{
	public:
		virtual void Init() = 0;
		virtual bool Connect() = 0;								// �T�[�o�[�ɐڑ�
		virtual bool Send(char* pData, int nDataLen) = 0;		// �f�[�^�𑗂�
		virtual RecvState Recv(char* pData, int nDataLen) = 0;	// �f�[�^���󂯎��
		virtual void Close() = 0;								// �ڑ����Ւf����
		virtual void Delete() = 0;
	};

	// �T�[�o�[���
	class Server : public NetWorkStandard
	{
	public:
		void Init();
		bool Connect();							// �N���C�A���g�ɐڑ�
		bool Send(char* pData, int nDataLen);	// �f�[�^�𑗂�
		RecvState Recv(char* pData, int nDataLen);	// �f�[�^���󂯎��
		void Close();							// �ڑ����Ւf����
		void Delete();

	private:
		SOCKET m_ServerSocket;			
		SOCKET m_ClientSocket;			
	};

	// �N���C�A���g���
	class Client : public NetWorkStandard
	{
	public:
		void Init();
		bool Connect();							// �T�[�o�[�ɐڑ�
		bool Send(char* pData, int nDataLen);	// �f�[�^�𑗂�
		RecvState Recv(char* pData, int nDataLen);	// �f�[�^���󂯎��
		void Close();							// �ڑ����Ւf����
		void Delete();

	private:
		SOCKET m_Socket;						// �T�[�o�[�ɐڑ����邽�߂̃\�P�b�g
	};

	// �l�b�g���[�N���Ǘ�����N���X(�l�b�g���[�N���g�p����ۂ�������g��)
	class NetWork
	{
	public:
		// �����̎��
		enum class ConnectKind
		{
			Server,
			Client,
		};

	public:
		static void Init(ConnectKind connectkind);
		static bool Connect();							  // �ڑ�
		static bool Send(char* pData, int nDataLen);	  // �f�[�^�𑗂�
		static RecvState Recv(char* pData, int nDataLen); // �f�[�^���󂯎��
		static void Close();							  // �ڑ����Ւf����
		static void Delete();
		static ConnectKind GetConnectKind() { return m_ConnectKind;  }

	private:
		static NetWorkStandard* m_NetWork;
		static ConnectKind m_ConnectKind;
	};
}