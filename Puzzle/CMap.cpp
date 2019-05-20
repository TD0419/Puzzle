//�g�p����w�b�_�[�t�@�C��
#include "CMap.h"
#include "GameL/SceneObjManager.h"
#include "GameHead.h"

#include "CEffect.h"

//�g�p����l�[���X�y�[�X
using namespace GameL;


CMap::CMap(float a)
{
	m_shift_x = MAP_SHIFT_X + a;
	nextblock_class_pos = a;

	CNextBlock* m_nextblockclass = new CNextBlock(nextblock_class_pos, this);
	Objs::InsertObj(m_nextblockclass, OBJ_NEXT_BLOCK, 1);

	//�u���b�N�I�u�W�F�N�g�ǂݍ���
	Cblock* p_block = new Cblock(100, m_shift_x + (MAP_X * 32.0f / 2), m_nextblockclass, this);
	Objs::InsertObj(p_block, OBJ_BLOCK, 1);
}

void CMap::Init()
{
	int map[MAP_Y][MAP_X] =
	{
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99},
		{99,99,99,99,99,99,99,99,99,99,99, 99},
	};

	memcpy(m_map, map, sizeof(int) * MAP_Y * MAP_X);

	freezeblock_num = 0;
	delete_freezeblock = 0;
}

void CMap::Action()
{
	//// TCP�ł̃f�[�^�̎󂯓n�����@�̗�
	//if (NetWork::GetConnectKind() == NetWork::ConnectKind::Server)
	//{
	//	int data = 100;
	//	NetWork::Send((char*)&data, sizeof(data));
	//}
	//else if(NetWork::GetConnectKind() == NetWork::ConnectKind::Client)
	//{
	//	int data = 0;
	//	RecvState State = NetWork::Recv((char*)&data, sizeof(data));

	//	// �ؒf����Ă��Ȃ����̊m�F
	//	if (State == RecvState::Connect_Cut)
	//	{
	//		// �ؒf���ꂽ
	//		// �^�C�g���ɖ߂�
	//		Scene::SetScene(new CSceneTitle);
	//	}
	//}
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
			dst.m_top = MAP_SHIFT_Y + y * 32.0f;
			dst.m_left = m_shift_x + x * 32.0f;
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
	//�����Ŏg���֐�
	bool right_delete_check = true;
	bool left_delete_check = true;

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
		//1���܂��́A�Q�����}�b�v�O�̎��A�����I�Ƀ��[�v�𔲂���
		if (m_map[y + 1][x] == 99 || m_map[y + 2][x] == 99)
		{
			break;
		}

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
					//�P�}�X������ɂ��ז��u���b�N�������
					if (m_map[(y + m_del_under) - 1][x] == 8)
					{
						delete_freezeblock += 1;

						m_map[(y + m_del_under) - 1][x] = 0;
					}

					//�P�}�X�������ɂ��ז��u���b�N�������
					if (m_map[(y + m_del_under) + 1][x] == 8)
					{
						delete_freezeblock += 1;

						m_map[(y + m_del_under) + 1][x] = 0;
					}

					//�P�}�X�������ɂ��ז��u���b�N�������
					if (m_map[y + m_del_under][x - 1] == 8)
					{
						delete_freezeblock += 1;

						m_map[y + m_del_under][x - 1] = 0;
					}

					//�P�}�X�E�����ɂ��ז��u���b�N�������
					if (m_map[y + m_del_under][x + 1] == 8)
					{
						delete_freezeblock += 1;

						m_map[y + m_del_under][x + 1] = 0;
					}


					m_map[y + m_del_under][x] = 0;

					freezeblock_num += 1;
				}
			}

			// �G�t�F�N�g�̕\���ʒu
			RECT_F dst;
			dst.m_top = MAP_SHIFT_Y + y * 32.f;
			dst.m_left = m_shift_x + x * 32.f;
			dst.m_right = dst.m_left + 32.f;
			dst.m_bottom = MAP_SHIFT_Y + (y + m_search_under + 1) * 32.f;

			// �G�t�F�N�g�̐���
			CreateEffect(dst, 90.f);

			break;//�����F�̐��^�u���b�N��������������ɂ������ꍇ�A�����ق��������Ȃ��悤�ɂ��邽�߂ɒE�o
		}
	}

	//�u�����Ƃ�����E�����ɒ��ׂ�
	//m_search_right�E�E�E�����u���b�N�����邩�̌����A�l�̐ݒ�
	//m_del_right�E�E�E�u���b�N���������߂ɉ�for���̕ϐ�
	//5��܂ł�����
	for (int m_search_right = 2; m_search_right < 5; m_search_right++)
	{
		//1�E�܂��́A�Q�E���}�b�v�O�̎��A�����I�Ƀ��[�v�𔲂���
		if (m_map[y][x + 1] == 99 || m_map[y][x + 2] == 99)
		{
			break;
		}

		//������������
		if (m_map[y][x + m_search_right] == id)
		{
			for (int a = 1; a < m_search_right; a++)
			{
				//������ɋ󔒁i�u���b�N���Ȃ��j�Ȃ�S�������Ȃ�
				if (m_map[y][x + a] == 0)
				{
					right_delete_check = false;
					//break;//���[�v�E�o
				}
			}

			if (right_delete_check == true)
			{
				//�������ꏊ�܂ł̃u���b�N������
				for (int m_del_right = 0; m_del_right <= m_search_right; m_del_right++)
				{
					//�r���ɐF�̈Ⴄ���u���b�N�������
					if (m_map[y][x + m_del_right] >= 4 && m_map[y][x + m_del_right] != id)
					{
						;//�X���[
					}
					else
					{
						//�P�}�X������ɂ��ז��u���b�N�������
						if (m_map[y - 1][x + m_del_right] == 8)
						{
							delete_freezeblock += 1;

							m_map[y - 1][x + m_del_right] = 0;
						}

						//�P�}�X�������ɂ��ז��u���b�N�������
						if (m_map[y + 1][x + m_del_right] == 8)
						{
							delete_freezeblock += 1;

							m_map[y + 1][x + m_del_right] = 0;
						}

						//�P�}�X�������ɂ��ז��u���b�N�������
						if (m_map[y][(x + m_del_right) - 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x + m_del_right) - 1] = 0;
						}

						//�P�}�X�E�����ɂ��ז��u���b�N�������
						if (m_map[y][(x + m_del_right) + 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x + m_del_right) + 1] = 0;
						}

						m_map[y][x + m_del_right] = 0;

						freezeblock_num += 1;

					}
				}
			}
			// �G�t�F�N�g�̕\���ʒu��ݒ�
			RECT_F dst;
			dst.m_top = MAP_SHIFT_Y + y * 32.f;
			dst.m_left = m_shift_x + x * 32.f;
			dst.m_right = m_shift_x + (x + m_search_right + 1) * 32.f;
			dst.m_bottom = dst.m_top + 32.f;

			// �G�t�F�N�g�𐶐�
			CreateEffect(dst, 180.f);

			break;//�����F�̐��^�u���b�N��������������ɂ������ꍇ�A�����ق��������Ȃ��悤�ɂ��邽�߂ɒE�o
		}
	}

	//�u�����Ƃ����獶�����ɒ��ׂ�
	//m_search_left�E�E�E�����u���b�N�����邩�̌����A�l�̐ݒ�
	//m_del_left�E�E�E�u���b�N���������߂ɉ�for���̕ϐ�
	//5��܂ł�����
	for (int m_search_left = 2; m_search_left < 5; m_search_left++)
	{
		//1���܂��́A�Q�����}�b�v�O�̎��A�����I�Ƀ��[�v�𔲂���
		if (m_map[y][x - 1] == 99 || m_map[y][x - 2] == 99)
		{
			break;
		}

		//������������
		if (m_map[y][x - m_search_left] == id)
		{
			for (int a = 1; a < m_search_left; a++)
			{
				//������ɋ󔒁i�u���b�N���Ȃ��j�Ȃ�S�������Ȃ�
				if (m_map[y][x - a] == 0)
				{
					left_delete_check = false;
					//break;//���[�v�E�o
				}
			}

			if (left_delete_check == true)
			{
				//�������ꏊ�܂ł̃u���b�N������
				for (int m_del_left = 0; m_del_left <= m_search_left; m_del_left++)
				{
					//�r���ɐF�̈Ⴄ���u���b�N�������
					if (m_map[y][x - m_del_left] >= 4 && m_map[y][x - m_del_left] != id)
					{
						;
					}
					else
					{
						//�P�}�X������ɂ��ז��u���b�N�������
						if (m_map[y - 1][x - m_del_left] == 8)
						{
							delete_freezeblock += 1;

							m_map[y - 1][x - m_del_left] = 0;
						}

						//�P�}�X�������ɂ��ז��u���b�N�������
						if (m_map[y + 1][x - m_del_left] == 8)
						{
							delete_freezeblock += 1;

							m_map[y + 1][x - m_del_left] = 0;
						}

						//�P�}�X�������ɂ��ז��u���b�N�������
						if (m_map[y][(x - m_del_left) - 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x - m_del_left) - 1] = 0;
						}

						//�P�}�X�E�����ɂ��ז��u���b�N�������
						if (m_map[y][(x - m_del_left) + 1] == 8)
						{
							delete_freezeblock += 1;

							m_map[y][(x - m_del_left) + 1] = 0;
						}

						m_map[y][x - m_del_left] = 0;

						freezeblock_num += 1;
					}
				}
			}

			// �G�t�F�N�g�̕\���ʒu��ݒ�
			RECT_F dst;
			dst.m_top = MAP_SHIFT_Y + y * 32.f;
			dst.m_left = m_shift_x + (x - m_search_left) * 32.f;
			dst.m_right = m_shift_x + (x + 1) * 32.f;
			dst.m_bottom = dst.m_top + 32.f;

			// �G�t�F�N�g�𐶐�
			CreateEffect(dst, 0.f);

			break;//�����F�̐��^�u���b�N��������������ɂ������ꍇ�A�����ق��������Ȃ��悤�ɂ��邽�߂ɒE�o
		}
	}

	freezeblock_num += delete_freezeblock / 2;//���ז��u���b�N�����̑����ɏ��������ז��u���b�N�̔�����ǉ�����

	delete_freezeblock = 0;
	
	return;
}

bool CMap::FreezeBlock_Check()
{
	//if (freezeblock_num != 0)
	//{
	//	return true;
	//}

	return false;
}

//���ז��u���b�N����
int CMap::FreezeBlock_Generate()
{
	//���ז��u���b�N�����������̃u���b�N���ǂ��ɂ��邩���ׂ�p�֐�
	int y_num = 0;

	//���ז��u���b�N�̐����O����Ȃ�������
	if (freezeblock_num != 0)
	{
		//���ז��u���b�N�̐�����
		for (int freeze_x = 0; freeze_x < freezeblock_num; freeze_x++)
		{
			//����ɂ����ԏ�̃u���b�N�̈ʒu�𒲂ׂ�
			for (int y = 0; y < 18; y++)
			{
				if (m_map[y][freeze_x + 1] != 0)
				{
					if (y_num < y)
					{
						//���܂ł̐������傫���Ȃ炻��ɂ���
						y_num = y;

						break;
					}
				}
			}

			//���ז��u���b�N�o��
			CFreezeblock* p_fblock = new CFreezeblock(freeze_x + 1,0,8);
			Objs::InsertObj(p_fblock, OBJ_FREEZE_BLOCK, 1);

		}

		//���ז��u���b�N�̐����Ȃ���
		freezeblock_num = 0;
	}

	//���ז��u���b�N����������t���[������Ԃ�
	return y_num * 32 / 4;
}

// �G�t�F�N�g�𐶐�����
// ����1 RECT_F : �G�t�F�N�g�̕\���ʒu
// ����2 float  : �G�t�F�N�g�̊p�x(�x���@)
void CMap::CreateEffect(RECT_F dst, float fRotation)
{
	// �G�t�F�N�g�̐؂���ʒu
	RECT_F src;
	src.m_top = 0.f;
	src.m_left = 0.f;
	src.m_right = 512.f;
	src.m_bottom = 512.f;
	float fWhiteColor[4] = { 1.f,1.f,1.f,1.f };			// ���F
	float fTranslucentColor[4] = { 1.f,1.f,1.f,0.5f };  // ������

	// �G�t�F�N�g��\������V�X�e��
	CEffectSystem* pEffectSystem = new CEffectSystem(new CExEffect(11, &src, &dst, 15, fTranslucentColor, fWhiteColor, fRotation));
	CSceneObjManager::InsertObj(pEffectSystem, 100, 10);
	// ���ɕ\���������G�t�F�N�g��ǉ�
	pEffectSystem->AddNextEffect(new CExEffect(12, &src, &dst, 20, fWhiteColor, fWhiteColor, fRotation));
	pEffectSystem->AddNextEffect(new CExEffect(13, &src, &dst, 15, fWhiteColor, fTranslucentColor, fRotation));
}