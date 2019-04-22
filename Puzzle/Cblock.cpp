//�g�p����w�b�_�[�t�@�C��
#include"Cblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameL/SetWindow.h"
#include"GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

//�C�j�V�����C�Y
void Cblock::Init()
{
	m_fPx = 416.0f;
	m_fPy = 32.0f;
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bColornum = rand() % 6;//�F���߂̂��߂̃����_��

	m_bStop_flag = false;

	m_a_key_push = false;
	m_d_key_push = false;

	m_elementX_storage = 0;
	m_elementY_storage = 0;

	m_Again_fall_on = false;
}

//�A�N�V����
void Cblock::Action()
{
	//�}�b�v�I�u�W�F�N�g�擾
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);

	//��~�Ȃ�
	if (m_bStop_flag == true)
	{
		//�}�b�v�̃f�[�^���u���b�N�̏����Ŗ����Ȃ��Ă�����
		if (obj_map->GetMap(m_elementX_storage, m_elementY_storage) == 0)
		{
			this->SetStatus(false);//�u���b�N����
		}

		//���Ƀu���b�N�������āA�����鏈���ŏ����Ă�����
		if (obj_map->GetMap(m_elementX_storage, m_elementY_storage + 1) == 0)
		{
			//��~�t���O��؂��āA�ė���������
			m_bStop_flag = false;
			m_Again_fall_on = true;
			obj_map->SetMap(m_elementX_storage, m_elementY_storage, 0);

			return;
		}

		return;//�Ƃ肠�����������Ȃ�
	}


	//�ړ��x�N�g��������
	m_fVy = 2.0f;
	m_fVx = 0.0f;

	//�ʒu��32=1�̂悤�ɂ���
	int x = ((int)m_fPx - 160) / 32;
	int y = (int)m_fPy / 32;

	//A����������
	// XBOX�R�� �g�p�� if (Input::GetJoyButton(XBoxInput::UP) == true)
	if (Input::GetVKey('A') == true)
	{
		//�������h�~
		//�ė������ɓ���Ȃ��悤��
		if (m_a_key_push == false && m_Again_fall_on == false)
		{
			//�ړ��悪160f��菬�����Ȃ�Ȃ�
			if (obj_map->GetMap(x - 1, y+1) != 0)
			{
				;//�������Ȃ�
			}
			else
			{
				m_fVx = -32.0f;//���ɓ���

				m_a_key_push = true;
			}
		}
	}
	else
	{
		m_a_key_push = false;
	}


	//D����������
	if (Input::GetVKey('D') == true)
	{
		//�������h�~
		//�ė������ɓ���Ȃ��悤��
		if (m_d_key_push == false && m_Again_fall_on == false)
		{
			//�ړ��悪576f���傫���Ȃ邩��
			if (obj_map->GetMap(x + 1, y+1) != 0)
			{
				;//�������Ȃ�
			}
			else
			{
				m_fVx = 32.0f;//�E�ɓ���

				m_d_key_push = true;
			}
		}
	}
	else
	{
		m_d_key_push = false;
	}



	//�ړ��x�N�g�����Z
	m_fPx += m_fVx;
	m_fPy += m_fVy;

	//�u���b�N����ԉ��ɒ�������~�߂�
	if ( obj_map->GetMap(x,y+1) != 0/*383.0f-32.0f*//*(float)Window::GetHeight() - 32.0f*/)
	{
		//�ړ��x�N�g����~
		//m_fVy = 0.0f;
		//m_fVx = 0.0f;

		//��~�����u���b�N�̗v�f�ԍ���ۑ�����
		m_elementX_storage = x;
		m_elementY_storage = y;

		//�}�b�v�ɒ�~�����u���b�N�̏�������
		obj_map->SetMap(x, y, m_bColornum + 1);


		obj_map->confirmblock(x, y, m_bColornum + 1);

		m_bStop_flag = true;//��~�t���OON

		//�ė������ɔ������Ȃ��悤��
		if (m_Again_fall_on == false)
		{
			//�V�����~�点��
			Cblock* p_block = new Cblock();
			Objs::InsertObj(p_block, OBJ_BLOCK, 1);
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