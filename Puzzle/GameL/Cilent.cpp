#include "NetWork.h"

#include <assert.h>

using namespace GameL;

void Client::Init()
{
	WSADATA wsaData;

	// winsock2�̏�����
	int nError = WSAStartup(MAKEWORD(2, 2), &wsaData);

	assert(nError == 0);
}

void Client::Delete()
{
	// Winsock2�̏I������
	WSACleanup();
}

// �T�[�o�[�ɐڑ�
// �߂�l bool : �ڑ��������������ǂ���
bool Client::Connect()
{
	// �\�P�b�g�쐬
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addr;
	memset(&addr, 0x00, sizeof(addr));
	addr.sin_family = AF_INET;				// IPv4
	addr.sin_addr.s_addr = inet_addr(IP);	// �ʐM����IP�A�h���X
	addr.sin_port = htons(PORT);			// �g�p����|�[�g�ݒ�
	
	// �����ŃT�[�o�[�ɐڑ�����
	if (connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr)) == 0)
	{
		// �ڑ�����
		return true;
	}

	// �ڑ����s
	return false;
}

// �f�[�^�𑗂�
// ����1 char* : ���肽���f�[�^
// ����2 int   : ���肽���f�[�^�̑傫��
// �߂�l bool : ���M�����������ǂ���
bool Client::Send(char* pData, int nDataLen)
{
	if (send(m_Socket, (const char*)pData, nDataLen, 0) > 0)
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
bool Client::Recv(char* pData, int nDataLen)
{
	if (recv(m_Socket, pData, nDataLen, 0) > 0)
	{
		// �f�[�^�󂯎�萬��
		return true;
	}

	// �f�[�^�󂯎�莸�s
	return false;
}

// �T�[�o�[�Ƃ̐ڑ��Ւf
void Client::Close()
{
	closesocket(m_Socket);
}