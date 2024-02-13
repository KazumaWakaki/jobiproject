//=============================================================================
//
// �v���C���[3D���� [player3D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "bullet3D.h"
#include "explosion.h"
#include "game.h"
#include "modelset.h"
#include "block3D.h"
#include "camera.h"
#include "effect.h"

//�}�N����`
#define PLAYERJAMPSPEED (3.0f)  //�W�����v���̗����X�s�[�h
#define JAMPCNT (10)  //�d�͂�������܂ł̃J�E���g
#define BULLETSPEED (10.0f)  //�v���C���[�̒e�X�s�[�h
#define ATTACKCNT (20)  //�A�^�b�N�J�E���g
#define LONGCNT (62)  //�����O�J�E���g
#define ATTACKGAGE (100)  //�A�^�b�N�Q�[�W
#define PLAYER_COR_REFLECTION (200.0f)  //���ˎ��̓����蔻��

//�ÓI�����o�ϐ�
CPlayer3D *CPlayer3D::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CPlayer3D::CPlayer3D()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CPlayer3D::~CPlayer3D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CPlayer3D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CModel *pModel = CManager::GetInstance()->GetModel();  //���f���̃|�C���^

	//���f����錾
	m_nIdxModel = pModel->Regist("data\\MODEL\\rob001.x");  //�v���C���[

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_PLAYER);

	//��ԊǗ��ݒ�
	CObjectX::SetState(CObject::STATE_NORMAL, 0);

	//���C�t�̐ݒ�
	m_Life = PLALIFE;

	m_apObject->SetLife(m_Life);

	//�l��������
	m_nCntDown = 0;
	m_nCntAttack = 0;
	m_nCntStep = 0;
	m_StepGaugeCnt = 0;
	m_Step = false;
	m_StepPossible = false;
	m_jump = PLAYERJUMP_GROUND;
	m_SwordAttack = SWORDATTACK_0;
	m_StateRes = STATERES_NONE;
	m_StepState = STEPSTATE_NONE;
	m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_KeepPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_StepGauge = PLASTAMINA_MAX;  //�X�^�~�i�������X�^�[�g

	//���{���̐���
	CModelSet::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_SWORD);

	//�N���X�w�A����
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 5.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_CROSS);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CPlayer3D::Uninit()
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CPlayer3D::Update()
{
	D3DXVECTOR3 pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 move = GetMove();	//�ړ��ʂ̎擾
	D3DXVECTOR3 rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 scale = GetSize();  //�T�C�Y�̎擾

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	SetPositionOld(pos);  //�ߋ��̈ʒu�ݒ�

	//��ԊǗ��ݒ�
	CObject::UpdateState();

	//�v���C���[�̋ߐڍU��
	CEnemy3D::PlayerAttack(this);

	//�G�̏e�U��
	CEnemy3D::ShootBullet(this);

	///////////////////////////////////////////
	//���X�|�[����Ԃ��ʏ�̎�
	///////////////////////////////////////////
	if (m_StateRes == STATERES_NONE)
	{
		///////////////////////////////////////////
		//�v���C���[�L�[�{�[�h����
		///////////////////////////////////////////
		//D�L�[��������Ă��鎞
		if (pInputKeyboard->GetPress(DIK_D) == true
			|| pInputPad->CInputPad::GetJoyStickLX(0) > 0)
		{
			//D�L�[��������Ă��鎞��W�L�[��������Ă��鎞
			if (pInputKeyboard->GetPress(DIK_W) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) > 0)
			{
				//�E��ړ�
				move.x += sinf(rot.y + D3DX_PI * -0.75f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * -0.75f) * PLAYERSPEED;
			}

			//D�L�[��������Ă��鎞��S�L�[��������Ă��鎞
			else if (pInputKeyboard->GetPress(DIK_S) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
			{
				//�E���ړ�
				move.x += sinf(rot.y + D3DX_PI * -0.25f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * -0.25f) * PLAYERSPEED;
			}

			else
			{
				//D�L�[�������ꂽ
				move.x += sinf(rot.y + D3DX_PI * -0.5f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * -0.5f) * PLAYERSPEED;
			}
		}

		//A�L�[��������Ă��鎞
		else if (pInputKeyboard->GetPress(DIK_A) == true
			|| pInputPad->CInputPad::GetJoyStickLX(0) < 0)
		{
			//A�L�[��������Ă��鎞��W�L�[��������Ă��鎞
			if (pInputKeyboard->GetPress(DIK_W) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) > 0)
			{
				//����ړ�
				move.x += sinf(rot.y + D3DX_PI * 0.75f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * 0.75f) * PLAYERSPEED;
			}

			//A�L�[��������Ă��鎞��S�L�[��������Ă��鎞
			else if (pInputKeyboard->GetPress(DIK_S) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
			{
				//�����ړ�
				move.x += sinf(rot.y + D3DX_PI * 0.25f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * 0.25f) * PLAYERSPEED;
			}

			else
			{
				//A�L�[�������ꂽ
				move.x += sinf(rot.y + D3DX_PI * 0.5f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * 0.5f) * PLAYERSPEED;
			}
		}

		//W�L�[��������Ă��鎞
		else if (pInputKeyboard->GetPress(DIK_W) == true
			|| pInputPad->CInputPad::GetJoyStickLY(0) > 0)
		{
			//W�L�[�������ꂽ
			move.x += sinf(rot.y + D3DX_PI) * PLAYERSPEED;
			move.z += cosf(rot.y + D3DX_PI) * PLAYERSPEED;
		}

		//S�L�[��������Ă��鎞
		else if (pInputKeyboard->GetPress(DIK_S) == true
			|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
		{
			//S�L�[�������ꂽ
			move.x += sinf(rot.y) * PLAYERSPEED;
			move.z += cosf(rot.y) * PLAYERSPEED;
		}

		//�W�����v
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_jump == PLAYERJUMP_GROUND   //SPACE�������ꂽ��
			|| pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) && m_jump == PLAYERJUMP_GROUND)  //A�{�^���������ꂽ��
		{
			move.y = 100.0f;  //��Ɉړ�����
			pos.y -= move.y;  //����
			move.y -= 0.3f;  //�d�͂�������

			m_nCntDown = 0;

			m_jump = PLAYERJUMP_SKY;  //�W�����v���Ă����Ԃɂ���

			//SE�̍Đ�
			pSound->PlaySound(SOUND_LABEL_SE_JAMP);
		}
	}

	///////////////////////////////////////////
	//���X�|�[����Ԃ��ҋ@�̎�
	///////////////////////////////////////////
	if (m_StateRes == STATERES_RESPAWN)
	{
		//SPACE�L�[�������ꂽ�Ƃ�
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
		{
			//���X�|�[����Ԃ�ʏ�ɂ���
			SetStateRes(STATERES_NONE);
		}
	}

	if (m_nCntDown > JAMPCNT)
	{
		//�X�e�b�v��Ԃ�false�̎�
		if (m_Step == false)
		{
			//�d�͂�������
			move.y -= 4.0f;
		}
	}

	//�X�e�b�v��Ԃ�true�̎�
	if (m_Step == true)
	{
		if (m_nCntStep > 10)
		{
			m_Step = false;
		}
	}

	//�C���N�������g
	m_nCntDown++;
	m_nCntStep++;

	//�ʒu�̍X�V
	pos += move;

	//�ړ��ʂ��X�V
	move.x += (0.0f - move.x) * PLAYERSPEEDUP;
	move.y += (0.0f - move.y) * PLAYERSPEEDUP;
	move.z += (0.0f - move.z) * PLAYERSPEEDUP;

	//�p�x�̕␳
	if (rot.x > D3DX_PI)
	{
		rot.x += -D3DX_PI * 2;
	}

	if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2;
	}

	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	///////////////////////////////////////////
	//�ݒ菈��
	///////////////////////////////////////////
	SetPosition(pos);  //�ʒu�̐ݒ�
	SetMove(move);  //�ړ��ʂ̐ݒ�
	SetRotation(rot);  //�����̐ݒ�
	SetLife(m_Life);  //���C�t�̐ݒ�

	///////////////////////////////////////////
	//�����̍X�V
	///////////////////////////////////////////
	CModelSet::SwordMove(this);  //���̈ړ�����
	CBlock3D::CollisionPlayer(this);  //�u���b�N�Ƃ̓����蔻��
	CModelSet::ModelCollision(this);  //���f���Ƃ̓����蔻��
	CCamera::MoveCamera(this);  //�J�����Ǐ]
	CCamera::PlayerTriggerCamera(this);  //�v���C���[���S���J�����̌����̏���

	//�X�e�b�v��ԈȊO�̎�
	if (m_StepState != STEPSTATE_STEP)
	{
		if (m_nCntStep > PLASTAMINA_HEAL)
		{
			m_StepGauge++;  //�Q�[�W���񕜂���
			m_StepState = STEPSTATE_NONE;  //�ʏ��Ԃɂ���
		}
	}

	 //�X�e�b�v��Ԃ̎�
	if (m_StepState == STEPSTATE_STEP)
	{
		StepMode();  //�X�e�b�v��Ԃ̍X�V
	}

	if (m_StepGauge > PLASTAMINA_MAX)
	{
		m_StepGauge = PLASTAMINA_MAX;  //�X�^�~�i������񕜂��Ȃ��悤�ɂ���
	}

	if (m_Restart == true)
	{
		//�W�����v�L�[�������ꂽ��
		if (pInputKeyboard->GetRelease(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
		{
			//���X�^�[�g��Ԃ𖳌��ɂ���
			m_Restart = false;
		}
	}

	if (pos.y < -1000.0f)
	{
		//�v���C���[�̃q�b�g����
		CPlayer3D::HitPlayer(1000);
	}

	//-------------------------------------------------------
	//�v���C���[�̃f�o�b�N�\��
	//-------------------------------------------------------
	CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�ʒu [%f, %f, %f]\n", pos.x, pos.y, pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�ړ��� [%f, %f, %f]\n", move.x, move.y, move.z);
	CManager::GetInstance()->GetDebugProc()->Print("�v���C���[���� [%f, %f, %f]\n", rot.x, rot.y, rot.z);
	CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�̗� [%d]\n", m_Life);
	CManager::GetInstance()->GetDebugProc()->Print("�v���C���[�W�����v [%d]\n", m_jump);
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CPlayer3D::Draw()
{
	//�I�u�W�F�N�gX�̕`�揈��
	//CObjectX::Draw();  //�v���C���[��\�����Ȃ�
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size)
{
	CPlayer3D *pPlayer3D = NULL;

	//�v���C���[�̐���
	pPlayer3D = new CPlayer3D;

	if (pPlayer3D != NULL)
	{
		//����������
		pPlayer3D->Init();

		//�ʒu�̐ݒ�
		pPlayer3D->SetPosition(pos);

		//�����̐ݒ�
		pPlayer3D->SetRotation(rot);

		//�g�嗦�̐ݒ�
		pPlayer3D->SetScale(scale);

		//�g�嗦�ݒ�
		pPlayer3D->SetSize(size);

		//���f���̊��蓖��
		pPlayer3D->BindModel(pPlayer3D->m_nIdxModel);

		//---------------------------------------------------------------
		//���C�t�̐���
		//---------------------------------------------------------------
		CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(300.0f, 30.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
		CLife::Create(D3DXVECTOR3(10.0f, 650.0f, 0.0f), D3DXVECTOR3(410.0f, 40.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEFRAME);

		//---------------------------------------------------------------
		//�X�e�b�v�Q�[�W�̐���
		//---------------------------------------------------------------
		CGauge::Create(D3DXVECTOR3(590.0f, 380.0f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CGauge::TYPE_STEPFRAME);
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pPlayer3D;
}
//-------------------------------------------------------
//�X�e�b�v���
//-------------------------------------------------------
void CPlayer3D::StepMode(void)
{
	D3DXVECTOR3 pos = GetPosition();  //�ʒu�̎擾
	D3DXVECTOR3 move = GetMove();  //�ړ��ʂ̎擾
	D3DXVECTOR3 rot = GetRotation();  //�����̎擾
	D3DXVECTOR3 m_startpos = GetStartPos();  //�X�^�[�g�ʒu�̎擾

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	
	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	//�V�t�g�L�[��LB�{�^���������ꂽ��
	if (pInputKeyboard->GetRelease(DIK_LSHIFT) == true && GetStepPossible() == false
		|| pInputPad->GetRelease(CInputPad::BUTTON_LB, 0) && GetStepPossible() == false)
	{
		//���e�B�N���������Ă�������ɃX�e�b�v����
		move.x += sinf(rot.y + D3DX_PI) * STEPSPEED;
		move.y += sinf(rot.x + D3DX_PI) * 170.0f;
		move.z += cosf(rot.y + D3DX_PI) * STEPSPEED;

		m_Step = true;
		m_nCntStep = 0;
		m_StepGaugeCnt = 0;
		m_StepState = STEPSTATE_NONE;  //�ʏ��Ԃɂ���
		SetStepPossible(true);  //�X�e�b�v�\��Ԃ𖳌��ɂ���
	}

	//�l�̐ݒ�
	SetPosition(pos);
	SetMove(move);
	SetRotation(rot);
}
//-------------------------------------------------------
//�v���C���[�̃q�b�g����
//-------------------------------------------------------
void CPlayer3D::HitPlayer(int nDamage)
{
	//�T�E���h�̎擾
	CSound *pSound = CManager::GetInstance()->GetSound();;

	if (m_apObject != NULL)
	{
		m_apObject->m_Life -= nDamage;

		if (m_apObject->m_Life <= 0)
		{
			D3DXVECTOR3 move = m_apObject->GetMove();
			D3DXVECTOR3 KeepPos = m_apObject->GetKeepPos();

			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			KeepPos.z += 130;

			//������
			m_apObject->m_nCntDown = 0;
			m_apObject->m_nCntAttack = 0;
			m_apObject->m_nCntStep = 0;
			m_apObject->m_StepGaugeCnt = 0;
			m_apObject->m_Step = false;
			m_apObject->m_StepPossible = false;
			m_apObject->m_jump = PLAYERJUMP_GROUND;
			m_apObject->m_SwordAttack = SWORDATTACK_0;
			m_apObject->m_StateRes = STATERES_NONE;
			m_apObject->m_StepState = STEPSTATE_NONE;
			m_apObject->m_StepGauge = PLASTAMINA_MAX;  //�X�^�~�i�������X�^�[�g

			m_apObject->m_Restart = true;  //���X�^�[�g��Ԃ�L���ɂ���
			m_apObject->SetStateRes(STATERES_RESPAWN);  //���X�|�[����Ԃ�ҋ@��Ԃɂ���
			m_apObject->SetPosition(KeepPos);  //�`�F�b�N�|�C���g�̈ʒu�Ɉړ�����
			m_apObject->SetMove(move);  //�ړ��ʂ�0�ɂ���
			m_apObject->SetLife(PLALIFE);  //���C�t���Z�b�g

			//���X�|�[���ҋ@��������
			CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 70.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_RESPAWN);

			//���X�|�[���ҋ@��Ԃ̔w�i����
			CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), CObject2D::TYPE_RESPAWNBG);

			//SE�̍Đ�
			pSound->PlaySound(SOUND_LABEL_SE_DEATH);
		}
		else
		{
			m_apObject->SetState(CObject::STATE_DAMAGE, 20);  //�_���[�W���

			//SE�̍Đ�
			pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//�G�Ƃ̓����蔻��
//-------------------------------------------------------
bool CPlayer3D::CollisionEnemy(CEnemy3D *pEnemy)
{	
	///////////////////////////////////////////
	//���X�|�[����Ԃ��ʏ�̎�
	///////////////////////////////////////////
	if (m_apObject->m_StateRes == STATERES_NONE)
	{
		if (m_apObject != NULL)
		{
			D3DXVECTOR3 pos = m_apObject->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 m_Oldpos = m_apObject->GetPositionOld();  //�ߋ��̈ʒu�̎擾
			D3DXVECTOR3 move = m_apObject->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 scale = m_apObject->GetScale();  //�g�嗦�̎擾
			CObject::TYPE type = pEnemy->GetType();   //��ނ��擾
			int typetex = 0;  //�G�̎�ޗp
			int PlaLife = m_apObject->GetLife();  //�v���C���[�̃��C�t�擾

			if (PlaLife >= 0)
			{
				//��ނ��G�̏ꍇ
				if (type == CObject::TYPE_ENEMY)
				{
					D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //�G�̈ʒu�̎擾
					D3DXVECTOR3 scaleEnemy = pEnemy->GetScale();  //�G�̊g�嗦�̎擾
					typetex = pEnemy->GetTypeTex();  //�G�̎��

					//�G���ʏ�G�̎�
					if (typetex == CEnemy3D::TYPE_USUALLY)
					{
						///////////////////////////////////
						//X���̔���
						///////////////////////////////////
						//�G�Əd�Ȃ�����
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * USUALLY_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * USUALLY_COR_Y)
						{
							if ((pos.z + scale.z * PLAYER_COL_Z + 50.0f > posEnemy.z - scaleEnemy.z * USUALLY_COR_Z
								&& pos.z - scale.z * PLAYER_COL_Z + 50.0f < posEnemy.z + scaleEnemy.z * USUALLY_COR_Z))
							{
								if (m_Oldpos.x - scale.x * PLAYER_COL_X > posEnemy.x + scaleEnemy.x * USUALLY_COR_X
									&&  pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * USUALLY_COR_X)
								{//�E
									pos.x = posEnemy.x + scaleEnemy.x * USUALLY_COR_X + 29.0f;  //�G�����Ȃ��悤�ɂ���
									move.x = 0.0f;  //�ړ��ʂ�0�ɂ���
								}

								if (m_Oldpos.x + scale.x * PLAYER_COL_X < posEnemy.x - scaleEnemy.x * USUALLY_COR_X
									&&  pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * USUALLY_COR_X)
								{//��
									pos.x = posEnemy.x - scaleEnemy.x * USUALLY_COR_X - 29.0f;  //�G�����Ȃ��悤�ɂ���
									move.x = 0.0f;  //�ړ��ʂ�0�ɂ���
								}
							}
						}

						///////////////////////////////////
						//Z���̔���
						///////////////////////////////////
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * USUALLY_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * USUALLY_COR_Y)
						{
							if ((pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * USUALLY_COR_X
								&& pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * USUALLY_COR_X))
							{
								if (m_Oldpos.z - scale.z * PLAYER_COL_Z > posEnemy.z + scaleEnemy.z * USUALLY_COR_Z - 70.0f
									&&  pos.z - scale.z * PLAYER_COL_Z < posEnemy.z + scaleEnemy.z * USUALLY_COR_Z - 70.0f)
								{//������
									pos.z = posEnemy.z + scaleEnemy.z * USUALLY_COR_Z - 50.0f;  //�G�����Ȃ��悤�ɂ���
									move.z = 0.0f;  //�ړ��ʂ�0�ɂ���
								}

								if (m_Oldpos.z + scale.z * PLAYER_COL_Z < posEnemy.z - scaleEnemy.z * USUALLY_COR_Z - 120.0f
									&&  pos.z + scale.z * PLAYER_COL_Z > posEnemy.z - scaleEnemy.z * USUALLY_COR_Z - 120.0f)
								{//��O
									pos.z = posEnemy.z - scaleEnemy.z * USUALLY_COR_Z - 140.0f;  //�G�����Ȃ��悤�ɂ���
									move.z = 0.0f;  //�ړ��ʂ�0�ɂ���
								}
							}
						}
					}

					//�{�X�̎�
					else if (typetex == CEnemy3D::TYPE_BOSS)
					{
						///////////////////////////////////
						//X���̔���
						///////////////////////////////////
						//�G�Əd�Ȃ�����
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * BOSS_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * BOSS_COR_Y)
						{
							if ((pos.z + scale.z * PLAYER_COL_Z + 50.0f > posEnemy.z - scaleEnemy.z * BOSS_COR_Z
								&& pos.z - scale.z * PLAYER_COL_Z + 50.0f < posEnemy.z + scaleEnemy.z * BOSS_COR_Z))
							{
								if (m_Oldpos.x - scale.x * PLAYER_COL_X > posEnemy.x + scaleEnemy.x * BOSS_COR_X
									&&  pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * BOSS_COR_X)
								{//�E
									pos.x = posEnemy.x + scaleEnemy.x * BOSS_COR_X + 29.0f;  //�G�����Ȃ��悤�ɂ���
									move.x = 0.0f;  //�ړ��ʂ�0�ɂ���
								}

								if (m_Oldpos.x + scale.x * PLAYER_COL_X < posEnemy.x - scaleEnemy.x * BOSS_COR_X
									&&  pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * BOSS_COR_X)
								{//��
									pos.x = posEnemy.x - scaleEnemy.x * BOSS_COR_X - 29.0f;  //�G�����Ȃ��悤�ɂ���
									move.x = 0.0f;  //�ړ��ʂ�0�ɂ���
								}
							}
						}

						///////////////////////////////////
						//Z���̔���
						///////////////////////////////////
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * BOSS_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * BOSS_COR_Y)
						{
							if ((pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * BOSS_COR_X
								&& pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * BOSS_COR_X))
							{
								if (m_Oldpos.z - scale.z * PLAYER_COL_Z > posEnemy.z + scaleEnemy.z * BOSS_COR_Z - 70.0f
									&&  pos.z - scale.z * PLAYER_COL_Z < posEnemy.z + scaleEnemy.z * BOSS_COR_Z - 70.0f)
								{//������
									pos.z = posEnemy.z + scaleEnemy.z * BOSS_COR_Z - 50.0f;  //�G�����Ȃ��悤�ɂ���
									move.z = 0.0f;  //�ړ��ʂ�0�ɂ���
								}

								if (m_Oldpos.z + scale.z * PLAYER_COL_Z < posEnemy.z - scaleEnemy.z * BOSS_COR_Z - 120.0f
									&&  pos.z + scale.z * PLAYER_COL_Z > posEnemy.z - scaleEnemy.z * BOSS_COR_Z - 120.0f)
								{//��O
									pos.z = posEnemy.z - scaleEnemy.z * BOSS_COR_Z - 140.0f;  //�G�����Ȃ��悤�ɂ���
									move.z = 0.0f;  //�ړ��ʂ�0�ɂ���
								}
							}
						}
					}

					//�l�̐ݒ�
					m_apObject->SetPosition(pos);
					m_apObject->SetMove(move);
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//�e�Ƃ̓����蔻��
//-------------------------------------------------------
bool CPlayer3D::CollisionBullet(CBullet3D *pBullet)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();;

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();;

	//�T�E���h�̎擾
	CSound *pSound = CManager::GetInstance()->GetSound();;

	//��ނ��擾
	CObject::TYPE type = pBullet->GetType();

	if (m_apObject != NULL)
	{
		//��ނ��e�̏ꍇ
		if (type == CObject::TYPE_BULLET)
		{
			D3DXVECTOR3 pos = m_apObject->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 rot = m_apObject->GetRotation();  //�����̎擾
			D3DXVECTOR3 scale = m_apObject->GetScale();  //�g�嗦�̎擾
			D3DXVECTOR3 posBullet = pBullet->GetPosition();  //�e�̈ʒu�擾
			D3DXVECTOR3 rotBullet = pBullet->GetRotation();  //�e�̌����擾
			D3DXVECTOR3 scaleBullet = pBullet->GetScale();  //�e�̊g�嗦�擾
			D3DXVECTOR3 PLACOL = pos;  //�v���C���[�̌����œ����蔻��
			D3DXVECTOR3 fAngle = D3DXVECTOR3(posBullet.x - pos.x, posBullet.y - pos.y, posBullet.z - pos.z);
			D3DXVec3Normalize(&fAngle, &fAngle);

			PLACOL.x = pos.x + sinf(rot.y) * PLAYER_COL_X;
			PLACOL.z = pos.z + 50.0f + cosf(rot.y) * PLAYER_COL_Z;

			//�e�͈̔�
			float fRangth = sqrtf((PLACOL.x - posBullet.x) * (PLACOL.x - posBullet.x) + (PLACOL.z - posBullet.z) * (PLACOL.z - posBullet.z));

			//�v���C���[���画�肳��鋗��
			float fLength = 50.0f;

			float fRot = rot.y + D3DX_PI - rotBullet.y;

			//�p�x�̕␳
			if (fRot > D3DX_PI)
			{
				fRot += -D3DX_PI * 2;
			}

			if (fRot < -D3DX_PI)
			{
				fRot += D3DX_PI * 2;
			}

			//�v���C���[�Əd�Ȃ�O�ɍU���L�[����͂��Ă�����(����)
			if (fRangth > fLength
				&& fRangth < 1000.0f
				&& pInputKeyboard->GetTrigger(DIK_V) == true || pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0))
			{
				pBullet->Uninit();

				//�e����
				CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_PLAYER);

				//�G�t�F�N�g�̐���
				CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(50.0f, 50.0f, 100.0f), CEffect::EFFECTTYPE_BEAM);
			}

			//�v���C���[�ɓ���������
			else if (fRangth < fLength)
			{
				//�v���C���[�̃q�b�g����
				CPlayer3D::HitPlayer(100);

				return TRUE;
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//���C�t�ݒ菈��
//-------------------------------------------------------
void CPlayer3D::LifeMove(CLife *pLife)
{
	if (m_apObject != NULL)
	{
		CObject::TYPE type = pLife->GetType();  //���

		//��ނ��擾
		int typetex = pLife->GetTypeTex();
		int nLife = pLife->GetLife();

		//��ނ����C�t�̏ꍇ
		if (type == CObject::TYPE_LIFE)
		{
			int m_lifePlayer = m_apObject->GetLife();  //�v���C���[�̃��C�t�擾

			if (m_lifePlayer == 500 &&
				nLife != CLife::LIFE_500)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(300.0f, 30.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_500;
			}

			if (m_lifePlayer == 400 &&
				nLife != CLife::LIFE_400)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(240.0f, 30.0f, 0.0f), D3DXVECTOR3(0.8f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_400;
			}

			if (m_lifePlayer == 300 &&
				nLife != CLife::LIFE_300)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(180.0f, 30.0f, 0.0f), D3DXVECTOR3(0.6f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_300;
			}

			if (m_lifePlayer == 200 &&
				nLife != CLife::LIFE_200)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f), D3DXVECTOR3(0.4f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_200;
			}

			if (m_lifePlayer == 100 &&
				nLife != CLife::LIFE_100)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(60.0f, 30.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_100;
			}

			if (m_lifePlayer == 0)
			{
				//---------------------------------------------------------------
				//���C�t�̐���
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}
			}

			pLife->SetLife(nLife);
		}
	}
}
//-------------------------------------------------------
//�X�e�b�v�Q�[�W�ݒ菈��
//-------------------------------------------------------
void CPlayer3D::StepGaugeMove(CGauge *pGauge)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();;

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();;

	if (m_apObject != NULL)
	{
		//��ނ��擾
		CObject::TYPE type = pGauge->GetType();

		//��ނ��擾
		int typetex = pGauge->GetTypeTex();

		//��ނ��Q�[�W�̏ꍇ
		if (type == CObject::TYPE_GAUGE)
		{
			D3DXVECTOR3 pos = m_apObject->GetPosition();  //�ʒu�̎擾
			D3DXVECTOR3 move = m_apObject->GetMove();  //�ړ��ʂ̎擾
			D3DXVECTOR3 rot = m_apObject->GetRotation();  //�����̎擾
			D3DXVECTOR3 GaugeSize = pGauge->GetSize();  //�e�N�X�`���T�C�Y�̎擾
			D3DXVECTOR3 fAngle = D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z);
			D3DXVec3Normalize(&fAngle, &fAngle);

			if (GaugeSize.x > 100.0f)
			{
				GaugeSize.x = 100.0f;
			}

			if (m_apObject->m_StepState == STEPSTATE_NONE 
				|| m_apObject->m_StepState == STEPSTATE_OUTSTAMINA)
			{
				m_apObject->m_StepState = STEPSTATE_NONE;

				if (m_apObject->m_nCntStep > PLASTAMINA_HEAL)
				{
					m_apObject->m_StepState = STEPSTATE_NONE;  //�ʏ��Ԃɂ���

					if (m_apObject->m_StepGauge < PLASTAMINA_MAX)
					{
						GaugeSize.x += m_apObject->m_StepGauge * 0.01f;
					}
				}
			}

			if (m_apObject->m_StepGauge < 0)
			{
				m_apObject->m_StepGauge = 0;
				m_apObject->m_StepState = STEPSTATE_OUTSTAMINA;
			}

			//�X�^�~�i���؂�Ă��Ȃ��Ƃ�
			if (m_apObject->m_StepState != STEPSTATE_OUTSTAMINA)
			{
				//�V�t�g�L�[��LB�{�^����������Ă鎞
				if (pInputKeyboard->GetPress(DIK_LSHIFT) == true
					|| pInputPad->GetPress(CInputPad::BUTTON_LB, 0))
				{
					m_apObject->m_nCntStep = 0;
					m_apObject->m_StepState = STEPSTATE_STEP;  //�X�e�b�v��Ԃɂ���
					m_apObject->m_StepGaugeCnt++;
					m_apObject->m_StepGauge--;
					GaugeSize.x -= m_apObject->m_StepGaugeCnt * 0.01f;  //�e�N�X�`�������������Ă���

					if (m_apObject->m_StepGaugeCnt > PLASTAMINA_MAX)
					{
						//���e�B�N���������Ă�������ɃX�e�b�v����
						move.x += sinf(rot.y + D3DX_PI) * STEPSPEED;
						move.y += fAngle.y * 170.0f;
						move.z += cosf(rot.y + D3DX_PI) * STEPSPEED;

						m_apObject->m_StepGaugeCnt = 0;
						m_apObject->m_Step = true;
						m_apObject->m_StepState = STEPSTATE_OUTSTAMINA;  //�ʏ��Ԃɂ���
					}
				}
			}

			//�l�̐ݒ�
			m_apObject->SetMove(move);
			pGauge->SetSize(GaugeSize);

			//-------------------------------------------------------
			//�v���C���[�̃f�o�b�N�\��
			//-------------------------------------------------------
			CManager::GetInstance()->GetDebugProc()->Print("�X�^�~�i [%d]\n", m_apObject->m_StepGauge);
			CManager::GetInstance()->GetDebugProc()->Print("�X�e�b�v�J�E���g [%d]\n", m_apObject->m_StepGaugeCnt);
			CManager::GetInstance()->GetDebugProc()->Print("�X�e�b�v���[%d]\n", m_apObject->m_StepState);
		}
	}
}
//-------------------------------------------------------
//�̗͂̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//�X�e�b�v�\��Ԑ؂�ւ��̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetStepPossible(bool StepPossible)
{
	m_StepPossible = StepPossible;
}
//-------------------------------------------------------
//���X�^�[�g��Ԑ؂�ւ��̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetRestart(bool Restart)
{
	m_Restart = Restart;
}
//-------------------------------------------------------
//�W�����v�̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetPlayerJump(PLAYERJAMP Jamp)
{
	m_jump = Jamp;
}
//-------------------------------------------------------
//���{���̍U���i�K�̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetSwordAttack(SWORDATTACK SwordAttack)
{
	m_SwordAttack = SwordAttack;
}
//-------------------------------------------------------
//���X�|�[����Ԃ̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetStateRes(STATERES StateRes)
{
	m_StateRes = StateRes;
}
//-------------------------------------------------------
//�ۑ�����Ă���ʒu�̐ݒ�
//-------------------------------------------------------
void CPlayer3D::SetKeepPos(D3DXVECTOR3 KeepPos)
{
	m_KeepPos = KeepPos;
}