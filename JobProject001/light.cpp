//=============================================================================
//
// ���C�g���� [light.cpp]
// Author ��� ��^
//
//=============================================================================
#include "light.h"
#include "input.h"
#include "manager.h"
#include "debugproc.h"

//�}�N����`
#define ROLL_SPEED  (0.03f)  //���X�s�[�h

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CLight::CLight()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CLight::~CLight()
{

}
//=======================================================
//���C�g�̏���������
//=======================================================
HRESULT CLight::Init(void)
{
	//�ϐ�������
	m_nCurrentLight = 0;

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	//���C�g�̎�ސݒ�
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕����ݒ�
	vecDir = D3DXVECTOR3(-0.2f, - 0.8f, 0.8f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//�x�N�g�����K��
	m_aLight[0].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(0, &m_aLight[0]);

	//���C�g�L����
	pDevice->LightEnable(0, TRUE);

	/////////////////////////////////
	//���C�g�Q�̐ݒ�
	/////////////////////////////////
	//���C�g�̎�ސݒ�
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕����ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, -1.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);  //�x�N�g�����K��
	m_aLight[1].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(1, &m_aLight[1]);

	//���C�g�L����
	pDevice->LightEnable(1, TRUE);

	/////////////////////////////////
	//���C�g�R�̐ݒ�
	/////////////////////////////////
	//���C�g�̎�ސݒ�
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U���̐ݒ�
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕����ݒ�
	vecDir = D3DXVECTOR3(-0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);  //�x�N�g�����K��
	m_aLight[2].Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(2, &m_aLight[2]);

	//���C�g�L����
	pDevice->LightEnable(2, TRUE);

	return (S_OK);
}
//=======================================================
//���C�g�̏I������
//=======================================================
void CLight::Uninit(void)
{

}
//=======================================================
//���C�g�̍X�V����
//=======================================================
void CLight::Update(void)
{
	//�f�o�C�X�|�C���^�ݒ�
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXVECTOR3 vecDir;

	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#if _DEBUG

	/////////////////////////////////
	//���C�g�ړ�
	/////////////////////////////////
	//if (pInputKeyboard->GetPress(DIK_J) == true)
	//{//���ړ�
	//	m_aLight[m_nCurrentLight].Direction.x -= ROLL_SPEED;
	//}
	//if (pInputKeyboard->GetPress(DIK_L) == true)
	//{//�E�ړ�
	//	m_aLight[m_nCurrentLight].Direction.x += ROLL_SPEED;
	//}

	//if (pInputKeyboard->GetPress(DIK_T) == true)
	//{//���ړ�
	//	m_aLight[m_nCurrentLight].Direction.z += ROLL_SPEED;
	//}
	//if (pInputKeyboard->GetPress(DIK_B) == true)
	//{//��O�ړ�
	//	m_aLight[m_nCurrentLight].Direction.z -= ROLL_SPEED;
	//}

	//if (pInputKeyboard->GetPress(DIK_U) == true)
	//{//��ړ�
	//	m_aLight[m_nCurrentLight].Direction.y += ROLL_SPEED;
	//}
	//if (pInputKeyboard->GetPress(DIK_M) == true)
	//{//���ړ�
	//	m_aLight[m_nCurrentLight].Direction.y -= ROLL_SPEED;
	//}

	///////////////////////////////////
	////���C�g�؂�ւ�
	///////////////////////////////////
	//if (pInputKeyboard->GetTrigger(DIK_O) == true)
	//{//���C�g�؂�ւ�
	//	m_nCurrentLight = (m_nCurrentLight + 1) % MAX_LIGHT;
	//}

#endif

	//MAX_LIGHT����
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//�x�N�g�����K��
		D3DXVec3Normalize
		(
			&(D3DXVECTOR3)m_aLight[nCntLight].Direction,
			&(D3DXVECTOR3)m_aLight[nCntLight].Direction
		);

		//���C�g�ݒ�
		pDevice->SetLight(nCntLight, &m_aLight[nCntLight]);
	}

	//-------------------------------------------------------
	//���C�g�̃f�o�b�N�\��
	//-------------------------------------------------------
	//CManager::GetDebugProc()->Print("���C�g1�ʒu [%f, %f, %f]\n", m_aLight[0].Direction.x, m_aLight[0].Direction.y, m_aLight[0].Direction.z);
	//CManager::GetDebugProc()->Print("���C�g2�ʒu [%f, %f, %f]\n", m_aLight[1].Direction.x, m_aLight[1].Direction.y, m_aLight[1].Direction.z);
	//CManager::GetDebugProc()->Print("���C�g3�ʒu [%f, %f, %f]\n", m_aLight[2].Direction.x, m_aLight[2].Direction.y, m_aLight[2].Direction.z);
}