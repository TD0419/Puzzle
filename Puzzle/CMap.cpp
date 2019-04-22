//�g�p����w�b�_�[�t�@�C��
#include "CMap.h"
#include "GameL/SceneObjManager.h"
#include "GameL/DrawTexture.h"
#include "GameHead.h"

#include "CEffect.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;

void CMap::Init()
{
	int map[MAP_Y][MAP_X] =
	{
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,99},
		{99,99,99,99,99,99,99,99,99,99,99,99,99,99},
	};

	memcpy(m_map, map, sizeof(int) * MAP_Y * MAP_X);

	//// �G�t�F�N�g�g�p��
	//RECT_F src, dst, dst2;
	//src.m_top = 0.f;
	//src.m_left = 0.f;
	//src.m_right = 64.f;
	//src.m_bottom = 64.f;
	//dst.m_top = 32.f;
	//dst.m_left = 32.f;
	//dst.m_right = 64.f;
	//dst.m_bottom = 64.f;
	//dst2.m_top = 0.f;
	//dst2.m_left = 0.f;
	//dst2.m_right = 96.f;
	//dst2.m_bottom = 96.f;
	//float c1[4] = { 1.f,1.f,1.f,0.5f };
	//float c2[4] = { 1.f,1.f,1.f,1.f };
	//float c3[4] = { 1.f,1.f,1.f,0.f };
	//// �G�t�F�N�g��\������V�X�e��
	//CEffectSystem* pEffectSystem = new CEffectSystem(new CExEffect(11, &src, &dst, 50, c1, c2, &dst2));
	//CSceneObjManager::InsertObj(pEffectSystem, 100, 10);
	//// ���ɕ\���������G�t�F�N�g��ǉ�
	//pEffectSystem->AddNextEffect(new CExEffect(11, &src, &dst2, 10, c2, c3));
}

void CMap::Action()
{


}

void CMap::Draw()
{
	//�J���[���
	float c[4] = { 1.0f,1.0f,1.0f,1.0f };

	RECT_F src;
	RECT_F dst;

	src.m_top = 0.0f;
	src.m_left = 0.0f;
	src.m_right = 32.0f;
	src.m_bottom = 32.0f;

	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			dst.m_top = 0.0f + y * 32.0f;
			dst.m_left = 160.0f + x * 32.0f;
			dst.m_right = dst.m_left + 32.0f;
			dst.m_bottom = dst.m_top + 32.0f;

			if (m_map[y][x] == 99)
			{
				Draw::Draw(10, &src, &dst, c, 0.0f);
			}
		}
	}
}


//�ړ��ł���悤��x,y�̒l���������l�����ׂ�֐�
int CMap::GetMap(int x, int y)
{
	//x,y����O�Ȓl�̏ꍇ�A-1��Ԃ�
	if (x < 0)
	{
		return -1;
	}

	if (y < 0)
	{
		return -1;
	}

	if (x >= MAP_X)
	{
		return -1;
	}

	if (y >= MAP_Y)
	{
		return -1;
	}

	//�v�f��Ԃ�
	return m_map[y][x];
}

//�����Ȃ��Ȃ����u���b�N���}�b�v�Ɋi�[����֐�
void CMap::SetMap(int x, int y, int id)
{
	//x,y����O�Ȓl�̏ꍇ�A-1��Ԃ�
	if (x < 0)
	{
		return ;
	}

	if (y < 0)
	{
		return ;
	}

	if (x >= MAP_X)
	{
		return ;
	}

	if (y >= MAP_Y)
	{
		return ;
	}

	m_map[y][x] = id;

	return;
}

//�E�E���E���ɓ����u���b�N�����邩���ׂ�
void CMap::confirmblock(int x, int y, int id)
{
	//�u���b�N�����^����Ȃ�������
	if (id <= 3)
	{
		return;//���ׂ��I��
	}

	//������
	if (m_map[y + 2][x] == id)
	{
		for (int a = 0; a <= 2; a++)
		{
			m_map[y + a][x] = 0;
		}
	}

	//�E����
	if (m_map[y][x + 2] == id)
	{
		for (int a = 0; a <= 2; a++)
		{
			m_map[y][x + a] = 0;
		}
	}

	//������
	if (m_map[y][x - 2] == id)
	{
		for (int a = 0; a <= 2; a++)
		{
			m_map[y][x - a] = 0;
		}
	}

	return;
}