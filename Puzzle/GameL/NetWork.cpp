#include "NetWork.h"

using namespace GameL;

SendData g_SendData;

NetWorkStandard* NetWork::m_NetWork = 0;
NetWork::ConnectKind NetWork::m_ConnectKind;
bool NetWork::m_isNetWorkConnect = false;

// ����1 ConnectKind : �������T�[�o�[�����N���C�A���g����
void NetWork::Init(ConnectKind connectkind)
{
	// �T�[�o�[�I�u�W�F�N�g�܂��́A�N���C�A���g�I�u�W�F�N�g�����łɐ������Ă���΁A��蒼��
	if (m_NetWork != 0)
	{
		m_NetWork->Close();
		m_NetWork->Delete();

		delete m_NetWork;
		m_NetWork = 0;
	}

	// �ڑ����@�ɂ���ĕς���
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
	m_ConnectKind = connectkind; // �����̓T�[�o�[���N���C�A���g���𒲂ׂ�p�̏��
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

// �ڑ��֐������s
// �߂�l bool : �ڑ��������������ǂ���
bool NetWork::Connect()
{
	// �ڑ���������
	m_isNetWorkConnect = m_NetWork->Connect();
	return m_isNetWorkConnect;
}

// �f�[�^�𑗂�
// ����1 char*		: ���肽���f�[�^
// ����2 int		: ���肽���f�[�^�̑傫��
// �߂�l SendState : ���M����(�T�[�o�[�Ƃ̐ڑ��؂�������Œ��ׂ�)
SendState NetWork::Send(char* pData, int nDataLen)
{ 
	return m_NetWork->Send(pData, nDataLen);
}

// �f�[�^���󂯎��
// ����1 char* : �󂯎�肽���f�[�^
// ����2 int   : �󂯎�肽���f�[�^�̑傫��
// �߂�l bool : �󂯎�茋��(�T�[�o�[�Ƃ̐ڑ��؂�������Œ��ׂ�)
RecvState NetWork::Recv(char* pData, int nDataLen)
{ 
	return m_NetWork->Recv(pData, nDataLen);
}

// �ڑ������֐������s
void NetWork::Close()
{
	m_NetWork->Close();
}