#include "NetWork.h"

#include <assert.h>

using namespace GameL;

void Server::Init()
{
	WSADATA wsadata;

	// winsock2�̏�����
	int nError = WSAStartup(MAKEWORD(2, 0), &wsadata);

	assert(nError == 0);
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
	// �\�P�b�gz�̍쐬
	m_ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	// �\�P�b�g�ݒ�
	struct sockaddr_in addr;
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_ServerSocket, (struct sockaddr*)&addr, sizeof(addr));

	// TCP�N���C�A���g����̐ڑ��v����҂Ă��Ԃɂ���
	listen(m_ServerSocket, 5);

	// TCP�N���C�A���g����̐ڑ��v�����󂯕t����
	struct sockaddr_in client;
	int nClientSize = sizeof(client);
	m_ClientSocket = accept(m_ServerSocket, (struct sockaddr*)&client, &nClientSize);

	if (m_ClientSocket == -1)
	{
		// �ڑ����s
		return false;
	}

	// �ڑ�����
	return true;
}

// �f�[�^�𑗂�
// ����1 char* : ���肽���f�[�^
// ����2 int   : ���肽���f�[�^�̑傫��
// �߂�l bool : ���M�����������ǂ���
bool Server::Send(char* pData, int nDataLen)
{
	if (send(m_ClientSocket, (const char*)pData, nDataLen, 0) > 0)
	{
		// ���M����
		return true;
	}

	// ���M���s
	return false;
}

// �f�[�^���󂯎��
// ����1 char* : �󂯎�肽���f�[�^
// ����2 int   : �󂯎�肽���f�[�^�̑傫��
// �߂�l bool : �󂯎�萬���������ǂ���
bool Server::Recv(char* pData, int nDataLen)
{
	if(recv(m_ClientSocket, pData, nDataLen, 0) > 0)
	{
		// �f�[�^�󂯎�萬��
		return true;
	}

	// �f�[�^�󂯎�莸�s
	return false;
}

// �T�[�o�[�Ƃ̐ڑ��Ւf
void Server::Close()
{
	// TCP�Z�b�V�����̏I��
	closesocket(m_ClientSocket);
}