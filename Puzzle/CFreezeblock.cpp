//�g�p����w�b�_�[�t�@�C��
#include"CFreezeblock.h"
#include"GameL/DrawTexture.h"
#include"GameL/SceneObjManager.h"
#include"GameL/WinInputs.h"
#include"GameHead.h"


//�g�p����l�[���X�y�[�X
using namespace GameL;


CFreezeblock::CFreezeblock(int x,int y,int id, CMap* pMap)
{
	if (pMap->GetName() == OBJ_MAP)
	{
		m_fPx = x * 32.0f + MAP_SHIFT_X;
	}
	else if (pMap->GetName() == OBJ_MAP_PLAY2)
	{
		m_fPx = x * 32.0f + MAP_SHIFT_X + 620.0f;
	}

	m_fPy = y * 32.0f + MAP_SHIFT_Y;
	m_bColornum = id;
	m_elementX_storage = x;
	m_elementY_storage = y;

	m_pMap = pMap;
}

//�C�j�V�����C�Y
void CFreezeblock::Init()
{
	m_fVx = 0.0f;
	m_fVy = 0.0f;

	m_bStop_flag = false;
}

//�A�N�V����
void CFreezeblock::Action()
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
			//m_Again_fall_on = true;
			m_pMap->SetMap(m_elementX_storage, m_elementY_storage, 0);

			return;
		}

		return;//�Ƃ肠�����������Ȃ�
	}


	//�ړ��x�N�g���ݒ�
	m_fVy = 4.0f;

	//�x�N�g�����Z
	m_fPy += m_fVy;

	int x = (int)((m_fPx - m_pMap->GetShiftX()) / 32.f);
	int y = (int)((m_fPy - 192) / 32.f);

	//�u���b�N����ԉ��ɒ�������~�߂�
	if (m_pMap->GetMap(x, y + 1) != 0)
	{
		//��~�����u���b�N�̗v�f�ԍ���ۑ�����
		m_elementX_storage = x;
		m_elementY_storage = y;

		//�}�b�v�ɒ�~�����u���b�N�̏�������
		m_pMap->SetMap(x, y, m_bColornum);

		m_bStop_flag = true;//��~�t���OON
	}
}

//�h���[
void CFreezeblock::Draw()
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
	Draw::Draw(8, &src, &dst, c, 0.0f);

}