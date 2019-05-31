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
	addr.sin_addr.S_un.S_addr = inet_addr(IP);	// �ʐM����IP�A�h���X
	addr.sin_port = htons(PORT);			// �g�p����|�[�g�ݒ�

	// �m���u���b�L���O���[�h�ɂ���
	u_long val = 1;
	ioctlsocket(m_Socket, FIONBIO, &val);   // �\�P�b�g��I/O���[�h�𐧌�

	// �����ŃT�[�o�[�ɐڑ�����
	connect(m_Socket, (struct sockaddr*)&addr, sizeof(addr));

	if (m_Socket == INVALID_SOCKET)
	{
		// �ڑ����s
		return false;
	}

	Sleep(1000);

	// �������T�[�o�[�ɐڑ��ł��Ă��邩�̃e�X�g
	bool bData = false;

	while (1)
	{
		// �m�F�p�f�[�^�擾
		RecvState ReState = Recv((char*)&bData, sizeof(bData));
		
		if (ReState == RecvState::Recv_Successful)
		{
			break;
		}
		else if(ReState == RecvState::Connect_Cut)
		{
			// �T�[�o�[�������オ���Ă��܂���
			return false;
		}
	}

	// �ڑ�����
	return true;
}

// �f�[�^�𑗂�
// ����1 char*		: ���肽���f�[�^
// ����2 int		: ���肽���f�[�^�̑傫��
// �߂�l SendState : ���M�����������ǂ���
SendState Client::Send(char* pData, int nDataLen)
{
	if (send(m_Socket, (const char*)pData, nDataLen, 0) > 0)
	{
		// ���M����
		return SendState::Send_Successful;
	}

	int nError = WSAGetLastError();
	if (nError == WSAEWOULDBLOCK || nError == 0)
	{
		// �f�[�^���M��
		return SendState::Send_Middle;
	}

	// �f�[�^���M���s
	return SendState::Connect_Cut;
}

// �f�[�^���󂯎��
// ����1 char*		: �󂯎�肽���f�[�^
// ����2 int		: �󂯎�肽���f�[�^�̑傫��
// �߂�l RecvState : �󂯎��������(�T�[�o�[�Ƃ̐ڑ��؂�������Œ��ׂ�)
RecvState Client::Recv(char* pData, int nDataLen)
{
	if (recv(m_Socket, pData, nDataLen, 0) > 0)
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

	// �T�[�o�[�Ƃ̐ڑ����؂�Ă���
	return RecvState::Connect_Cut;
}

// �T�[�o�[�Ƃ̐ڑ��Ւf
void Client::Close()
{
	closesocket(m_Socket);
}