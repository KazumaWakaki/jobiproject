//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author ��� ��^
//
//=============================================================================
#include "effectbeam.h"
#include "manager.h"

//�}�N����`
#define EXPLOSIONAMIME (5)  //�A�j���[�V�������x
#define EXPLOSIONPATTERNAMIME (8)  //�A�j���[�V�����p�^�[����
#define TEXSIZE_X	(20.0f)  //�e�N�X�`���̃T�C�YX
#define TEXSIZE_Y	(20.0f)  //�e�N�X�`���̃T�C�YY
#define TEXSIZE_Z	(20.0f)  //�e�N�X�`���̃T�C�YZ
#define LIFE	 (3)  //����

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CEffectBeam::CEffectBeam()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu�̏�����
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�T�C�Y�̏�����
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CEffectBeam::~CEffectBeam()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CEffectBeam::Init()
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//���f����錾
	m_nIdxTexture[EFFECTTYPE_BEAM] = pTexture->Regist("data\\texture\\Beam001.jpg");  //�r�[��
	m_nIdxTexture[EFFECTTYPE_BLINKING] = pTexture->Regist("data\\texture\\blinking.png");  //�_��

	//�T�C�Y������
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�I�u�W�F�N�g�r���{�[�h�̏���������
	CObject3D::Init();

	//��ނ̐ݒ�
	SetType(TYPE_EFFECT);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CEffectBeam::Uninit()
{
	//�I�u�W�F�N�g�r���{�[�h�̏I������
	CObject3D::Uninit();
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CEffectBeam::Update()
{
	D3DXVECTOR3 pos = GetPosition();  //�ʒu�擾
	D3DXVECTOR3 move = GetMove();  //�ړ��ʎ擾

	//�ʒu�̍X�V
	pos += move;

	//�ʒu�̐ݒ�
	SetPosition(pos);

	CObject3D::SetVtxEffect();

	m_nLife++;

	//�G�t�F�N�g��������܂ł̃J�E���g
	if (m_nLife >= LIFE)
	{
		//�폜����
		Uninit();

		m_nLife = 0;  //0�ɖ߂�
	}
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CEffectBeam::Draw()
{
	//�I�u�W�F�N�g�r���{�[�h�̕`�揈��
	CObject3D::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CEffectBeam *CEffectBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex)
{
	CEffectBeam *pEffectBeam;

	//�G�t�F�N�g�̐���
	pEffectBeam = new CEffectBeam;

	//NULL����Ȃ�������
	if (pEffectBeam != NULL)
	{
		//����������
		pEffectBeam->Init();

		//�ʒu�̐ݒ�
		pEffectBeam->SetPosition(pos);

		//�ړ��ʂ̐ݒ�
		pEffectBeam->SetMove(move);

		//�T�C�Y
		pEffectBeam->SetSize(size);

		//���_���̐���
		pEffectBeam->SetVtxEffect();

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pEffectBeam->BindTexture(pEffectBeam->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffectBeam;
}