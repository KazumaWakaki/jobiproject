//=============================================================================
//
// �Q�[�W���� [gauge.cpp]
// Author�F��؈�^
//
//=============================================================================
#include "manager.h"
#include "gauge.h"

//�ÓI�����o�ϐ�
CGauge *CGauge::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CGauge::CGauge()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject == NULL)
		{
			m_apObject = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CGauge::~CGauge()
{

}
//-------------------------------------------------------
//�Q�[�W�̏���������
//-------------------------------------------------------
HRESULT CGauge::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture[TYPE_STEPFRAME] = pTexture->Regist("data\\texture\\attackgagecover001.png");
	m_nIdxTexture[TYPE_STEPGAUGE_GREEN] = pTexture->Regist("data\\texture\\attackgage001.png");
	m_nIdxTexture[TYPE_STEPGAUGE_ORANGE] = pTexture->Regist("data\\texture\\attackgage001.png");
	m_nIdxTexture[TYPE_STEPGAUGE_RED] = pTexture->Regist("data\\texture\\attackgage001.png");

	//�I�u�W�F�N�g2D�̏���������
	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_GAUGE);

	//������
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�T�C�Y
	SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�X�P�[��

	return (S_OK);
}
//-------------------------------------------------------
//�Q�[�W�̏I������
//-------------------------------------------------------
void CGauge::Uninit(void)
{
	//�I�u�W�F�N�g2D�̏I������
	CObject2D::Uninit();
}
//-------------------------------------------------------
//�Q�[�W�̍X�V����
//-------------------------------------------------------
void CGauge::Update(void)
{
	//���_���̐���
	SetVtxUI();

	CPlayer3D::StepGaugeMove(this);
}
//-------------------------------------------------------
//�Q�[�W�̕`�揈��
//-------------------------------------------------------
void CGauge::Draw(void)
{
	//�I�u�W�F�N�g2D�̕`�揈��
	CObject2D::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CGauge *CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CGauge *pGauge = NULL;

	//�Q�[�W�̐���
	pGauge = new CGauge;

	//NULL����Ȃ�������
	if (pGauge != NULL)
	{
		//����������
		pGauge->Init();

		//�ʒu�ݒ�
		pGauge->SetPosition(pos);

		//�T�C�Y�ݒ�
		pGauge->SetSize(size);

		//�X�P�[���ݒ�
		pGauge->SetScale(scale);

		//�e�N�X�`���^�C�v�ݒ�
		pGauge->SetTypeTex(SetTypeTex);

		//���_���̐���
		pGauge->SetVtxUI();

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pGauge->BindTexture(pGauge->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pGauge;
}
//-------------------------------------------------------
//�X�e�b�v�Q�[�W�̐ݒ菈��
//-------------------------------------------------------
void CGauge::SetStepGauge(D3DXVECTOR3 StepGauge)
{
	m_nStepGauge = StepGauge;
}