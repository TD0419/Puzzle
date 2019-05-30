//�g�p����w�b�_�[�t�@�C��
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameL/SetWindow.h"
#include"GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

Cblock::Cblock(int num, float fPosX, CNextBlock* pNextBlock, CMap* pMap)
{
	if (num == 100)
	{
		m_bColornum = rand() % 6;
	}
	else
	{
		m_bColornum = num;
	}

	m_fPx = fPosX;

	m_pNextBlock = pNextBlock;
	m_pMap = pMap;
}

//�C�j�V�����C�Y
void Cblock::Init()
{
	m_fPy = MAP_SHIFT_Y;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bStop_flag = false;

	m_elementX_storage = (int)((m_fPx - m_pMap->GetShiftX()) / 32.f);
	m_elementY_storage = (int)((m_fPy - 192.f) / 32.f);

	m_Again_fall_on = false;
	m_block_fall_ok = false;
}

//�A�N�V����
void Cblock::Action()
{
	//��~�Ȃ�
	if (m_bStop_flag == true)
	{
		//�}�b�v�̃f�[�^���u���b�N�̏����Ŗ����Ȃ��Ă�����
		if (m_pMap->GetMap(m_elementX_storage, m_elementY_storage) == 0)
		{
			this->SetStatus(false);//�u���b�N����
		}

		//���Ƀu���b�N�������āA�����鏈���ŏ����Ă�����
		if (m_pMap->GetMap(m_elementX_storage, m_elementY_storage + 1) == 0)
		{
			//��~�t���O��؂��āA�ė���������
			m_bStop_flag = false;
			m_Again_fall_on = true;
			m_pMap->SetMap(m_elementX_storage, m_elementY_storage, 0);

			return;
		}

		return;
	}

	if (m_pMap->GetName() == OBJ_MAP)
	{
		char nKeyCode = 0;
		//A����������
		// XBOX�R�� �g�p�� if (Input::GetJoyButton(XBoxInput::UP) == true)
		if (m_Again_fall_on == false)
		{
			// �������u��
			if (Input::GetVKeyDown('A') == true)
			{
				nKeyCode = 'A';
			}
			else if (Input::GetVKeyDown('D') == true)
			{
				nKeyCode = 'D';
			}
		
			g_SendData.m_player_operation = nKeyCode;

			while (1)
			{
				SendState send_state = NetWork::Send((char*)&g_SendData, sizeof(g_SendData));
				// �ΐ푊��̃f�[�^���M����
				if (send_state == SendState::Send_Successful)
				{
					break;
				}
				// �ΐ푊��̒ʐM���r�₦���ꍇ
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

			Sleep(10);
		}

		// �ړ�������
		Move((int)nKeyCode);
	}
	else
	{
		int nTime = 0;
		char nKeyCode = 0;
		if (m_Again_fall_on == false)
		{
			while (1)
			{
				RecvState recv_state = NetWork::Recv((char*)&g_SendData, sizeof(g_SendData));
				
				// �ΐ푊��̃f�[�^�󂯎�萬��
				if (recv_state == RecvState::Recv_Successful || recv_state == RecvState::Recv_NoSend)
				{
					break;
				}
				// �ΐ푊��̒ʐM���r�₦���ꍇ
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
					return;
				}
			}

			// �������ۑ�
			nKeyCode = g_SendData.m_player_operation;
		}

		// �ړ�������
		Move((int)nKeyCode);
	}

	//�ʒu��32=1�̂悤�ɂ���
	m_elementX_storage = (int)((m_fPx - m_pMap->GetShiftX()) / 32.f);
	m_elementY_storage = (int)((m_fPy - 192.f) / 32.f);

	//�u���b�N����ԉ��ɒ�������~�߂�
	if (m_pMap->GetMap(m_elementX_storage, m_elementY_storage +1) != 0)
	{
		//�}�b�v�ɒ�~�����u���b�N�̏�������
		m_pMap->SetMap(m_elementX_storage, m_elementY_storage, m_bColornum + 1);

		m_pMap->confirmblock(m_elementX_storage, m_elementY_storage, m_bColornum + 1);

		m_bStop_flag = true;//��~�t���OON
		
		if (m_pMap->GetMap(6, 0) != 0)
		{
			Scene::SetScene(new CSceneResult(m_pMap));
		}
		
		//�ė������ɔ������Ȃ��悤��
		if (m_Again_fall_on == false)
		{
			//�����������[�̃t���O������
			m_block_fall_ok = true;
			
			//�����I�b�P�[�t���O���ς����������
			m_pNextBlock->Setblock_fall(m_block_fall_ok);
		}
	}
}

//�h���[
void Cblock::Draw()
{
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;//�؂���ʒu
	RECT_F dst;//�\���ʒu

	//�؂���ʒu�̐ݒ�
	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	dst.m_top = 0.0f + m_fPy;
	dst.m_left = 0.0f + m_fPx;
	dst.m_right = dst.m_left + 32.0f;
	dst.m_bottom = dst.m_top + 32.0f;

	//�F����
	if (m_bColornum == 0)
	{
		Draw::Draw(0, &src, &dst, c, 0.0f);//�I�����W
	}

	else if (m_bColornum == 1)
	{
		Draw::Draw(1, &src, &dst, c, 0.0f);//���F
	}

	else if (m_bColornum == 2)
	{
		Draw::Draw(2, &src, &dst, c, 0.0f);//���F
	}

	else if (m_bColornum == 3)
	{
		Draw::Draw(3, &src, &dst, c, 0.0f);//�I�����W��
	}

	else if (m_bColornum == 4)
	{
		Draw::Draw(4, &src, &dst, c, 0.0f);//���F��
	}

	else if (m_bColornum == 5)
	{
		Draw::Draw(5, &src, &dst, c, 0.0f);//���F��
	}
}

// �ړ��������܂Ƃ߂��֐�
void Cblock::Move(int nKeyCode)
{
	//�ړ��x�N�g��������
	m_fVy = 4.0f;
	m_fVx = 0.0f;

	//A����������
	// XBOX�R�� �g�p�� if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (nKeyCode == (int)'A')
	{
		//�ړ��悪160f��菬�����Ȃ�Ȃ�
		if (m_pMap->GetMap(m_elementX_storage - 1, m_elementY_storage + 1) != 0)
		{
			;//�������Ȃ�
		}
		else
		{
			m_fVx = -32.0f;//���ɓ���
		}
	}

	if (nKeyCode == (int)'D')
	{
		//�ړ��悪576f���傫���Ȃ邩��
		if (m_pMap->GetMap(m_elementX_storage + 1, m_elementY_storage + 1) != 0)
		{
			;//�������Ȃ�
		}
		else
		{
			m_fVx = 32.0f;//�E�ɓ���
		}
	}

	//�ړ��x�N�g�����Z
	m_fPy += m_fVy;
	m_fPx += m_fVx;
}