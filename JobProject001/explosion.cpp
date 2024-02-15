//=============================================================================
//
// �������� [explosion.cpp]
// Author ��� ��^
//
//=============================================================================
#include "explosion.h"
#include "manager.h"

//�}�N����`
#define ANIMTIMER (4)  //�A�j���[�V�������x
#define MAX_ANIMPATTERN (8)  //�A�j���[�V�����̍ő�p�^�[����
#define MAX_HEIFGHTPATTERN (8)  //�A�j���[�V�����̍ő剡�p�^�[����

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CExplosion::CExplosion()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu�̏�����
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�T�C�Y�̏�����
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CExplosion::~CExplosion()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CExplosion::Init()
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture = pTexture->Regist("data\\texture\\explosion000.png");

	//�I�u�W�F�N�g�r���{�[�h�̏���������
	CBillboard::Init();

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CExplosion::Uninit()
{
	//�I�u�W�F�N�g�r���{�[�h�̏I������
	CBillboard::Uninit();
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CExplosion::Update()
{
	//���_���ݒ�
	SetVtx(m_nPatternAnim, MAX_HEIFGHTPATTERN, MAX_ANIMPATTERN / MAX_HEIFGHTPATTERN);

	//�A�j���[�V��������
	Anim();
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CExplosion::Draw()
{
	//�I�u�W�F�N�g�r���{�[�h�̕`��(�A�j���[�V����)����
	CBillboard::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CExplosion *CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CExplosion *pExplosion = NULL;

	//�����̐���
	pExplosion = new CExplosion;

	if (pExplosion != NULL)
	{
		//����������
		pExplosion->Init();

		//��ނ̐ݒ�
		pExplosion->SetType(TYPE_EXPLOSION);

		//�����̈ʒu�̐ݒ�
		pExplosion->SetPosition(pos);

		//�����̃T�C�Y�̐ݒ�
		pExplosion->SetSize(size);

		//�e�N�X�`���ݒ�
		pExplosion->SetVtx(pExplosion->m_nPatternAnim, MAX_HEIFGHTPATTERN, MAX_ANIMPATTERN / MAX_HEIFGHTPATTERN);

		//�e�N�X�`���̊��蓖��
		pExplosion->BindTexture(pExplosion->m_nIdxTexture);
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pExplosion;
}
//-------------------------------------------------------
//�A�j���[�V��������
//-------------------------------------------------------
void CExplosion::Anim(void)
{
	m_nCounterAnim++;  //�J�E���^�[�����Z

	//�A�j���[�V�����^�C�}�[�̒l�𒴂����ꍇ
	if (m_nCounterAnim % ANIMTIMER == 0)
	{
		m_nCounterAnim = 0;

		m_nPatternAnim++;  //�p�^�[��No.���X�V

		//�Ō�܂ŃA�j���[�V���������ꍇ
		if (m_nPatternAnim >= MAX_ANIMPATTERN)
		{
			Uninit();
		}
	}
}
