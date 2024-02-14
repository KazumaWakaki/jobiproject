//=============================================================================
//
// ���C�t���� [life.cpp]
// Author�F��؈�^
//
//=============================================================================
#include "manager.h"
#include "life.h"
#include "player3D.h"

//�ÓI�����o�ϐ�
CLife *CLife::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CLife::CLife()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu�̏�����
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�T�C�Y�̏�����
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CLife::~CLife()
{

}
//-------------------------------------------------------
//���C�t�̏���������
//-------------------------------------------------------
HRESULT CLife::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture[TYPE_LIFEFRAME] = pTexture->Regist("data\\texture\\life001.png");
	m_nIdxTexture[TYPE_LIFEGAUGE] = pTexture->Regist("data\\texture\\lifegauge001.png");
	m_nIdxTexture[TYPE_BOSSLIFEGAUGE] = pTexture->Regist("data\\texture\\lifegauge002.png");  //�{�X�̃��C�t�Q�[�W

	//�I�u�W�F�N�g�r���{�[�h�̏���������
	CObject2D::Init();

	//��ނ̐ݒ�
	CObject::SetType(TYPE_LIFE);

	m_nLife = LIFE_400;

	return (S_OK);
}
//-------------------------------------------------------
//���C�t�̏I������
//-------------------------------------------------------
void CLife::Uninit(void)
{
	//�I�u�W�F�N�g�r���{�[�h�̏I������
	CObject2D::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//���C�t�̍X�V����
//-------------------------------------------------------
void CLife::Update(void)
{
	int typetexLife = GetTypeTex();

	//���_���̐���
	SetVtxUI();

	CPlayer3D::LifeMove(this);  //�v���C���[�̃��C�t�Q�[�W

	//�{�X�̃��C�t�Q�[�W�������Ƃ�
	if (typetexLife == CLife::TYPE_BOSSLIFEGAUGE)
	{
		CEnemy3D::LifeGauge(this);  //���C�t�Q�[�W�X�V
	}
}
//-------------------------------------------------------
//���C�t�̕`�揈��
//-------------------------------------------------------
void CLife::Draw(void)
{
	//�I�u�W�F�N�g�r���{�[�h�̕`��(�A�j���[�V����)����
	CObject2D::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CLife *CLife::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CLife *pLife = NULL;

	//���C�t�̐���
	pLife = new CLife;

	//pLife��NULL����Ȃ�������
	if (pLife != NULL)
	{
		//���C�t�̏���������
		pLife->Init();

		//���C�t�̈ʒu�̐ݒ�
		pLife->SetPosition(pos);

		//���C�t�̃T�C�Y
		pLife->SetSize(size);

		//���C�t�̃X�P�[��
		pLife->SetScale(scale);

		//�e�N�X�`���^�C�v
		pLife->SetTypeTex(SetTypeTex);

		//���_���̐���
		pLife->SetVtxUI();

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pLife->BindTexture(pLife->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pLife;
}
//-------------------------------------------------------
//���C�t�̐ݒ菈��
//-------------------------------------------------------
void CLife::SetLife(int nLife)
{
	m_nLife = nLife;
}

