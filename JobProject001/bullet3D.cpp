//=============================================================================
//
// �e�̏���(3D) [bullet3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "bullet3D.h"
#include "manager.h"
#include "explosion.h"
#include "block3D.h"
#include "effectbeam.h"
#include "modelset.h"

//�}�N����`
#define LIFE_ENEMY (150)  //�G�̒e����
#define LIFE_PLAYER (150)  //�v���C���[�̒e����
#define LIFE_PLAYERBOSS (50)  //�v���C���[�{�X��̒e����
#define PLAYER_SPEED (5.0f)  //�v���C���[�̒e�̑��x
#define ENEMY_SPEED (5.0f)  //�G�̒e�̑��x

//�ÓI�����o�ϐ�
CBullet3D *CBullet3D::m_apObject[MAX_BULLET] = {};
bool CBullet3D::m_Beam = false;
//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CBullet3D::CBullet3D()
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
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
CBullet3D::~CBullet3D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CBullet3D::Init(void)
{
	//�f�o�C�X�̎擾
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //���f���̃|�C���^

	//���f����錾
	m_nIdxModel[BULLETTYPE_PLAYER] = pModel->Regist("data\\MODEL\\bullet001.x");  //�v���C���[�̒e
	m_nIdxModel[BULLETTYPE_ENEMY] = pModel->Regist("data\\MODEL\\bullet001.x");  //�G�̒e
	m_nIdxModel[BULLETTYPE_TUTORIAL] = pModel->Regist("data\\MODEL\\bullet001.x");  //�G�̃`���[�g���A���e

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//�l�̃N���A
	m_nLife = 0;
	m_nCntHit = 0;
	m_Beam = false;

	//��ނ̐ݒ�
	CObject::SetType(TYPE_BULLET);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CBullet3D::Uninit(void)
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
void CBullet3D::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 move = GetMove();  //�ړ��ʂ̎擾

	int nID = m_nID;

	//�ʒu�̍X�V
	pos += move;

	//�ʒu�̐ݒ�
	SetPosition(pos);

	m_nLife++;
	m_nCntHit++;

	if (m_Beam == false)
	{
		////�r�[������
		//CModelSet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BEAM);

		m_Beam = true;
	}



	//�^�C�v���v���C���[�̎�
	if (m_type == BULLETTYPE_PLAYER)
	{
		//�e��������܂ł̃J�E���g
		if (m_nLife >= LIFE_PLAYER)
		{
			//�폜����
			Uninit();

			m_nLife = 0;  //0�ɖ߂�

			return;
		}

		//�G�Ƃ̓����蔻��
		if (CEnemy3D::CollisionBullet(this))
		{
			return;
		}

		//���f���Ƃ̓����蔻��
		if (CModelSet::CollisionBullet(this)) {
			return;
		}
	}

	//�^�C�v���G�̎�
	if (m_type == BULLETTYPE_ENEMY || m_type == BULLETTYPE_TUTORIAL)
	{
		if (m_nCntHit >= 10)
		{
			//�v���C���[�Ƃ̓����蔻��
			if (CPlayer3D::CollisionBullet(this) == true)
			{
				//�����̏I������
				Uninit();

				m_nCntHit = 0;  //�J�E���g��0�Ƀ��Z�b�g����
			}
		}

		//�e��������܂ł̃J�E���g
		if (m_nLife >= LIFE_ENEMY)
		{
			//�폜����
			Uninit();

			m_nLife = 0;  //0�ɖ߂�
		}
	}
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CBullet3D::Draw(void)
{
	//�I�u�W�F�N�g�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int type)
{
	CBullet3D *pBullet = NULL;;

	//�e�̐���
	pBullet = new CBullet3D;

	if (pBullet != NULL)
	{
		//����������
		pBullet->Init();

		//�ʒu�̐ݒ�
		pBullet->SetPosition(pos);

		//�ړ��ʂ̐ݒ�
		pBullet->SetMove(move);

		//�����̐ݒ�
		pBullet->SetRotation(rot);

		//�g�嗦�̐ݒ�
		pBullet->SetScale(scale);

		//��ނ̐ݒ�
		pBullet->SetTypeBullet(type);

		//�r�[�����Ȃ���Ԃɂ���
		m_Beam = false;

		//�e�̈ړ��ʐݒ�
		pBullet->SetMove(move * ENEMY_SPEED);

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == type)
			{
				//���f���̊��蓖��
				pBullet->BindModel(pBullet->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{
		//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBullet;
}
//-------------------------------------------------------
//�u���b�N�Ƃ̓����蔻��
//-------------------------------------------------------
bool CBullet3D::CollisionBlock(CBlock3D *pBlock)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//NULL����Ȃ��Ƃ�
		if (m_apObject[nCnt] != NULL)
		{
			CObject::TYPE type = pBlock->GetType();  //��ނ��擾

			//��ނ��e�̏ꍇ
			if (type == CObject::TYPE_BLOCK)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 m_scale = m_apObject[nCnt]->GetScale();  //�T�C�Y�̎擾
				D3DXVECTOR3 posBlock = pBlock->GetPosition();  //�u���b�N�̈ʒu�̎擾
				D3DXVECTOR3 scaleBlock = pBlock->GetScale();  //�u���b�N�̃T�C�Y�̎擾
				int typetex = pBlock->GetTypeTex();  //��ގ擾

				if (typetex == CBlock3D::BLOCK_NEONFLOOR)
				{
					//�e�Əd�Ȃ�����
					if (pos.x + m_scale.x > posBlock.x - scaleBlock.x * NEONFLOOR_COL
						&&  pos.x - m_scale.x < posBlock.x + scaleBlock.x * NEONFLOOR_COL
						&&  pos.y + m_scale.y > posBlock.y - scaleBlock.y
						&&  pos.y - m_scale.y < posBlock.y + scaleBlock.y * NEONFLOOR_COL
						&&  pos.z + m_scale.z > posBlock.z - scaleBlock.z
						&&  pos.z - m_scale.z < posBlock.z + scaleBlock.z) 
					{
						//�e�̏I������
						m_apObject[nCnt]->Uninit();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//�e�̎�ރ^�C�v�̐ݒ�
//-------------------------------------------------------
void CBullet3D::SetTypeBullet(int Type)
{
	m_type = Type;
}