//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "CNextBlock.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CNextBlock::Init()
{

	m_Px = MAP_X * 32.0f + 160.0f;
	m_Py = MAP_SHIFT_Y;

	m_freeze_block_late = 0;
	m_generate_block_flag = false;

	m_block_num = rand() % 6;

}

void CNextBlock::Action()
{
	//�}�b�v�I�u�W�F�N�g�擾
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);
	//�u���b�N�I�u�W�F�N�g�擾
	Cblock* obj_block = (Cblock*)Objs::GetObj(OBJ_BLOCK);

	//FreezeBlock_Generate�̖߂�l���Ƃ��Ă���
	int freeze_time = obj_map->FreezeBlock_Generate();
	
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
			//�V�����~�点��E���l���n��
			Cblock* p_block = new Cblock(m_block_num);
			Objs::InsertObj(p_block, OBJ_BLOCK, 1);

			//�u���b�N�̐��l�����߂�
			m_block_num = rand() % 6;


			//�����t���O��ς���
			m_generate_block_flag = false;
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