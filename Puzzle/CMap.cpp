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

	//�u�����Ƃ����牺�����ɒ��ׂ�
	//m_search_under�E�E�E�����u���b�N�����邩�̌����A�l�̐ݒ�
	//m_del_under�E�E�E�u���b�N���������߂ɉ�for���̕ϐ�
	//5��܂ł�����
	for (int m_search_under = 2; m_search_under < 5; m_search_under++)
	{
		//������������
		if (m_map[y + m_search_under][x] == id)
		{
			//�������ꏊ�܂ł̃u���b�N������
			for (int m_del_under = 0; m_del_under <= m_search_under; m_del_under++)
			{
				//�r���ɐF�̈Ⴄ���u���b�N�������
				if (m_map[y + m_del_under][x] >= 4 && m_map[y + m_del_under][x] != id)
				{
					;//�X���[
				}
				else
				{
					m_map[y + m_del_under][x] = 0;
				}
			}

			break;//2�ȏ゠�����ꍇ�A�����Ȃ��悤�ɂ��邽�߂ɒE�o
		}
	}

	//�u�����Ƃ�����E�����ɒ��ׂ�
	//m_search_right�E�E�E�����u���b�N�����邩�̌����A�l�̐ݒ�
	//m_del_right�E�E�E�u���b�N���������߂ɉ�for���̕ϐ�
	//5��܂ł�����
	for (int m_search_right = 2; m_search_right < 5; m_search_right++)
	{
		//������������
		if (m_map[y][x + m_search_right] == id)
		{
			//�������ꏊ�܂ł̃u���b�N������
			for (int m_del_right = 0; m_del_right <= m_search_right; m_del_right++)
			{
				//������ɋ󔒁i�u���b�N���Ȃ��j�Ȃ�S�������Ȃ�
				if (m_map[y][x + m_del_right + 1] == 0 || m_map[y][x + m_del_right + 2] == 0 || m_map[y][x + m_del_right + 3] == 0)
				{
					break;//���[�v�E�o
				}

				//�r���ɐF�̈Ⴄ���u���b�N�������
				if (m_map[y][x + m_del_right] >= 4 && m_map[y][x + m_del_right] != id)
				{
					;//�X���[
				}
				else
				{
					m_map[y][x + m_del_right] = 0;
				}
			}

			break;//2�ȏ゠�����ꍇ�A�����Ȃ��悤�ɂ��邽�߂ɒE�o
		}
	}

	//�u�����Ƃ����獶�����ɒ��ׂ�
	//m_search_left�E�E�E�����u���b�N�����邩�̌����A�l�̐ݒ�
	//m_del_left�E�E�E�u���b�N���������߂ɉ�for���̕ϐ�
	//5��܂ł�����
	for (int m_search_left = 2; m_search_left < 5; m_search_left++)
	{
		//������������
		if (m_map[y][x - m_search_left] == id)
		{
			//�������ꏊ�܂ł̃u���b�N������
			for (int m_del_left = 0; m_del_left <= m_search_left; m_del_left++)
			{
				//������ɋ󔒁i�u���b�N���Ȃ��j�Ȃ�S�������Ȃ�
				if (m_map[y][x - m_del_left - 1] == 0 || m_map[y][x - m_del_left - 2] == 0 || m_map[y][x - m_del_left - 3] == 0)
				{
					break;//���[�v�E�o
				}

				//�r���ɐF�̈Ⴄ���u���b�N�������
				if (m_map[y][x - m_del_left] >= 4 && m_map[y][x - m_del_left] != id)
				{
					;
				}
				else
				{
					m_map[y][x - m_del_left] = 0;
				}
			}

			break;//2�ȏ゠�����ꍇ�A�����Ȃ��悤�ɂ��邽�߂ɒE�o
		}
	}

	return;
}