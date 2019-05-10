#include "NetWork.h"

#include <assert.h>

using namespace GameL;

void Server::Init()
{
	WSADATA wsadata;

	// winsock2�̏�����
	int nError = WSAStartup(MAKEWORD(2, 2), &wsadata);

	assert(nError == 0);

	// �\�P�b�g�̍쐬
	m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	// �\�P�b�g�ݒ�
	struct sockaddr_in addr;
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_ServerSocket, (struct sockaddr*)&addr, sizeof(addr));

	// TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	listen(m_ServerSocket, 1);

	// �m���u���b�L���O���[�h�ɂ���
	u_long val = 1;
	ioctlsocket(m_ServerSocket, FIONBIO, &val); // �\�P�b�g��I/O���[�h�𐧌�
}

void Server::Delete()
{
	// Winsock2�̏I������
	WSACleanup();
}

// �N���C�A���g�ɐڑ�
// �߂�l bool : �ڑ��������������ǂ���
bool Server::Connect()
{
	// TCP�N���C�A���g����̐ڑ��v�����󂯕t����
	struct sockaddr_in client;
	int nClientSize = sizeof(client);
	m_ClientSocket = accept(m_ServerSocket, (struct sockaddr*)&client, &nClientSize);

	if (m_ClientSocket == INVALID_SOCKET)
	{
		// �ڑ����s
		return false;
	}

	// �ڑ��������������ǂ����̊m�F�p�̃f�[�^�𑗂�
	bool bData = true;
	Send((char*)&bData, sizeof(bData));

	int nError = WSAGetLastError();
	
	// �f�[�^������Ă��邩�ǂ����̊m�F
	if (nError == WSAEWOULDBLOCK || nError == 0)
	{
		// �ڑ�����
		return true;
	}

	return false;
}

// �f�[�^�𑗂�
// ����1 char* : ���肽���f�[�^
// ����2 int   : ���肽���f�[�^�̑傫��
// �߂�l bool : ���M�����������ǂ���
bool Server::Send(char* pData, int nDataLen)
{
	if (send(m_ClientSocket, (const char*)pData, nDataLen, 0) > 0)
	{
		// �f�[�^���M����
		return true;
	}

	// �f�[�^���M���s
	return false;
}

// �f�[�^���󂯎��
// ����1 char* : �󂯎�肽���f�[�^
// ����2 int   : �󂯎�肽���f�[�^�̑傫��
// �߂�l bool : �󂯎�萬���������ǂ���
RecvState Server::Recv(char* pData, int nDataLen)
{
	if(recv(m_ClientSocket, pData, nDataLen, 0) > 0)
	{
		// �f�[�^�󂯎�萬��
		return RecvState::Recv_Successful;
	}

	int nError = WSAGetLastError();
	if (nError == WSAEWOULDBLOCK || nError == 0)
	{
		// �f�[�^�󂯎�蒆
		return RecvState::Recv_Middle;
	}

	// �f�[�^�󂯎�莸�s
	return RecvState::Connect_Cut;
}

// �T�[�o�[�Ƃ̐ڑ��Ւf
void Server::Close()
{
	// TCP�Z�b�V�����̏I��
	closesocket(m_ClientSocket);
}