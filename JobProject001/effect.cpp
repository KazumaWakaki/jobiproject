//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author ��� ��^
//
//=============================================================================
#include "effect.h"
#include "manager.h"

//�}�N����`
#define EXPLOSIONAMIME (5)         //�A�j���[�V�������x
#define EXPLOSIONPATTERNAMIME (8)  //�A�j���[�V�����p�^�[����
#define TEXSIZE_X	(20.0f)        //�e�N�X�`���̃T�C�YX
#define TEXSIZE_Y	(20.0f)        //�e�N�X�`���̃T�C�YY
#define TEXSIZE_Z	(20.0f)        //�e�N�X�`���̃T�C�YZ
#define LIFE	    (3)           //����

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CEffect::CEffect()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //�ʒu�̏�����
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //�T�C�Y�̏�����
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CEffect::~CEffect()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CEffect::Init()
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//���f����錾
	m_nIdxTexture[EFFECTTYPE_BEAM] = pTexture->Regist("data\\texture\\Beam001.jpg");  //�r�[��
	m_nIdxTexture[EFFECTTYPE_BLINKING] = pTexture->Regist("data\\texture\\Beam001.png");  //�_��

	//�T�C�Y������
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�I�u�W�F�N�g�r���{�[�h�̏���������
	CBillboard::Init();

	//��ނ̐ݒ�
	SetType(TYPE_EFFECT);

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CEffect::Uninit()
{
	//�I�u�W�F�N�g�r���{�[�h�̏I������
	CBillboard::Uninit();
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CEffect::Update()
{
	D3DXVECTOR3 pos = GetPosition();  //�ʒu�擾
	D3DXVECTOR3 move = GetMove();  //�ړ��ʎ擾

	//�ʒu�̍X�V
	pos += move;

	//�ʒu�̐ݒ�
	SetPosition(pos);

	CBillboard::SetVtxBullet();

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
void CEffect::Draw()
{
	//�I�u�W�F�N�g�r���{�[�h�̕`�揈��
	CBillboard::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex)
{
	CEffect *pEffect;

	//�G�t�F�N�g�̐���
	pEffect = new CEffect;

	//NULL����Ȃ�������
	if (pEffect != NULL)
	{
		//����������
		pEffect->Init();

		//�ʒu�̐ݒ�
		pEffect->SetPosition(pos);

		//�ړ��ʂ̐ݒ�
		pEffect->SetMove(move);

		//�T�C�Y
		pEffect->SetSize(size);

		//���_���̐���
		pEffect->SetVtxBullet();

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ���f���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pEffect->BindTexture(pEffect->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pEffect;
}