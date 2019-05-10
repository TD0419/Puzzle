//�g�p����w�b�_�[�t�@�C��
#include "GameL/DrawTexture.h"
#include "CNextBlock.h"
#include "GameHead.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CNextBlock::Init()
{
	m_Px = 608.0f;
	m_Py = 0.0f;

	freeze_block_late = 0;
	generate_block_flag = false;


	m_block_num = 0;
}

void CNextBlock::Action()
{
	//�}�b�v�I�u�W�F�N�g�擾
	CMap* obj_map = (CMap*)Objs::GetObj(OBJ_MAP);
	//�u���b�N�I�u�W�F�N�g�擾
	Cblock* obj_block = (Cblock*)Objs::GetObj(OBJ_BLOCK);

	//�u���b�N�N���X��m_block_fall_ok�������Ă���
	generate_block_flag = obj_block->Getblock_fall();

	//FreezeBlock_Generate�̖߂�l���Ƃ��Ă���
	int freeze_time = obj_map->FreezeBlock_Generate();
	
	//freeze_time������Ȃ�������
	if (freeze_time != 0)
	{
		//freeze_time�ɑ������
		freeze_block_late = freeze_time;
	}

	//���ɗ��������̃t���O��true�Ȃ�
	if (generate_block_flag == true)
	{
		//freeze_block_late��0����Ȃ�������
		if (freeze_block_late > 0)
		{
			//1���炷
			freeze_block_late--;
		}
		else
		{
			//�u���b�N�̐��l�����߂�
			m_block_num = rand() % 6;

			//�V�����~�点��E���l���n��
			Cblock* p_block = new Cblock(m_block_num);
			Objs::InsertObj(p_block, OBJ_BLOCK, 1);

			//�����t���O��ς���
			generate_block_flag = false;
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
	dst.m_right = dst.m_left + 64.0f;
	dst.m_bottom = dst.m_top + 64.0f;

	Draw::Draw(15, &src, &dst, c, 0);
}