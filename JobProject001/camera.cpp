//=============================================================================
//
// �J�������� [camera.cpp]
// Author ��� ��^
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "player3D.h"

//�}�N����`
#define MOVE_SPEED  (3.0f)  //�ړ��X�s�[�h
#define ROLL_SPEED  (0.03f)  //��]�X�s�[�h
#define ROLLDIG_SPEED  (0.02f)  //�΂߂̉�]�X�s�[�h
#define ROLL_X  (0.5f)  //X���̍ő����

//�ÓI�����o�ϐ�
CCamera *CCamera::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CCamera::CCamera()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CCamera::~CCamera()
{

}
//=======================================================
//�J�����̏���������
//=======================================================
HRESULT CCamera::Init(void)
{
	//���[�J���ϐ��錾
	D3DXVECTOR3 StartRot;

	//�l�̏�����
	m_posV = D3DXVECTOR3(0.0f, 160.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 150.0f, 100.0f);
	m_vecU = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fLength = 90.0f;  //Y�ʂ̎��_���璍���_�܂ł̋���

	//PRIORITY����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT����
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //�I�u�W�F�N�g�N���X�̃|�C���^

			//�I�u�W�F�N�g���擾
			pObj = CObject::GetObject(nCntPriority, nCntObj);

			//pObj��NULL����Ȃ�������
			if (pObj != NULL)
			{
				CObject::TYPE type;  //���

				//��ނ��擾
				type = pObj->GetType();

				//��ނ��v���C���[�̏ꍇ
				if (type == CObject::TYPE_PLAYER)
				{
					//�����ʒu���v���C���[�̌���ɐݒ肷��
					StartRot = -pObj->GetRotation();

					//�ڕW�ʒu�܂ňړ�����
					m_posV.x = StartRot.y + (-D3DX_PI * 0.5f);
				}
			}
		}
	}

	return (S_OK);
}
//=======================================================
//�J�����̏I������
//=======================================================
void CCamera::Uninit(void)
{
	m_apObject = NULL;
}
//=======================================================
//�J�����̍X�V����
//=======================================================
void CCamera::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInstance()->GetInputPad();

	/////////////////////////////////
	//���_��]
	/////////////////////////////////
	//���Ɏ��_��������
	if (pInputKeyboard->GetPress(DIK_J) == true
		|| pInputPad->CInputPad::GetJoyStickRX(0) < 0)
	{
		//����ړ�
		if (pInputKeyboard->GetPress(DIK_I) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) > 0)
		{
			m_rot.y -= ROLLDIG_SPEED;
			m_rot.x += ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		//�����ړ�
		else if (pInputKeyboard->GetPress(DIK_K) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) < 0)
		{
			m_rot.y -= ROLLDIG_SPEED;
			m_rot.x -= ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		else
		{
			m_rot.y -= ROLL_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}
	}

	//�E�Ɏ��_��������
	else if (pInputKeyboard->GetPress(DIK_L) == true
		|| pInputPad->CInputPad::GetJoyStickRX(0) > 0)
	{
		//�E��ړ�
		if (pInputKeyboard->GetPress(DIK_I) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) > 0)
		{
			m_rot.y += ROLLDIG_SPEED;
			m_rot.x += ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		//�E���ړ�
		else if (pInputKeyboard->GetPress(DIK_K) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) < 0)
		{
			m_rot.y += ROLLDIG_SPEED;
			m_rot.x -= ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		else
		{
			m_rot.y += ROLL_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}
	}

	//��Ɏ��_��������
	else if (pInputKeyboard->GetPress(DIK_I) == true
		|| pInputPad->CInputPad::GetJoyStickRY(0) > 0)
	{
		m_rot.x += ROLL_SPEED;
	}

	//���Ɏ��_��������
	else if (pInputKeyboard->GetPress(DIK_K) == true
		|| pInputPad->CInputPad::GetJoyStickRY(0) < 0)
	{
		m_rot.x -= ROLL_SPEED;
	}

	//�p�x�̕␳
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	//�p�x�̕␳
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z += -D3DX_PI * 2;
	}

	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2;
	}

	if (m_rot.x > ROLL_X)
	{
		m_rot.x = ROLL_X;
	}

	if (m_rot.x < -ROLL_X)
	{
		m_rot.x = -ROLL_X;
	}

	//�����_�𑊑Έʒu�ɐݒ�
	//m_posR =
	//{
	//	m_posV.x + sinf(m_rot.y) * fLength,
	//	m_posV.y - 20,
	//	m_posV.z + cosf(m_rot.y) * fLength
	//};

	//m_posV.x = m_posR.x + sinf(m_rot.y) * -fLength;
	//m_posV.y = m_posR.y + 3.0f;
	//m_posV.z = m_posR.z + cosf(m_rot.y) * -fLength;

#if _DEBUG

	//m_posR.y = m_posV.y + 50.0f;

#endif

	m_posR.x = m_posV.x + sinf(m_rot.y) * cosf(m_rot.x) * fLength;
	m_posR.y = m_posV.y + sinf(m_rot.x) * fLength;
	m_posR.z = m_posV.z + cosf(m_rot.y) * cosf(m_rot.x) * fLength;

	SetPosV(m_posV);  //���_�̐ݒ�
	SetPosR(m_posR);  //�����_�̐ݒ�
	SetRotation(m_rot);  //�����̐ݒ�

	//-------------------------------------------------------
	//�J�����̃f�o�b�N�\��
	//-------------------------------------------------------
	CManager::GetInstance()->GetDebugProc()->Print("�J�����̎��_ [%f, %f, %f]\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetInstance()->GetDebugProc()->Print("�J�����̒����_ [%f, %f, %f]\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetInstance()->GetDebugProc()->Print("�J�����̌��� [%f, %f, %f]\n", m_rot.x, m_rot.y, m_rot.z);
}
//=======================================================
//�J�����̐ݒ菈��
//=======================================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬(�������e)
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		20000.0f);

	//�v���W�F�N�V�����}�g���b�N�X��ݒ�(���s���e)
	//D3DXMatrixOrthoLH(&mtxProjection,
	//				  (float)SCREEN_WIDTH,
	//				  (float)SCREEN_HEIGHT,
	//				  1.0f,
	//				  1000.0f);

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
					   &m_posV,
					   &m_posR,
					   &m_vecU);

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=======================================================
//�J�����̒Ǐ]����
//=======================================================
void CCamera::MoveCamera(CPlayer3D *pPlayer)
{
	//pPlayer��NULL����Ȃ�������
	if (pPlayer != NULL)
	{
		CObject::TYPE type;  //���
	
		//��ނ��擾
		type = pPlayer->GetType();
	
		//��ނ��v���C���[�̏ꍇ
		if (type == CObject::TYPE_PLAYER)
		{
			D3DXVECTOR3 rot = m_apObject->GetRot();  //����
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //�v���C���[�̈ʒu�̎擾
			D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //�v���C���[�̈ړ��ʂ̎擾
			D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //�v���C���[�̌����̎擾
	
			///////////////////////////////////////////
			//���_
			///////////////////////////////////////////
			m_apObject->m_posV.x = posPlayer.x;
			m_apObject->m_posV.y = posPlayer.y + 150.0f;
			m_apObject->m_posV.z = posPlayer.z;

#if _DEBUG

			//m_apObject->m_posV.y = posPlayer.y + 200.0f;
			//m_apObject->m_posV.z = posPlayer.z - 300.0f;

#endif

			//�����_�̖ڕW�ʒu���Z�o
			m_apObject->m_posRDest = D3DXVECTOR3
			(
				posPlayer.x - sinf(rotPlayer.y),
				posPlayer.y + sinf(rotPlayer.x),
				posPlayer.z - cosf(rotPlayer.y)
			);
			
			//�����_��␳
			D3DXVECTOR3 RDeff = D3DXVECTOR3
			(
				m_apObject->m_posRDest.x - m_apObject->m_posR.x,
				m_apObject->m_posRDest.y - m_apObject->m_posR.y,
				m_apObject->m_posRDest.z - m_apObject->m_posR.z
			);
	
			//�����̕t�^
			//m_apObject->m_posR.x += RDeff.x * 0.05f;
			//m_apObject->m_posR.z += RDeff.z * 0.05f;

			//���_�����_�Ԃ̋��������߂�
			float fLength_X = sqrtf((m_apObject->m_posR.x * m_apObject->m_posR.x) + (m_apObject->m_posV.x *m_apObject->m_posV.x));
			float fLength_Y = sqrtf((m_apObject->m_posR.y * m_apObject->m_posR.y) + (m_apObject->m_posV.y *m_apObject->m_posV.y));
			float fLength_Z = sqrtf((m_apObject->m_posR.z * m_apObject->m_posR.z) + (m_apObject->m_posV.z * m_apObject->m_posV.z));
	
			//���_�̖ڕW�ʒu���Z�o
			m_apObject->m_posVDest = D3DXVECTOR3
			(
				movePlayer.x - sinf(rotPlayer.x * fLength_X),
				movePlayer.y - cosf(rotPlayer.y * fLength_Y),
				movePlayer.z - cosf(rotPlayer.z * fLength_Z)
			);
	
			//���_��␳
			D3DXVECTOR3 VDeff = D3DXVECTOR3
			(
				m_apObject->m_posVDest.x - m_apObject->m_posV.x,
				m_apObject->m_posVDest.y - m_apObject->m_posV.y,
				m_apObject->m_posVDest.z - m_apObject->m_posV.z
			);
	
			//�����̕t�^
			//m_apObject->m_posV += VDeff * 0.01f;

			//�v���C���[�̌������J�����Ɠ����ɂ���
			rotPlayer.y = rot.y + D3DX_PI;
			rotPlayer.x = rot.x - D3DX_PI;

			pPlayer->SetRotation(rotPlayer);
		}
	}
}
//=======================================================
//�v���C���[���S���J�����̌����̏���
//=======================================================
void CCamera::PlayerTriggerCamera(CPlayer3D *pPlayer)
{
	//pPlayer��NULL����Ȃ�������
	if (pPlayer != NULL)
	{
		CObject::TYPE type;  //���

		//��ނ��擾
		type = pPlayer->GetType();

		//��ނ��v���C���[�̏ꍇ
		if (type == CObject::TYPE_PLAYER)
		{
			D3DXVECTOR3 rot = m_apObject->GetRot();  //����
			int PlaRes = pPlayer->GetStateRes();  //�v���C���[�̃��X�|�[����Ԏ擾

			//�v���C���[�̃��X�|�[����Ԃ��ҋ@�̂Ƃ�
			if (pPlayer->GetStateRes() == pPlayer->STATERES_RESPAWN)
			{
				rot.y = 0.0f;  //�J�����̌���������������
			}

			//�J�����̌����̐ݒ�
			m_apObject->SetRotation(rot);
		}
	}
}
//=======================================================
//�v���C���[���Ǒ��肵�Ă���Ƃ��̏���
//=======================================================
void CCamera::PlayerWallRunCamera(CPlayer3D *pPlayer)
{
	//pPlayer��NULL����Ȃ�������
	if (pPlayer != NULL)
	{
		CObject::TYPE type;  //���

		//��ނ��擾
		type = pPlayer->GetType();

		//��ނ��v���C���[�̏ꍇ
		if (type == CObject::TYPE_PLAYER)
		{
			D3DXVECTOR3 rot = m_apObject->GetRot();  //����
			int PlaJamp = pPlayer->GetJamp();  //�v���C���[�̃W�����v��Ԏ擾

			////�v���C���[�̕Ǒ����Ԃ��E����Ƃ�
			//if (PlaJamp == pPlayer->PLAYERJUMP_WALLRUN_R)
			//{
			//	rot.z = 1.2f;  //�J�����̌���������������
			//}

			////�v���C���[�̕Ǒ����Ԃ�������Ƃ�
			//if (PlaJamp == pPlayer->PLAYERJUMP_WALLRUN_L)
			//{
			//	rot.x = -1.2f;  //�J�����̌���������������
			//}

			//�J�����̌����̐ݒ�
			m_apObject->SetRotation(rot);
		}
	}
}
//-------------------------------------------------------
//���_�̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetPosV(const D3DXVECTOR3 posV)
{
	m_posV = posV;
}
//-------------------------------------------------------
//�����_�̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetPosR(const D3DXVECTOR3 posR)
{
	m_posR = posR;
}
//-------------------------------------------------------
//������x�N�g���̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetVecU(const D3DXVECTOR3 vecU)
{
	m_vecU = vecU;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CCamera::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}