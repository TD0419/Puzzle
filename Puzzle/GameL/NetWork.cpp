#include "NetWork.h"

using namespace GameL;

NetWorkStandard* NetWork::m_NetWork = 0;
ConnectKind NetWork::m_ConnectKind;

// ����1 ConnectKind : �������T�[�o�[�����N���C�A���g����
void NetWork::Init(ConnectKind connectkind)
{
	// �ڑ����@�ɂ���ĕς���
	switch (connectkind)
	{
	case GameL::ConnectKind::Server:
		m_NetWork = new Server;
		break;
	case GameL::ConnectKind::Client:
		m_NetWork = new Client;
		break;
	default:
		break;
	}

	m_NetWork->Init();
	m_ConnectKind = connectkind;
}

void NetWork::Delete()
{
	if (m_NetWork != 0)
	{
		m_NetWork->Delete();
		delete m_NetWork;
	}
}

// �ڑ��֐������s
// �߂�l bool : �ڑ��������������ǂ���
bool NetWork::Connect()
{
	return m_NetWork->Connect();
}

// �f�[�^�𑗂�
// ����1 char* : ���肽���f�[�^
// ����2 int   : ���肽���f�[�^�̑傫��
// �߂�l bool : ���M�����������ǂ���
bool NetWork::Send(char* pData, int nDataLen)
{ 
	return m_NetWork->Send(pData, nDataLen); 
}

// �f�[�^���󂯎��
// ����1 char* : �󂯎�肽���f�[�^
// ����2 int   : �󂯎�肽���f�[�^�̑傫��
// �߂�l bool : �󂯎�萬���������ǂ���
bool NetWork::Recv(char* pData, int nDataLen)
{ 
	return m_NetWork->Recv(pData, nDataLen); 
}

// �ڑ������֐������s
void NetWork::Close()
{
	m_NetWork->Close();
}