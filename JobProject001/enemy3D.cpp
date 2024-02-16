//=============================================================================
//
// �G���� [enemy3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "enemy3D.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "bullet3D.h"
#include "block3D.h"
#include "modelset.h"
#include "effect.h"

//�}�N����`
#define BULLETSPEED (10.0f)   //�G�̒e�X�s�[�h
#define BESTPOS (700.0f)  //�G�̓����Ă���ŋߋ���
#define BESTPOSBOSS (1300.0f)  //�{�X�̓����Ă���ŋߋ���
#define USUALLY_RANGE (1000.0f)  //�ʏ�G�̌��m�͈�
#define BOSS_RANGE (4000.0f)  //�{�X�̌��m�͈�

//�ÓI�����o�ϐ�
CEnemy3D *CEnemy3D::m_apObject[MAX_ENEMY] = {};
bool CEnemy3D::m_CreateCore = false;
bool CEnemy3D::m_LifeState = false;
//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CEnemy3D::CEnemy3D()
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
CEnemy3D::~CEnemy3D()
{

}
//-------------------------------------------------------
//�G�̏���������
//-------------------------------------------------------
HRESULT CEnemy3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //���f���̃|�C���^

	//���f����錾
	m_nIdxModel[TYPE_USUALLY] = pModel->Regist("data\\MODEL\\usually_enemy.x");  //�ʏ�G
	m_nIdxModel[TYPE_BOSS] = pModel->Regist("data\\MODEL\\Boss_enemy.x");     //�{�X
	m_nIdxModel[TYPE_TUTORIAL_ENE] = pModel->Regist("data\\MODEL\\usually_enemy.x");  //�`���[�g���A���G

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//�l��������
	m_Life = 100;
	m_nCntHit = 0;
	m_nCounterMove = 0;
	m_nCntEnemyBullet = 0;
	m_nCntDownSpeed = 0;
	m_nCntAttack = 0;
	m_BossDownState = false;
	m_CreateCore = false;
	m_LifeState = false;
	m_LifeGaugeSize = false;
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_BossBattel = BOSS_BATTEL_0;
	CObject::SetType(TYPE_ENEMY);
	CObjectX::SetState(CObject::STATE_NORMAL, 0);

	return (S_OK);
}
//-------------------------------------------------------
//�G�̏I������
//-------------------------------------------------------
void CEnemy3D::Uninit(void)
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
//�G�̍X�V����
//-------------------------------------------------------
void CEnemy3D::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 move = GetMove();   //�ړ��ʂ̎擾
	D3DXVECTOR3 rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 posPlayer;
	int typetex = GetTypeTex();  //��ގ擾

	SetPositionOld(pos);  //�ߋ��̈ʒu�ݒ�

	//��ԊǗ��ݒ�
	CObject::UpdateState();

	//��ԊǗ�
	UpdateEnemyState();

	//�ړ��ݒ�
	//MoveEnemy();

	if (typetex == TYPE_USUALLY)
	{
		//�d�͂�������
		move.y -= 4.0f;
	}

	m_nCntHit++;

	//�ʒu�̍X�V
	pos += move;

	//�ړ��ʂ��X�V
	move.x += (0.0f - move.x) * ENEMYSPEEDUP;
	move.y += (0.0f - move.y) * ENEMYSPEEDUP;

	//�p�x�̕␳
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	SetPosition(pos);  //�ʒu�̐ݒ�
	SetMove(move);  //�ړ��ʂ̐ݒ�
	SetRotation(rot);  //�����̐ݒ�

	CBlock3D::CollisionEnemy(this);  //�u���b�N�Ƃ̓����蔻��
	CPlayer3D::CollisionEnemy(this);  //�v���C���[�ƓG�Ƃ̓����蔻��
	CModelSet::CoreMove(this);  //�{�X�R�A�ړ�����
}
//-------------------------------------------------------
//�G�̕`�揈��
//-------------------------------------------------------
void CEnemy3D::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CEnemy3D *CEnemy3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life)
{
	CEnemy3D *pEnemy3D;

	//�G�̐���
	pEnemy3D = new CEnemy3D;

	if (pEnemy3D != NULL)
	{
		//����������
		pEnemy3D->Init();

		//�ʒu�̐ݒ�
		pEnemy3D->SetPosition(pos);

		//�ʒu�̐ݒ�
		pEnemy3D->SetPositionOld(pos);

		//�ړ��ʂ̐ݒ�
		pEnemy3D->SetMove(move);

		//�����̐ݒ�
		pEnemy3D->SetRotation(rot);

		//�g�嗦�̐ݒ�
		pEnemy3D->SetScale(scale);

		//�T�C�Y
		pEnemy3D->SetSize(size);

		//�e�N�X�`���^�C�v
		pEnemy3D->SetTypeTex(SetTypeTex);

		//���C�t�̐ݒ�
		pEnemy3D->SetLife(Life);

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pEnemy3D->BindModel(pEnemy3D->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEnemy3D;
}
//-------------------------------------------------------
//�v���C���[�̐퓬
//-------------------------------------------------------
void CEnemy3D::PlayerAttack(CPlayer3D *pPlayer)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();;

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	CObject::TYPE type;  //���

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//m_apObject[nCnt]��NULL����Ȃ�������
		if (m_apObject[nCnt] != NULL)
		{
			//��ނ��擾
			type = pPlayer->GetType();

			//��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
				D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //�g�嗦�̎擾
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //�v���C���[�̌����̎擾
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //�v���C���[�̊g�嗦�̎擾
				D3DXVECTOR3 PLACOL = posPlayer;  //�v���C���[�Ƃ̌����œ����蔻��
				D3DXVECTOR3 BOSSCOL = pos;  //�{�X�Ƃ̌����œ����蔻��
				int typetex = m_apObject[nCnt]->GetTypeTex();  //�G�̎�ގ擾
				PLACOL.x = posPlayer.x + sinf(rotPlayer.y) * PLAYER_COL_X;
				PLACOL.z = posPlayer.z + cosf(rotPlayer.y) * PLAYER_COL_Z;
				BOSSCOL.x = pos.x + sinf(rot.y) * BOSS_COR_X;
				BOSSCOL.z = pos.z + cosf(rot.y) * BOSS_COR_Z;

				//�G�͈̔�
				float fRangth = sqrtf((PLACOL.x - pos.x) * (PLACOL.x - pos.x) + (PLACOL.z - pos.z) * (PLACOL.z - pos.z));
				float fRangthBoss = sqrtf((BOSSCOL.x - posPlayer.x) * (BOSSCOL.x - posPlayer.x) + (BOSSCOL.z - posPlayer.z) * (BOSSCOL.z - posPlayer.z));

				//�v���C���[���画�肳��鋗��
				float fLength = 500.0f;
				float fLengthBoss = 2000.0f;

				float fRot = rotPlayer.y + D3DX_PI - rot.y;

				//�p�x�̕␳
				if (fRot > D3DX_PI)
				{
					fRot += -D3DX_PI * 2;
				}

				if (fRot < -D3DX_PI)
				{
					fRot += D3DX_PI * 2;
				}

				m_apObject[nCnt]->m_nCntAttack++;

				//�U���L�[���������Ƃ��U���J�E���^�[��50�ȏゾ������
				if (pInputKeyboard->GetTrigger(DIK_V) == true && m_apObject[nCnt]->m_nCntAttack > 50
					|| pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0) && m_apObject[nCnt]->m_nCntAttack > 50)
				{
					m_apObject[nCnt]->m_nCntAttack = 0;  //0�ɖ߂�

					if (typetex == TYPE_USUALLY)
					{
						//�ʏ�G�ɓ�������
						if (fRangth < fLength
							&& fRot < 0.5f
							&& fRot > -0.5f)
						{
							//�G�̃q�b�g����
							HitEnemy(200, nCnt);
						}
					}

					if (typetex == TYPE_BOSS)
					{
						if (m_apObject[nCnt]->m_BossDownState == true)
						{
							//�{�X�ɓ�������
							if (fRangthBoss < fLengthBoss
								&& fRot < 0.5f
								&& fRot > -0.5f)
							{
								//�G�̃q�b�g����
								HitEnemy(200, nCnt);
							}
						}
					}

					if (typetex == TYPE_TUTORIAL_ENE)
					{
						//�`���[�g���A���G�ɓ�������
						if (fRangth < fLength
							&& fRot < 0.5f
							&& fRot > -0.5f)
						{
							//�G�̃q�b�g����
							HitEnemy(200, nCnt);
						}
					}
				}

				if (typetex == TYPE_BOSS)
				{
					//-------------------------------------------------------
					//�G�̃f�o�b�N�\��
					//-------------------------------------------------------
					//CManager::GetInstance()->GetDebugProc()->Print("�{�X�Ƃ̋��� [%f] : �{�X�̔��a[ %f ]\n", fLengthBoss, fRangthBoss);
				}

				//-------------------------------------------------------
				//�G�̃f�o�b�N�\��
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("�G�̌��� [%f, %f, %f]\n", rot.x, rot.y, rot.z);
				//CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�ƓG�̌������� [%f]\n", fRot);
				//CManager::GetInstance()->GetDebugProc()->Print("�U���i�K [%d]\n", pPlayer->GetSwordAttack());
				//CManager::GetInstance()->GetDebugProc()->Print("�U���J�E���g [%d]\n", m_apObject[nCnt]->m_nCntAttack);
			}
		}
	}
}
//-------------------------------------------------------
//�e��������
//-------------------------------------------------------
void CEnemy3D::ShootBullet(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
			D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //�X�P�[���̎擾
			int typetex = m_apObject[nCnt]->GetTypeTex();  //��ގ擾
			CObject::TYPE type = pPlayer->GetType();  //�I�u�W�F�N�g�̎�ނ��擾

			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //�v���C���[�̉ߋ��̈ʒu�̎擾
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //�v���C���[�̃X�P�[���擾
				int PlaLife = pPlayer->GetLife();  //�v���C���[�̃��C�t�擾

				if (PlaLife <= 0)
				{
					if (typetex == TYPE_BOSS)
					{
						m_apObject[nCnt]->Uninit();
					}
				}

				//�v���C���[�̃��X�^�[�g��Ԃ������̎�
				if (pPlayer->GetRestart() == false)
				{
					//=============================================
					//�ʏ�G
					//=============================================
					if (typetex == TYPE_USUALLY)
					{
						float fAngleY = atan2f(posOldPlayer.z - pos.z, pos.x - posOldPlayer.x);

						D3DXVECTOR3 fAngle = D3DXVECTOR3(posOldPlayer.x - pos.x, (posOldPlayer.y + 50.0f) - pos.y, posOldPlayer.z - pos.z);
						D3DXVec3Normalize(&fAngle, &fAngle);

						rot.y = fAngleY + 1.57f;

						//�v���C���[���͈͓��ɓ�������
						if (pos.x - scale.x * USUALLY_COR_X - USUALLY_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  pos.x + scale.x * USUALLY_COR_X + USUALLY_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
							&&  pos.y - scale.y * USUALLY_COR_Y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
							&&  pos.z - scale.z * USUALLY_COR_Z - USUALLY_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
							&&  pos.z + scale.z * USUALLY_COR_Z + USUALLY_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
						{
							if (m_apObject[nCnt]->m_nCntEnemyBullet == 60)
							{
								D3DXMATERIAL redMat;
								ZeroMemory(&redMat, sizeof(redMat));
								redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
								redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

								m_apObject[nCnt]->SetMat(1, redMat);
							}

							if (m_apObject[nCnt]->m_nCntEnemyBullet == 100)
							{
								m_apObject[nCnt]->ResetMat();

								//�e����
								CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

								//�r�[������
								CModelSet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, rot.y, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BEAM_ENE);

								m_apObject[nCnt]->m_nCntEnemyBullet = 0;  //���Z�b�g
							}

							m_apObject[nCnt]->m_nCntEnemyBullet++;  //�G�̒e�J�E���^�[
						}

						//-------------------------------------------------------
						//�G�̃f�o�b�N�\��
						//-------------------------------------------------------
						CManager::GetInstance()->GetDebugProc()->Print("�G�̈ʒu [%f, %f, %f]\n", pos.x, pos.y, pos.z);
					}

					//=============================================
					//�{�X
					//=============================================
					if (typetex == TYPE_BOSS)
					{
						float fAngleY = atan2f(posOldPlayer.z - pos.z, pos.x - posOldPlayer.x);

						D3DXVECTOR3 fAngle = D3DXVECTOR3(posOldPlayer.x - pos.x, (posOldPlayer.y + 50.0f) - pos.y, posOldPlayer.z - pos.z);
						D3DXVec3Normalize(&fAngle, &fAngle);

						rot.y = fAngleY + 1.57f;

						//�v���C���[���{�X�̌�����͈͓��ɓ�������
						if (pos.x - scale.x * USUALLY_COR_X - BOSS_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  pos.x + scale.x * USUALLY_COR_X + BOSS_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
							&&  pos.z - scale.z * USUALLY_COR_Z - BOSS_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
							&&  pos.z + scale.z * USUALLY_COR_Z + BOSS_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
						{
							if (m_apObject[nCnt]->m_LifeState == false)
							{
								//---------------------------------------------------------------
								//���C�t�Q�[�W����
								//---------------------------------------------------------------
								CLife::Create(D3DXVECTOR3(100.0f, 80.0f, 0.0f), D3DXVECTOR3(1000.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_BOSSLIFEGAUGE);

								m_apObject[nCnt]->m_LifeState = true;
							}

							//�v���C���[���{�X�̍U���͈͓��ɓ�������
							if (pos.x - scale.x * USUALLY_COR_X - BOSS_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
								&&  pos.x + scale.x * USUALLY_COR_X + BOSS_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
								&&  pos.z - scale.z * USUALLY_COR_Z - BOSS_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
								&&  pos.z + scale.z * USUALLY_COR_Z + BOSS_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
							{
								m_apObject[nCnt]->m_BossBattel = BOSS_BATTEL_1;  //�{�X�̐퓬�Ԑ���Ԃ���i�K�ɂ���

								//�{�X���_�E����Ԃ���Ȃ��Ƃ�
								if (m_apObject[nCnt]->m_BossDownState == false)
								{
									if (m_apObject[nCnt]->m_nCntEnemyBullet == 60)
									{
										D3DXMATERIAL redMat;
										ZeroMemory(&redMat, sizeof(redMat));
										redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
										redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

										m_apObject[nCnt]->SetMat(1, redMat);
									}

									if (m_apObject[nCnt]->m_nCntEnemyBullet == 100)
									{
										m_apObject[nCnt]->ResetMat();

										//�e����
										CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

										//�r�[������
										CModelSet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, rot.y, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BEAM_ENE);

										m_apObject[nCnt]->m_nCntEnemyBullet = 0;  //���Z�b�g
									}

									m_apObject[nCnt]->m_nCntEnemyBullet++;  //�G�̒e�J�E���^�[
								}
							}
						}
					}

					//=============================================
					//�`���[�g���A���G
					//=============================================
					if (typetex == TYPE_TUTORIAL_ENE)
					{
						//�v���C���[���͈͓��ɓ�������
						if (pos.x - scale.x * USUALLY_COR_X - USUALLY_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  pos.x + scale.x * USUALLY_COR_X + USUALLY_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
							&&  pos.y - scale.y * USUALLY_COR_Y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
							&&  pos.z - scale.z * USUALLY_COR_Z - USUALLY_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
							&&  pos.z + scale.z * USUALLY_COR_Z + USUALLY_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
						{
							float fAngleY = atan2f(posOldPlayer.z - pos.z, pos.x - posOldPlayer.x);

							D3DXVECTOR3 fAngle = D3DXVECTOR3(posOldPlayer.x - pos.x, (posOldPlayer.y + 50.0f) - pos.y, posOldPlayer.z - pos.z);
							D3DXVec3Normalize(&fAngle, &fAngle);

							rot.y = fAngleY + 1.57f;

							if (m_apObject[nCnt]->m_TutorialEne == TUTORIAL_ENESTATE_ATTACKMODE)
							{
								if (m_apObject[nCnt]->m_nCntEnemyBullet == 60)
								{
									D3DXMATERIAL redMat;
									ZeroMemory(&redMat, sizeof(redMat));
									redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
									redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

									m_apObject[nCnt]->SetMat(0, redMat);
								}

								if (m_apObject[nCnt]->m_nCntEnemyBullet == 100)
								{
									m_apObject[nCnt]->ResetMat();

									//�e����
									CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

									m_apObject[nCnt]->m_nCntEnemyBullet = 0;  //���Z�b�g
								}

								m_apObject[nCnt]->m_nCntEnemyBullet++;  //�G�̒e�J�E���^�[
							}
						}
					}
				}
			}

			//�ݒ�
			m_apObject[nCnt]->SetPosition(pos);  //�ʒu�̐ݒ�
			m_apObject[nCnt]->SetRotation(rot);  //�����̐ݒ�
		}
	}
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CEnemy3D::UpdateEnemyState(void)
{
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]��NULL����Ȃ�������
			if (m_apObject[nCnt] != NULL)
			{
				m_apObject[nCnt]->m_LifeGaugeSize = false;  //���C�t�Q�[�W�T�C�Y���ύX�o���Ȃ���Ԃɂ���
			}
		}
		break;

	case ENEMYSTATE_DAMAGE:

		m_nCounterState--;

		if (m_nCounterState <= 0)
		{
			m_state = ENEMYSTATE_NORMAL;

			for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
			{
				//m_apObject[nCnt]��NULL����Ȃ�������
				if (m_apObject[nCnt] != NULL)
				{
					m_apObject[nCnt]->ResetMat();
				}
			}

			break;
		}
	}
}
//-------------------------------------------------------
//�G�̐퓬�Ԑ����Ƃ̏���
//-------------------------------------------------------
void CEnemy3D::EnemyBattelState(CModelSet *pModelSet)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 move = m_apObject[nCnt]->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
			D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //�X�P�[���̎擾
			BOSS_BATTEL BossBattel = m_apObject[nCnt]->GetBossBattel();  //�{�X�̐퓬�Ԑ���Ԃ̎擾
			int typetex = m_apObject[nCnt]->GetTypeTex();  //�e�N�X�`���^�C�v�擾
			int BossCoreState = pModelSet->GetBossCoreState();  //�{�X�R�A�̏�Ԃ��擾

			//�ʏ�G�̏���
			if (typetex == TYPE_USUALLY)
			{

			}

			//�{�X�̏���
			if (typetex == TYPE_BOSS)
			{
				if (BossBattel == BOSS_BATTEL_1)
				{
					//�R�A���Ȃ��Ƃ�
					if (BossCoreState == pModelSet->BOSSCORESTATE_NONE)
					{
						if (m_CreateCore == false)
						{
							//��ڂ̃R�A���o�� (�ԍ�5)
							CModelSet::Create(D3DXVECTOR3(pos.x - 200.0f, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//��ڂ̃R�A���o�� (�ԍ�6)
							CModelSet::Create(D3DXVECTOR3(pos.x + 200.0f, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//�O�ڂ̃R�A���o�� (�ԍ�7)
							CModelSet::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//�l�ڂ̃R�A���o�� (�ԍ�8)
							CModelSet::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//�܌ڂ̃R�A���o�� (�ԍ�9)
							CModelSet::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							m_CreateCore = true;
							pModelSet->SetBossCoreState(pModelSet->BOSSCORESTATE_LIVE);
						}
					}

					//�{�X�̗̑͂�1000�ȉ��ɂȂ�����
					if (m_apObject[nCnt]->m_Life <= 0)
					{
						m_apObject[nCnt]->SetBossBattel(BOSS_BATTEL_2);  //��i�K�ڂɂ���
						m_apObject[nCnt]->m_BossDownState = false;  //�_�E����Ԃ��畜�A����
						m_CreateCore = false;  //�R�A���Ȃ���Ԃɂ���

						rot.x += 0.005f;  //�{�X���_�E������߂鑬�x

						if (rot.x > -0.09f)
						{
							rot.x = -0.09f;  //���ɖ߂�
							pModelSet->SetBreakCore(false);  //�R�A�����Ă��Ȃ���Ԃɂ���
						}
					}
				}

				//��i�K�ڂ̂Ƃ�
				if (BossBattel == BOSS_BATTEL_2)
				{
					//�R�A���Ȃ��Ƃ�
					if (BossCoreState == pModelSet->BOSSCORESTATE_NONE)
					{
						if (m_CreateCore == false)
						{
							m_CreateCore = true;

							pModelSet->SetBossCoreState(pModelSet->BOSSCORESTATE_LIVE);  //�R�A�������Ԃɂ���
						}
					}
				}

				//�R�A����ꂽ�Ƃ�
				if (pModelSet->GetBossCoreState() == pModelSet->BOSSCORESTATE_BREAK && m_apObject[nCnt]->m_BossDownState == false)
				{
					m_apObject[nCnt]->m_nCntDownSpeed++;

					if (m_apObject[nCnt]->m_nCntDownSpeed > 60)
					{
						m_apObject[nCnt]->m_BossDownState = true;
						m_apObject[nCnt]->m_nCntDownSpeed = 0;
						pModelSet->SetBossCoreState(pModelSet->BOSSCORESTATE_NONE);  //�R�A���Ȃ���Ԃɂ���
						m_apObject[nCnt]->ResetMat();  //�F��߂�
					}
				}

				//�{�X���_�E����Ԃ̂Ƃ�
				if (m_apObject[nCnt]->m_BossDownState == true)
				{
					rot.x -= 0.004f;  //�{�X���_�E�����鑬�x
					rot.y = 0.0f;

					if (rot.x < -1.2f)
					{
						rot.x = -1.2f;
					}
				}

				if (m_apObject[nCnt]->m_nCntDownSpeed > 100)
				{
					m_apObject[nCnt]->m_nCntDownSpeed = 100;
				}

				m_apObject[nCnt]->SetPosition(pos);  //�ʒu�̐ݒ�
				m_apObject[nCnt]->SetRotation(rot);  //�����̐ݒ�

				//-------------------------------------------------------
				//�G�̃f�o�b�N�\��
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("�{�X���_�E������X�s�[�h [%d]\n", m_apObject[nCnt]->m_nCntDownSpeed);
			}
		}
	}
}
//-------------------------------------------------------
//�G�̃q�b�g����
//-------------------------------------------------------
void CEnemy3D::HitEnemy(int nDamage, int nCnt)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	if (m_apObject[nCnt] != NULL)
	{
		D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
		int typetex = m_apObject[nCnt]->GetTypeTex();

		m_apObject[nCnt]->m_Life -= nDamage;  //���C�t������������

		if (m_apObject[nCnt]->m_Life <= 0)
		{
			//�ʏ�G�̎�
			if (typetex == TYPE_USUALLY)
			{
				//�����̐���
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), D3DXVECTOR3(200.0f, 200.0f, 0.0f));

				//���S���
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//�����̏I������
				m_apObject[nCnt]->Uninit();
			}

			//�{�X�̎�
			else if (typetex == TYPE_BOSS)
			{
				//�����̐���
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), D3DXVECTOR3(200.0f, 200.0f, 0.0f));

				//���S���
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//�����̏I������
				m_apObject[nCnt]->Uninit();

				//�Q�[���̏�Ԃ̐ݒ�
				CGame::SetGameState(CGame::GAMESTATE_END, 60);
			}

			//SE�̍Đ�
			pSound->PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}

		else
		{
			//�ʏ�G�̎�
			if (typetex == TYPE_USUALLY || typetex == TYPE_BOSS)
			{
				m_apObject[nCnt]->SetState(CObject::STATE_DAMAGE, 20);  //�_���[�W���
				m_apObject[nCnt]->SetEnemyState(ENEMYSTATE_DAMAGE, 20);  //�_���[�W���

				D3DXMATERIAL redMat;
				ZeroMemory(&redMat, sizeof(redMat));
				redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				 m_apObject[nCnt]->SetMat(0, redMat);
				m_apObject[nCnt]->m_LifeGaugeSize = true;  //���C�t�Q�[�W�T�C�Y���ύX�o�����Ԃɂ���
			}

			//�`���[�g���A���G�̎�
			if (typetex == TYPE_TUTORIAL_ENE)
			{
				m_apObject[nCnt]->SetState(CObject::STATE_DAMAGE, 20);  //�_���[�W���
				m_apObject[nCnt]->SetEnemyState(ENEMYSTATE_DAMAGE, 60);  //�_���[�W���
			}

			//SE�̍Đ�
			pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//�e�Ƃ̓����蔻��
//-------------------------------------------------------
bool CEnemy3D::CollisionBullet(CBullet3D *pBullet)
{
	//��ނ��擾
	CObject::TYPE type = pBullet->GetType();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			//��ނ��e�̏ꍇ
			if (type == CObject::TYPE_BULLET)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //�X�P�[���̎擾
				D3DXVECTOR3 posBullet = pBullet->GetPosition();  //�e�̈ʒu�擾
				D3DXVECTOR3 scaleBullet = pBullet->GetScale();  //�e�̃X�P�[���擾
				int typetex = m_apObject[nCnt]->GetTypeTex();

				//�ʏ�̎�
				if (typetex == TYPE_USUALLY)
				{
					//�G�Əd�Ȃ�����
					if (pos.x + scale.x * USUALLY_COR_X > posBullet.x - scaleBullet.x * BULLET_COL_XZ
						&&  pos.x - scale.x * USUALLY_COR_X < posBullet.x + scaleBullet.x * BULLET_COL_XZ
						&&  pos.y + scale.y * USUALLY_COR_Y > posBullet.y - scaleBullet.y * BULLET_COL_Y
						&&  pos.y - scale.y < posBullet.y + scaleBullet.y
						&&  pos.z + scale.z * USUALLY_COR_Z > posBullet.z - scaleBullet.z * BULLET_COL_XZ
						&&  pos.z - scale.z * USUALLY_COR_Z < posBullet.z + scaleBullet.z * BULLET_COL_XZ)
					{
						//�G�̃q�b�g����
						CEnemy3D::HitEnemy(100, nCnt);

						pBullet->Uninit();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//���C�t�Q�[�W
//-------------------------------------------------------
void CEnemy3D::LifeGauge(CLife *pLife)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			CObject::TYPE type = pLife->GetType();  //���

			//��ނ����C�t�̏ꍇ
			if (type == CObject::TYPE_LIFE)
			{
				//��ނ��擾
				int typetexEnemy = m_apObject[nCnt]->GetTypeTex();
				int lifeEnemy = m_apObject[nCnt]->m_Life;  //�{�X�̃��C�t�擾
				D3DXVECTOR3 GaugeSize = pLife->GetSize();  //�e�N�X�`���T�C�Y�̎擾
				
				if (typetexEnemy == TYPE_BOSS)
				{
					if (lifeEnemy > 1100)
					{
						pLife->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					}

					else if (lifeEnemy < 1100 && lifeEnemy > 500)
					{
						pLife->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
					}

					else if (lifeEnemy <= 400)
					{
						pLife->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					}

					//�_���[�W���󂯂���
					if (m_apObject[nCnt]->m_state == ENEMYSTATE_DAMAGE && m_apObject[nCnt]->m_LifeGaugeSize == true)
					{
						GaugeSize.x -= 100.0f;  //�e�N�X�`�������������Ă���
					}
				}

				//-------------------------------------------------------
				//�G�̃f�o�b�N�\��
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("�{�X�̃��C�t�Q�[�W�T�C�Y [%f]\n", GaugeSize.x);
				
				pLife->SetSize(GaugeSize);
			}
		}
	}
}
//-------------------------------------------------------
//�̗͂̐ݒ菈��
//-------------------------------------------------------
void CEnemy3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//�{�X���_�E�����Ă邩�̐ݒ�
//-------------------------------------------------------
void CEnemy3D::SetBossDownState(bool BossDownState)
{
	m_BossDownState = BossDownState;
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CEnemy3D::SetEnemyState(ENEMYSTATE state, int nCounterState)
{
	m_state = state;
	m_nCounterState = nCounterState;
}
//-------------------------------------------------------
//�{�X�̐퓬�Ԑ����
//-------------------------------------------------------
void CEnemy3D::SetBossBattel(BOSS_BATTEL BossBattel)
{
	m_BossBattel = BossBattel;
}