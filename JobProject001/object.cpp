//=============================================================================
//
// �I�u�W�F�N�g�Ǘ� [object.cpp]
// Author ��� ��^
//
//=============================================================================
#include "object.h"
#include "manager.h"

//�ÓI�����o�ϐ�
CObject *CObject::m_apObject[PRIORITY][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CObject::CObject(int nPriority)
{
	//MAX_OBJECT����
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nPriority][nCntObject] == NULL)
		{
			m_apObject[nPriority][nCntObject] = this;
			m_nPriority = nPriority;
			m_nlD = nCntObject;  //�������g��ID��ۑ�
			m_nNumAll++;  //�������J�E���g�A�b�v

			break;
		}
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CObject::~CObject()
{

}
//-------------------------------------------------------
//�S�ẴI�u�W�F�N�g�̔j��
//-------------------------------------------------------
void CObject::ReleaseAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT����
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				//�I������
				m_apObject[nCntPriority][nCntObject]->Uninit();
			}
		}
	}
}
//-------------------------------------------------------
//�S�ẴI�u�W�F�N�g�̍X�V����
//-------------------------------------------------------
void CObject::UpdateAll(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT����
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				//�X�V����
				m_apObject[nCntPriority][nCntObject]->Update();
			}
		}
	}
}
//-------------------------------------------------------
//�S�ẴI�u�W�F�N�g�̕`�揈��
//-------------------------------------------------------
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	//PRIORITY����
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT����
		for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
		{
			if (m_apObject[nCntPriority][nCntObject] != NULL)
			{
				//�`�揈��
				m_apObject[nCntPriority][nCntObject]->Draw();
			}
		}
	}
}
//-------------------------------------------------------
//�I�u�W�F�N�g�̔j��
//-------------------------------------------------------
void CObject::Release(void)
{
	int nNum = m_nlD;                //�ԍ��ێ�
	int nNumPriority = m_nPriority;  //�ԍ��ێ�

	if (m_apObject[nNumPriority][nNum]!= NULL)
	{
		delete m_apObject[nNumPriority][nNum];  //�������̊J��

		m_apObject[nNumPriority][nNum] = NULL;  //�g�p���Ă��Ȃ���Ԃɂ���

		m_nNumAll--;  //�������J�E���g�_�E��
	}	
}
//-------------------------------------------------------
//�^�C�v�ݒ�
//-------------------------------------------------------
void CObject::SetType(TYPE type)
{
	m_type = type;
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CObject::SetState(STATE state, int nCounterState)
{
	m_state = state;
	m_nCounterState = nCounterState;
}
//-------------------------------------------------------
//��ԊǗ��ݒ�
//-------------------------------------------------------
void CObject::UpdateState(void)
{
	switch (m_state)
	{
	case STATE_NORMAL:
		break;

	case STATE_DAMAGE:

		m_nCounterState--;

		if (m_nCounterState <= 0)
		{
			m_state = STATE_NORMAL;

			break;
		}

	case STATE_DEATH:
		break;
	}
}
//-------------------------------------------------------
//�I�u�W�F�N�g�擾
//-------------------------------------------------------
CObject *CObject::GetObject(int nPriority, int nIdx)
{
	return m_apObject[nPriority][nIdx];
}