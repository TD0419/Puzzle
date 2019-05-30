//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "GameL/SceneManager.h"

#include "CNextBlock.h"
#include "GameHead.h"
#include <time.h>

//�g�p����l�[���X�y�[�X
using namespace GameL;

extern bool g_isNetWorkCut;

CNextBlock::CNextBlock(float a,CMap* pMap)
{
	m_Px = MAP_X * 32.0f + MAP_SHIFT_X + a;

	m_pMap = pMap;
}

void CNextBlock::Init()
{
	m_Py = MAP_SHIFT_Y;

	m_freeze_block_late = 0;
	m_generate_block_flag = false;

	// ������ς���
	if (NetWork::GetConnectKind() == NetWork::ConnectKind::Server)
	{
		srand((unsigned int)time(NULL));
	}
	else
	{
		srand((unsigned int)(time(NULL) + (unsigned int)1000));
	}

	// ���̃^�C�~���O�ł�GetName�ł͔���ł��Ȃ��̂ŁAGetShiftX���g�p���Ă���B
	if (m_pMap->GetShiftX() == 96)
	{
		m_block_num = rand() % 100;

		if (m_block_num < 40)
		{
			m_block_num = (rand() % 3) + 3;
		}
		else
		{
			m_block_num = rand() % 3;
		}

		// ��������u���b�N���𑗂�
		SendNextBlock(m_block_num);
	}
	else
	{
		// �ΐ푊��̎��̃u���b�N�����󂯎��
		m_block_num = RecvNextBlock();
	}

	Cblock* p_block = new Cblock(m_block_num, m_Px - 192.f, this, m_pMap);
	Objs::InsertObj(p_block, OBJ_BLOCK_2, 1);

	freeze_time = 0;
}

void CNextBlock::Action()
{
	if (m_generate_block_flag == true)
	{
		//FreezeBlock_Generate�̖߂�l���Ƃ��Ă���	
		freeze_time = m_pMap->FreezeBlock_Generate();
	}

	//freeze_time������Ȃ�������
	if (freeze_time != 0)
	{
		//freeze_time�ɑ������
		m_freeze_block_late = freeze_time;
	}

	//���ɗ��������̃t���O��true�Ȃ�
	if (m_generate_block_flag == true)
	{
		//freeze_block_late��0����Ȃ�������
		if (m_freeze_block_late > 0)
		{
			//1���炷
			m_freeze_block_late--;
		}
		else
		{
			Cblock* p_block = new Cblock(m_block_num, m_Px - 192.f,this, m_pMap);
			Objs::InsertObj(p_block, OBJ_BLOCK_2, 1);

			if (m_pMap->GetName() == OBJ_MAP)
			{
				//�u���b�N�̐��l�����߂�
				m_block_num = rand() % 100;

				if (m_block_num < 60)
				{
					m_block_num = (rand() % 3) + 3;
				}
				else
				{
					m_block_num = rand() % 3;
				}

				// ��������u���b�N���𑗂�
				SendNextBlock(m_block_num);
			}
			else
			{
				// �ΐ푊��̎��̃u���b�N�����󂯎��
				m_block_num = RecvNextBlock();
			}

			//�����t���O��ς���
			m_generate_block_flag = false;

			freeze_time = 0;
		}
	}

}

void CNextBlock::Draw()
{
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 64.0f;
	src.m_bottom = 64.0f;

	dst.m_top = 0.0f + m_Py;
	dst.m_left = 0.0f + m_Px;
	dst.m_right = dst.m_left + 96.0f;
	dst.m_bottom = dst.m_top + 96.0f;

	Draw::Draw(15, &src, &dst, c, 0);



	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	dst.m_top = 0.0f + m_Py + 32.0f;
	dst.m_left = 0.0f + m_Px + 32.0f;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	//�F����
	if (m_block_num == 0)
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);//�I�����W
	}

	else if (m_block_num == 1)
	{
		Draw::Draw(1, &src, &dst, c, 0.0f);//���F
	}

	else if (m_block_num == 2)
	{
		Draw::Draw(2, &src, &dst, c, 0.0f);//���F
	}

	else if (m_block_num == 3)
	{
		Draw::Draw(3, &src, &dst, c, 0.0f);//�I�����W��
	}

	else if (m_block_num == 4)
	{
		Draw::Draw(4, &src, &dst, c, 0.0f);//���F��
	}

	else if (m_block_num == 5)
	{
		Draw::Draw(5, &src, &dst, c, 0.0f);//���F��
	}
}

// �l�b�g���[�N���g�p�����A���̃u���b�N���𑗂�
// ����1 int : ���肽�����
void CNextBlock::SendNextBlock(int nNextBlock)
{
	g_SendData.m_generate_block = (char)nNextBlock;

	// ��������u���b�N���𑗂�
	while (1)
	{
		SendState send_state = NetWork::Send((char*)&g_SendData, sizeof(g_SendData));

		if (send_state == SendState::Send_Successful)
		{
			return;
		}
		else if (send_state == SendState::Connect_Cut)
		{
			if (NetWork::GetisNetWorkConnect() == true)
			{
				// �^�C�g���ɖ߂�
				Scene::SetScene(new CSceneTitle);

				// �ΐ푊��̒ʐM���r�₦���ꍇ
				MessageBox(NULL, L"�ΐ푊��Ƃ̒ʐM���r�₦�܂���", L"�ʐM�G���[", MB_OK);

				// �ڑ��؂�t���O�𗧂Ă�
				NetWork::NetWorkCut();
			}

			return;
		}
	}
}

// �l�b�g���[�N���g�p�����A���̃u���b�N�����󂯎��
// �߂�l int : �󂯎�����f�[�^��Ԃ� �f�[�^���Ȃ���΁A-1��Ԃ�
int CNextBlock::RecvNextBlock()
{
	int nTime = 0;
	// ��������u���b�N��񂪗���܂ő҂�
	while (1)
	{
		RecvState recv_state = NetWork::Recv((char*)&g_SendData, sizeof(g_SendData));
		if (recv_state == RecvState::Recv_Successful || recv_state == RecvState::Recv_NoSend)
		{
			break;
		}
		else if (recv_state == RecvState::Connect_Cut)
		{
			if (NetWork::GetisNetWorkConnect() == true)
			{
				// �^�C�g���ɖ߂�
				Scene::SetScene(new CSceneTitle);

				// �ΐ푊��̒ʐM���r�₦���ꍇ
				MessageBox(NULL, L"�ΐ푊��Ƃ̒ʐM���r�₦�܂���", L"�ʐM�G���[", MB_OK);

				// �ڑ��؂�t���O�𗧂Ă�
				NetWork::NetWorkCut();
			}

			return -1;
		}
	}

	return (int)g_SendData.m_generate_block;
}