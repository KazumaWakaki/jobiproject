//=============================================================================
//
// ���f���z�u���� [modelset.cpp]
// Author ��� ��^
//
//=============================================================================
#include "modelset.h"
#include "manager.h"
#include "player3D.h"
#include "bullet3D.h"

//�}�N����`
#define POS_Y (0.0f)  //�ʒuY�̒���

//�ÓI�����o�ϐ�
CModelSet *CModelSet::m_apObject[MAX_MODEL] = {};
int CModelSet::m_nCntBreakCore = 0;
//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CModelSet::CModelSet()
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
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
CModelSet::~CModelSet()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CModelSet::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //���f���̃|�C���^

	m_nIdxModel[TYPE_SWORD] = pModel->Regist("data\\MODEL\\sword.x");  //���{��
	m_nIdxModel[TYPE_CHECKPOINT] = pModel->Regist("data\\MODEL\\neonfloor001.x");  //�`�F�b�N�|�C���g
	m_nIdxModel[TYPE_BOSSCORE] = pModel->Regist("data\\MODEL\\core.x");  //�{�X�R�A
	m_nIdxModel[TYPE_BEAM_PLA] = pModel->Regist("data\\MODEL\\beameffect.x");  //�r�[��
	m_nIdxModel[TYPE_BEAM_ENE] = pModel->Regist("data\\MODEL\\beameffect.x");  //�r�[��
	m_nIdxModel[TYPE_WALL] = pModel->Regist("data\\MODEL\\wall001.x");  //����̕�
	m_nIdxModel[TYPE_JAMP_BOARD] = pModel->Regist("data\\MODEL\\jamp_board.x");  //�W�����v�Ŕ�
	m_nIdxModel[TYPE_STEP_BOARD] = pModel->Regist("data\\MODEL\\step_board.x");  //�X�e�b�v�Ŕ�

	//���f���̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_MODEL);

	//�l�̏�����
	m_AttackSwordCnt = 0;
	m_nCntSwordRot = 200;
	m_BreakCore = false;
	m_BossCoreState = BOSSCORESTATE_NONE;
	m_SwordTag = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CModelSet::Uninit()
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
void CModelSet::Update()
{
	//���{�������ړ�����
	SwordRotMove();

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	D3DXVECTOR3 pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 scale = GetScale();  //�X�P�[���̎擾
	int typetex = GetTypeTex();  //�^�C�v����p

#if _DEBUG

	//B�L�[�������ꂽ��
	if (pInputKeyboard->GetPress(DIK_B) == true)
	{
		rot.x += 0.05f;
	}

	//N�L�[�������ꂽ��
	if (pInputKeyboard->GetPress(DIK_N) == true)
	{
		rot.y += 0.05f;
	}

	//M�L�[�������ꂽ��
	if (pInputKeyboard->GetPress(DIK_M) == true)
	{
		rot.z += 0.05f;
	}

	//ENTER�L�[�������ꂽ��
	if (pInputKeyboard->GetPress(DIK_RETURN) == true)
	{
		rot.x = 0.0f;
		rot.y = 0.0f;
		rot.z = 0.0f;
	}

#endif

	//�ʒu�̕␳
	if (pos.x >= 10000.0f)
	{
		pos.x = 10000.0f;
	}

	//�p�x�̕␳
	if (rot.x > D3DX_PI)
	{
		rot.x += -D3DX_PI * 2;
	}
	
	if (rot.x < -D3DX_PI)
	{		 
		rot.x += D3DX_PI * 2;
	}

	//�p�x�̕␳
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	//�p�x�̕␳
	if (rot.z > D3DX_PI)
	{
		rot.z = -D3DX_PI;
	}

	if (rot.z < -D3DX_PI)
	{
		rot.z = D3DX_PI;
	}

	if (typetex == TYPE_BEAM_PLA || typetex == TYPE_BEAM_ENE)
	{
		m_nCntBeamScale++;

		scale.z += 0.08f;
	}

	SetPosition(pos);
	SetRotation(rot);
	SetScale(scale);

	if (m_nCntBeamScale >70)
	{
		Uninit();
	}

	CEnemy3D::EnemyBattelState(this);  //�G�ʂ̐퓬�Ԑ���Ԃ��Ƃ̏���

	//�I�u�W�F�N�g�̃^�C�v�����{���̂Ƃ�
	if (typetex == TYPE_SWORD)
	{
		//-------------------------------------------------------
		//���f���̃f�o�b�N�\��
		//-------------------------------------------------------
		CManager::GetInstance()->GetDebugProc()->Print("���{���ʒu [%f, %f, %f]\n", pos.x, pos.y, pos.z);
		CManager::GetInstance()->GetDebugProc()->Print("���{������ [%f, %f, %f]\n", rot.x, rot.y, rot.z);
	}
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CModelSet::Draw()
{
	int typetex = GetTypeTex();  //�^�C�v����p

	//if (typetex != TYPE_CHECKPOINT)
	{
		//���f��X�̕`�揈��
		CObjectX::Draw();
	}
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CModelSet *CModelSet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex)
{
	CModelSet *pModelSet = NULL;

	//���f���̐���
	pModelSet = new CModelSet;

	if (pModelSet != NULL)
	{
		//����������
		pModelSet->Init();
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	pModelSet->SetPosition(pos);  //�ʒu�̐ݒ�
	pModelSet->SetRotation(rot);  //�����̐ݒ�
	pModelSet->SetScale(scale);  //�g�嗦�̐ݒ�
	pModelSet->SetSize(size);  //�T�C�Y�ݒ�
	pModelSet->SetTypeTex(SetTypeTex);  //�e�N�X�`���^�C�v�ݒ�

	//nCount����
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCount�ƑI�����ꂽ���f������v������
		if (nCount == SetTypeTex)
		{
			//���f���̊��蓖��
			pModelSet->BindModel(pModelSet->m_nIdxModel[nCount]);
		}
	}

	return pModelSet;
}
//-------------------------------------------------------
//�v���C���[�Ƃ̓����蔻�菈��
//-------------------------------------------------------
bool CModelSet::ModelCollision(CPlayer3D *pPlayer)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 m_scale = m_apObject[nCnt]->GetScale();  //�g�嗦�̎擾
			CObject::TYPE type;  //���
			type = pPlayer->GetType();   //��ނ��擾

			 //��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //�v���C���[�̌����̎擾
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //�v���C���[�̊g�嗦�̎擾
				D3DXVECTOR3 PLACOL = posPlayer;  //�v���C���[�̌����œ����蔻��
				int typetex = m_apObject[nCnt]->GetTypeTex();  //�^�C�v����p

				//�`�F�b�N�|�C���g�̎�
				if (typetex == TYPE_CHECKPOINT)
				{
					D3DXVECTOR3  KeepPos;  //�v���C���[�̈ʒu��ۑ��p

					//�v���C���[�Əd�Ȃ�����
					if (pos.x - m_scale.x * CHECKPOINT_COR < posPlayer.x + scalePlayer.x * PLAYER_COL_X
						&&  pos.x + m_scale.x * CHECKPOINT_COR > posPlayer.x - scalePlayer.x * PLAYER_COL_X
						&&  pos.y - m_scale.y * CHECKPOINT_COR < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  pos.z - m_scale.z * CHECKPOINT_COR < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 120.0f
						&&  pos.z + m_scale.z * CHECKPOINT_COR > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 120.0f)
					{
						KeepPos = pPlayer->GetPosition();  //���݂̃v���C���[�̈ʒu��ۑ�
						KeepPos.x = pos.x;  //�`�F�b�N�|�C���g�̐^�񒆂Ɉʒu����
						KeepPos.y = pos.y + 200.0f;  //�`�F�b�N�|�C���g�̐^�񒆂Ɉʒu����
						pPlayer->SetKeepPos(KeepPos);  //�ۑ�����Ă���ʒu�̐ݒ�
						m_apObject[nCnt]->Uninit();  //�I������

						//SE�̍Đ�
						pSound->PlaySound(SOUND_LABEL_SE_CHECKPOINT);

						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//�e�Ƃ̓����蔻��
//-------------------------------------------------------
bool CModelSet::CollisionBullet(CBullet3D *pBullet)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	//��ނ��擾
	CObject::TYPE type = pBullet->GetType();

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
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
				int typetex = m_apObject[nCnt]->GetTypeTex();  //�e�N�X�`���^�C�v�擾

				//�{�X�R�A�̎�
				if (typetex == TYPE_BOSSCORE)
				{
					//�v���C���[�̒e�Əd�Ȃ�����
					if (pos.x + scale.x * BOSSCORE_COR_X > posBullet.x - scaleBullet.x * BULLET_COL_XZ
						&&  pos.x - scale.x * BOSSCORE_COR_X < posBullet.x + scaleBullet.x * BULLET_COL_XZ
						&&  pos.y + scale.y * BOSSCORE_COR_Y > posBullet.y - scaleBullet.y * BULLET_COL_Y
						&&  pos.y - scale.y < posBullet.y + scaleBullet.y
						&&  pos.z + scale.z * BOSSCORE_COR_Z > posBullet.z - scaleBullet.z * BULLET_COL_XZ
						&&  pos.z - scale.z * BOSSCORE_COR_Z < posBullet.z + scaleBullet.z * BULLET_COL_XZ)
					{
						pBullet->Uninit();  //�e������

						m_apObject[nCnt]->SetBreakCore(true);
						pos.x = 10000.0f;  //�R�A�̈ʒu���΂�
						m_apObject[nCnt]->m_nCntBreakCore += 1;

						//�R�A����j�󂳂ꂽ�Ƃ�
						if (m_apObject[nCnt]->m_nCntBreakCore == 2)
						{
							m_apObject[nCnt]->SetBossCoreState(BOSSCORESTATE_BREAK);  //�R�A����ꂽ��Ԃɂ���
							m_apObject[nCnt]->m_nCntBreakCore += 1;
						}

						//�R�A���ǉ��ŎO�j�󂳂ꂽ�Ƃ�
						if (m_apObject[nCnt]->m_nCntBreakCore == 6)
						{
							m_apObject[nCnt]->SetBossCoreState(BOSSCORESTATE_BREAK);  //�R�A����ꂽ��Ԃɂ���
						}

						m_apObject[nCnt]->SetPosition(pos);  //�ʒu�̐ݒ�

						return TRUE;
					}
				}

				//-------------------------------------------------------
				//���f���̃f�o�b�N�\��
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("�R�A�j��J�E���^�[ [%d]\n", m_apObject[nCnt]->m_nCntBreakCore);
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//���{�������ړ�����
//-------------------------------------------------------
void CModelSet::SwordRotMove(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	D3DXVECTOR3 pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 posOld = GetPositionOld();  //�ߋ��̈ʒu�̎擾
	D3DXVECTOR3 rot = GetRotation();  //�����̎擾
	int typetex = GetTypeTex();  //�^�C�v����p
	posOld = pos;  //�ߋ��̈ʒu�Ɍ��݂̈ʒu������

	//�I�u�W�F�N�g�̃^�C�v�����{���̂Ƃ�
	if (typetex == TYPE_SWORD)
	{
		//�U���L�[���������Ƃ�
		if (pInputKeyboard->GetTrigger(DIK_V) == true && m_SwordRot == SWORDROT_0
			|| pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0) && m_SwordRot == SWORDROT_0)
		{
			m_nCntSwordRot = 0;
			m_SwordRot = SWORDROT_1;
		}

		if (m_SwordRot == SWORDROT_1)
		{
			rot.x = -1.57f;

			if (m_nCntSwordRot < 15)
			{
				m_SwordRotTag = rot;
				m_SwordRotTag.y += 0.2f;  //�ڕW�n�_Y
			}

			D3DXVECTOR3 RotDest = m_SwordRotTag - GetRotation();
			rot.y = GetRotation().y + RotDest.y * 0.8f;  //����������

			if (m_nCntSwordRot > 50)
			{
				//�l�̏�����
				rot.x = 0.0f;
				rot.y = 0.0f;
				m_nCntSwordRot = 0;
				m_SwordRot = SWORDROT_0;  //�U�����Ă��Ȃ��ɂ���
			}

			m_nCntSwordRot++;
		}

		SetPosition(pos);  //�ʒu�̐ݒ�
		SetRotation(rot);  //�����̐ݒ�
		SetSwordRot(m_SwordRot);

		//-------------------------------------------------------
		//���f���̃f�o�b�N�\��
		//-------------------------------------------------------
		CManager::GetInstance()->GetDebugProc()->Print("�U���i�K [%d]\n", m_SwordRot);
		CManager::GetInstance()->GetDebugProc()->Print("�U���J�E���g [%d]\n", m_nCntSwordRot);
	}
}
//-------------------------------------------------------
//���{���̈ړ�����
//-------------------------------------------------------
void CModelSet::SwordMove(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			//�L�[�{�[�h�̎擾
			CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

			//�Q�[���p�b�h�̎擾
			CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
			SWORDROT SwordRot = m_apObject[nCnt]->GetSwordRot();  //���{���̍U��3�i�K�̎擾
			CObject::TYPE type;  //���
			CPlayer3D::PLAYERJAMP jamp = pPlayer->GetJamp();  //�v���C���[�̃W�����v��Ԏ擾
			type = pPlayer->GetType();   //��ނ��擾
			int typetex = m_apObject[nCnt]->GetTypeTex();  //�^�C�v����p

			//��ނ��v���C���[�̏ꍇ
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //�v���C���[�̈ړ��ʂ̎擾
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //�v���C���[�̌����̎擾

				//�I�u�W�F�N�g�̃^�C�v�����{���̂Ƃ�
				if (typetex == TYPE_SWORD)
				{
					pos.x = posPlayer.x + sinf(rotPlayer.y + D3DX_PI * -0.85f) * 150.0f;
					pos.y = posPlayer.y + 100.0f + sinf(rotPlayer.x + D3DX_PI) * 150.0f;
					pos.z = posPlayer.z + cosf(rotPlayer.y + D3DX_PI * -0.85f) * 150.0f;

#if 1
					if (SwordRot == SWORDROT_0)
					{
						rot.y = rotPlayer.y - D3DX_PI;
						rot.x = rotPlayer.x + D3DX_PI;
					}
#endif

					//�v���C���[�̃��X�|�[����Ԃ��ʏ�̂Ƃ�
					if (pPlayer->GetStateRes() == pPlayer->STATERES_NONE)
					{
						//�v���C���[���n�ʂɂ���Ƃ�
						if (jamp == pPlayer->PLAYERJUMP_GROUND)
						{
							//�O���E�ړ����Ă��鎞
							if (pInputKeyboard->GetPress(DIK_W) == true || pInputPad->CInputPad::GetJoyStickLY(0) > 0
								|| pInputKeyboard->GetPress(DIK_A) == true || pInputPad->CInputPad::GetJoyStickLX(0) < 0
								|| pInputKeyboard->GetPress(DIK_D) == true || pInputPad->CInputPad::GetJoyStickLX(0) > 0)
							{
								if (m_apObject[nCnt]->m_nCntSword < 15)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y += 3.0f;  //�ڕW�n�_
								}
								else if (m_apObject[nCnt]->m_nCntSword < 30)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y -= 3.0f;  //�ڕW�n�_
								}

								D3DXVECTOR3 PosDest = m_apObject[nCnt]->m_SwordTag - m_apObject[nCnt]->GetPosition();
								pos.y = m_apObject[nCnt]->GetPosition().y + PosDest.y * 0.1f;  //����������

								if (m_apObject[nCnt]->m_nCntSword > 45)
								{
									m_apObject[nCnt]->m_nCntSword = 0;  //�J�E���g��߂�
								}
							}

							//���ړ����Ă��鎞
							if (pInputKeyboard->GetPress(DIK_S) == true
								|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
							{
								if (m_apObject[nCnt]->m_nCntSword < 15)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y -= 3.0f;  //�ڕW�n�_
								}

								else if (m_apObject[nCnt]->m_nCntSword < 30)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y += 3.0f;  //�ڕW�n�_
								}

								D3DXVECTOR3 PosDest = m_apObject[nCnt]->m_SwordTag - m_apObject[nCnt]->GetPosition();
								pos.y = m_apObject[nCnt]->GetPosition().y + PosDest.y * 0.1f;  //����������

								if (m_apObject[nCnt]->m_nCntSword > 45)
								{
									m_apObject[nCnt]->m_nCntSword = 0;  //�J�E���g��߂�
								}
							}
						}

						m_apObject[nCnt]->m_nCntSword++;
					}

					m_apObject[nCnt]->SetPosition(pos);  //�ʒu�̐ݒ�
					m_apObject[nCnt]->SetRotation(rot);  //�����̐ݒ�

					//-------------------------------------------------------
					//���f���̃f�o�b�N�\��
					//-------------------------------------------------------
					//CManager::GetInstance()->GetDebugProc()->Print("���㉺�J�E���g [%d]\n", m_apObject[nCnt]->m_nCntSword);
					//CManager::GetInstance()->GetDebugProc()->Print("�W�����v [%d]\n", jamp);
				}
			}
		}
	}
}
//-------------------------------------------------------
//�{�X�̃R�A�ړ��ʏ���
//-------------------------------------------------------
void CModelSet::CoreMove(CEnemy3D *pEnemy)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			//�L�[�{�[�h�̎擾
			CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

			//�Q�[���p�b�h�̎擾
			CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //�����̎擾
			CObject::TYPE type;  //���
			type = pEnemy->GetType();   //��ނ��擾
			int typetex = m_apObject[nCnt]->GetTypeTex();  //�^�C�v����p

			//��ނ��G�̏ꍇ
			if (type == CObject::TYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //�G�̈ʒu�̎擾
				D3DXVECTOR3 rotEnemy = pEnemy->GetRotation();  //�G�̌����̎擾
				CEnemy3D::BOSS_BATTEL BossBattel = pEnemy->GetBossBattel();  //�{�X�̐퓬�Ԑ����

				//�{�X�R�A�̂Ƃ�
				if (typetex == TYPE_BOSSCORE)
				{
					rot.y += 0.005f;

					if (BossBattel == CEnemy3D::BOSS_BATTEL_1)
					{
						if (m_apObject[nCnt]->m_BreakCore == false)
						{
							if (m_apObject[nCnt]->m_nID == 5)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * 150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 150.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

							if (m_apObject[nCnt]->m_nID == 6)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * -150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 150.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 400.0f;
							}
						}
					}

					if (BossBattel == CEnemy3D::BOSS_BATTEL_2)
					{
						if (m_apObject[nCnt]->m_BreakCore == false)
						{
							if (m_apObject[nCnt]->m_nID == 7)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * 0.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 300.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

							if (m_apObject[nCnt]->m_nID == 8)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * 150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 300.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

							if (m_apObject[nCnt]->m_nID == 9)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * -150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 300.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

						}
					}

					m_apObject[nCnt]->SetPosition(pos);  //�ʒu�̐ݒ�
					m_apObject[nCnt]->SetRotation(rot);  //�����̐ݒ�

					//-------------------------------------------------------
					//���f���̃f�o�b�N�\��
					//-------------------------------------------------------
					//CManager::GetInstance()->GetDebugProc()->Print("���㉺�J�E���g [%d]\n", m_apObject[nCnt]->m_nCntSword);
					//CManager::GetInstance()->GetDebugProc()->Print("�W�����v [%d]\n", jamp);
				}
			}
		}
	}
}
//-------------------------------------------------------
//�R�A�̔j�󂳂ꂽ���J�E���^�[�̐ݒ�
//-------------------------------------------------------
void CModelSet::SetnCntBreakCore(int nCntBreakCore)
{
	m_nCntBreakCore += nCntBreakCore;
}
//-------------------------------------------------------
//�R�A����ꂽ���̊m�F�̐ݒ�
//-------------------------------------------------------
void CModelSet::SetBreakCore(bool BreakCore)
{
	m_BreakCore = BreakCore;
}
//-------------------------------------------------------
//���{���̍U��3�i�K�̐ݒ�
//-------------------------------------------------------
void CModelSet::SetSwordRot(SWORDROT SwordRot)
{
	m_SwordRot = SwordRot;
}
//-------------------------------------------------------
//�{�X���_�E�����Ă邩�̐ݒ�
//-------------------------------------------------------
void CModelSet::SetBossCoreState(BOSSCORESTATE BossCoreState)
{
	m_BossCoreState = BossCoreState;
}