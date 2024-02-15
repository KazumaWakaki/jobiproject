//=============================================================================
//
// �u���b�N3D���� [block3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "block3D.h"
#include "manager.h"
#include "player3D.h"
#include "enemy3D.h"
#include "bullet3D.h"
#include "explosion.h"

//�}�N����`
#define CORRECTION	(6.0f)  //���̓����蔻��␳

//�ÓI�����o�ϐ�
CBlock3D *CBlock3D::m_apObject[MAX_BLOCK] = {};

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CBlock3D::CBlock3D()
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		if (m_apObject[nCnt] == NULL)
		{
			m_apObject[nCnt] = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CBlock3D::~CBlock3D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CBlock3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //���f���̃|�C���^

	m_nIdxModel[BLOCK_NEONFLOOR] = pModel->Regist("data\\MODEL\\neonfloor001.x");  //���u���b�N
	m_nIdxModel[BLOCK_NEON] = pModel->Regist("data\\MODEL\\neonwall001.x");  //�l�I���u���b�N
	m_nIdxModel[BLOCK_NEONWALL] = pModel->Regist("data\\MODEL\\runwall001.x");  //�l�I���u���b�N

	//���f���̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_BLOCK);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CBlock3D::Uninit()
{
	int nID = m_nID;

	//�I�u�W�F�N�g�̍폜����
	CObjectX::Uninit();

	if (m_apObject[nID] != NULL)
	{
		m_apObject[nID] = NULL;
	}
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CBlock3D::Update()
{
	//�e�Ƃ̓����蔻��
	//CBullet3D::CollisionBlock(this);
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CBlock3D::Draw()
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CBlock3D *CBlock3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int SetTypeTex)
{
	CBlock3D *pBlock3D = nullptr;

	//�u���b�N�̐���
	pBlock3D = new CBlock3D;

	if (pBlock3D != nullptr)
	{
		//����������
		pBlock3D->Init();

		//�ʒu�̐ݒ�
		pBlock3D->SetPosition(pos);

		//�����̐ݒ�
		pBlock3D->SetRotation(rot);

		//�g�嗦�̐ݒ�
		pBlock3D->SetScale(scale);

		//�e�N�X�`���^�C�v
		pBlock3D->SetTypeTex(SetTypeTex);

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//���f���̊��蓖��
				pBlock3D->BindModel(pBlock3D->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBlock3D;
}
//-------------------------------------------------------
//�v���C���[�Ƃ̓����蔻��
//-------------------------------------------------------
bool CBlock3D::CollisionPlayer(CPlayer3D *pPlayer)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInstance()->GetInputPad();

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�u���b�N�̈ʒu�̎擾
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 m_Scale = m_apObject[nCnt]->GetScale();  //�u���b�N�̊g�嗦�̎擾
			CObject::TYPE type;  //���
			int typetex = m_apObject[nCnt]->GetTypeTex();  //�G�̎�ގ擾

			//��ނ��擾
			type = pPlayer->GetType();

			//��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu
				D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //�v���C���[�̉ߋ��̈ʒu
				D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //�v���C���[�̈ړ���
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //�v���C���[�̌���
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //�v���C���[�̊g�嗦

				//�l�I����
				if (typetex == BLOCK_NEONFLOOR)
				{
					//�v���C���[�Əd�Ȃ�����
					if (m_pos.z - m_Scale.z * NEONFLOOR_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
						&&  m_pos.z + m_Scale.z * NEONFLOOR_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
					{
						///////////////////////////////////
						//���̔���
						///////////////////////////////////
						if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
							&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posPlayer.y - scalePlayer.y)
						{
							if (m_pos.x - m_Scale.x * NEONFLOOR_COL > posOldPlayer.x + scalePlayer.x * PLAYER_COL_X
								&&  m_pos.x - m_Scale.x * NEONFLOOR_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X)
							{//�Ђ���B
								posPlayer.x = m_pos.x - m_Scale.x * NEONFLOOR_COL;  //�u���b�N�̍����甲���Ȃ�
								movePlayer.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}

							if (m_pos.x + m_Scale.x * NEONFLOOR_COL < posOldPlayer.x - scalePlayer.x * PLAYER_COL_X
								&&  m_pos.x + m_Scale.x * NEONFLOOR_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X)
							{//�~�M�[�B
								posPlayer.x = m_pos.x + m_Scale.x * NEONFLOOR_COL;  //�u���b�N�̉E���甲���Ȃ�
								movePlayer.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}
						}

						///////////////////////////////////
						//�c�̔���
						///////////////////////////////////
						if ((m_pos.x - m_Scale.x * NEONFLOOR_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&& m_pos.x + m_Scale.x * NEONFLOOR_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X))
						{
							if (m_pos.y + m_Scale.y * NEONFLOOR_COL < posOldPlayer.y - scalePlayer.y + 2.0f
								&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posPlayer.y - scalePlayer.y + 2.0f)
							{//�ゾ�B
								posPlayer.y = m_pos.y + m_Scale.y * NEONFLOOR_COL + 0.4f;  //�u���b�N�̏�ɗ�������
								movePlayer.y = 0.0f;  //�ړ��ʂ�0�ɂ���
								pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_GROUND);  //�v���C���[��n���Ԃɂ���
								pPlayer->SetStepPossible(false);  //�X�e�b�v�\��Ԃ�L���ɂ���
							}

							if (m_pos.y - m_Scale.y > posOldPlayer.y + scalePlayer.y * PLAYER_COL_X
								&&  m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_X)
							{//�����B
								posPlayer.y = m_pos.y - m_Scale.y - 70.0f;  //�u���b�N�����Ȃ��悤�ɂ���
								movePlayer.y = 0.0f;  //�ړ��ʂ�0�ɂ���
							}
						}
					}

					///////////////////////////////////
					//���s���̔���
					///////////////////////////////////
					if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posPlayer.y - scalePlayer.y)
					{
						if (m_pos.x - m_Scale.x * NEONFLOOR_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  m_pos.x + m_Scale.x * NEONFLOOR_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X)
						{
							if (m_pos.z - m_Scale.z * NEONFLOOR_COL > posOldPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
								&&  m_pos.z - m_Scale.z * NEONFLOOR_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f)
							{//��O
								posPlayer.z = m_pos.z - m_Scale.z * NEONFLOOR_COL - 170.0f;  //�u���b�N�̎�O���甲���Ȃ�
								movePlayer.z = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}

							if (m_pos.z + m_Scale.z * NEONFLOOR_COL < posOldPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f
								&&  m_pos.z + m_Scale.z * NEONFLOOR_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
							{//��
								posPlayer.z = m_pos.z + m_Scale.z * NEONFLOOR_COL + 170.0f;  //�u���b�N�̉����甲���Ȃ�
								movePlayer.z = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}
						}
					}
				}

				//�l�I���u���b�N
				if (typetex == BLOCK_NEON)
				{
					if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  m_pos.y + m_Scale.y * NEON_COL > posPlayer.y - scalePlayer.y)
					{
						///////////////////////////////////
						//���̔���
						///////////////////////////////////
						if (m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
							&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
						{
							if (m_pos.x - m_Scale.x * NEON_COL > posOldPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f
								&&  m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f)
							{//��
								posPlayer.x = m_pos.x - m_Scale.x * NEON_COL - 180.0f;  //�u���b�N�̍����甲���Ȃ�
								movePlayer.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}

							if (m_pos.x + m_Scale.x * NEON_COL < posOldPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f
								&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f)
							{//�E
								posPlayer.x = m_pos.x + m_Scale.x * NEON_COL + 180.0f;  //�u���b�N�̉E���甲���Ȃ�
								movePlayer.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}
						}

						///////////////////////////////////
						//���s���̔���
						///////////////////////////////////
						if (m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X)
						{
							if (m_pos.z - m_Scale.z * NEON_COL > posOldPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
								&&  m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f)
							{//��O
								posPlayer.z = m_pos.z - m_Scale.z * NEON_COL - 170.0f;  //�u���b�N�̎�O���甲���Ȃ�
								movePlayer.z = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}

							if (m_pos.z + m_Scale.z * NEON_COL < posOldPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f
								&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
							{//��
								posPlayer.z = m_pos.z + m_Scale.z * NEON_COL + 170.0f;  //�u���b�N�̉����甲���Ȃ�
								movePlayer.z = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}
						}
					}
				}

				//�l�I����
				if (typetex == BLOCK_NEONWALL)
				{
					if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  m_pos.y + m_Scale.y * NEON_COL > posPlayer.y - scalePlayer.y)
					{
						///////////////////////////////////
						//���̔���
						///////////////////////////////////
						if (m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
							&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
						{
							if (m_pos.x - m_Scale.x * NEON_COL > posOldPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f
								&&  m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f)
							{//��
								posPlayer.x = m_pos.x - m_Scale.x * NEON_COL - 179.0f;  //�u���b�N�̍����甲���Ȃ�

								//�O�ɐi��
								movePlayer.x += sinf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;
								movePlayer.z += cosf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;

								if (rotPlayer.y > 1.57f || rotPlayer.y < -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_R);  //�v���C���[���E����̕Ǒ����Ԃɂ���
								}

								else if (rotPlayer.y < 1.57f || rotPlayer.y > -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_L);  //�v���C���[��������̕Ǒ����Ԃɂ���
								}
							}

							if (m_pos.x + m_Scale.x * NEON_COL < posOldPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f
								&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f)
							{//�E
								posPlayer.x = m_pos.x + m_Scale.x * NEON_COL + 179.0f;  //�u���b�N�̉E���甲���Ȃ�

								//�O�ɐi��
								movePlayer.x += sinf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;
								movePlayer.z += cosf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;

								if (rotPlayer.y > 1.57f || rotPlayer.y < -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_R);  //�v���C���[���E����̕Ǒ����Ԃɂ���
								}

								else if (rotPlayer.y < 1.57f || rotPlayer.y > -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_L);  //�v���C���[��������̕Ǒ����Ԃɂ���
								}
							}
						}

						///////////////////////////////////
						//���s���̔���
						///////////////////////////////////
						if (m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f
							&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f)
						{
							if (m_pos.z - m_Scale.z * NEON_COL > posOldPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
								&&  m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f)
							{//��O
								posPlayer.z = m_pos.z - m_Scale.z * NEON_COL - 170.0f;  //�u���b�N�̎�O���甲���Ȃ�
								movePlayer.z = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}

							if (m_pos.z + m_Scale.z * NEON_COL < posOldPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f
								&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
							{//��
								posPlayer.z = m_pos.z + m_Scale.z * NEON_COL + 170.0f;  //�u���b�N�̉����甲���Ȃ�
								movePlayer.z = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}
						}
					}
				}

				pPlayer->SetPosition(posPlayer);  //�v���C���[�̈ʒu�̐ݒ�
				pPlayer->SetMove(movePlayer);  //�v���C���[�̈ړ��ʂ̐ݒ�
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//�G�Ƃ̓����蔻��
//-------------------------------------------------------
bool CBlock3D::CollisionEnemy(CEnemy3D *pEnemy)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //�u���b�N�̈ʒu�̎擾
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 m_Scale = m_apObject[nCnt]->GetScale();  //�u���b�N�̃T�C�Y�̎擾
			CObject::TYPE type;  //���
			int typetex = m_apObject[nCnt]->GetTypeTex();  //�G�̎�ގ擾

			//��ނ��擾
			type = pEnemy->GetType();

			//��ނ��G�̏ꍇ
			if (type == CObject::TYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //�G�̈ʒu�̎擾
				D3DXVECTOR3 posOldEnemy = pEnemy->GetPositionOld();  //�G�̉ߋ��̈ʒu�̎擾
				D3DXVECTOR3 moveEnemy = pEnemy->GetMove();  //�G�̈ړ��ʂ̎擾
				D3DXVECTOR3 scaleEnemy = pEnemy->GetScale();  //�G�̃T�C�Y�̎擾

				if (typetex == BLOCK_NEONFLOOR)
				{
					///////////////////////////////////
					//���̔���
					///////////////////////////////////
					//�v���C���[�Əd�Ȃ�����
					if (m_pos.z - m_Scale.z * NEONFLOOR_COL <= posEnemy.z + scaleEnemy.z * USUALLY_COR_Z
						&&  m_pos.z + m_Scale.z * NEONFLOOR_COL >= posEnemy.z - scaleEnemy.z * USUALLY_COR_Z)
					{
						if (m_pos.y - m_Scale.y < posEnemy.y + scaleEnemy.y * PLAYER_COL_Y
							&&  m_pos.y + m_Scale.y * NEONFLOOR_COL + 10.0f > posEnemy.y - scaleEnemy.y)
						{
							if (m_pos.x - m_Scale.x * NEONFLOOR_COL > posOldEnemy.x + scaleEnemy.x * USUALLY_COR_X
								&&  m_pos.x - m_Scale.x * NEONFLOOR_COL < posEnemy.x + scaleEnemy.x * USUALLY_COR_X)
							{//�Ђ���B
								posEnemy.x = m_pos.x - m_Scale.x * NEONFLOOR_COL;  //�u���b�N�̍����甲���Ȃ�
								moveEnemy.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}

							if (m_pos.x + m_Scale.x * NEONFLOOR_COL < posOldEnemy.x - scaleEnemy.x * USUALLY_COR_X
								&&  m_pos.x + m_Scale.x * NEONFLOOR_COL > posEnemy.x - scaleEnemy.x * USUALLY_COR_X)
							{//�~�M�[�B
								posEnemy.x = m_pos.x + m_Scale.x * NEONFLOOR_COL;  //�u���b�N�̉E���甲���Ȃ�
								moveEnemy.x = 0.0f;  //�v���C���[�̈ړ��ʂ�0�ɂ���
							}
						}
					}

					///////////////////////////////////
					//�c�̔���
					///////////////////////////////////
					if (m_pos.z - m_Scale.z * NEONFLOOR_COL <= posEnemy.z + scaleEnemy.z * USUALLY_COR_Z
						&&  m_pos.z + m_Scale.z * NEONFLOOR_COL >= posEnemy.z - scaleEnemy.z * USUALLY_COR_Z)
					{
						if ((m_pos.x - m_Scale.x * NEONFLOOR_COL < posEnemy.x + scaleEnemy.x * USUALLY_COR_X
							&& m_pos.x + m_Scale.x * NEONFLOOR_COL > posEnemy.x - scaleEnemy.x * USUALLY_COR_X))
						{
							if (m_pos.y + m_Scale.y * NEONFLOOR_COL < posOldEnemy.y - scaleEnemy.y + 2.0f
								&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posEnemy.y - scaleEnemy.y + 2.0f)
							{//�ゾ�B
								posEnemy.y = m_pos.y + m_Scale.y * NEONFLOOR_COL + 0.4f;  //�u���b�N�̏�ɗ�������
								moveEnemy.y = 0.0f;  //�ړ��ʂ�0�ɂ���
							}

							if (m_pos.y - m_Scale.y > posOldEnemy.y + scaleEnemy.y * USUALLY_COR_Y
								&&  m_pos.y - m_Scale.y < posEnemy.y + scaleEnemy.y * USUALLY_COR_Y)
							{//�����B
								posEnemy.y = m_pos.y - m_Scale.y - 70.0f;  //�u���b�N�����Ȃ��悤�ɂ���
								moveEnemy.y = 0.0f;  //�ړ��ʂ�0�ɂ���
							}
						}
					}
				}

				pEnemy->SetPosition(posEnemy);  //�G�̈ʒu�̐ݒ�
				pEnemy->SetMove(moveEnemy);  //�G�̈ړ��ʂ̐ݒ�
			}
		}
	}

	return FALSE;
}