//=======================================================
//
// �^�C�g������
// Author ��؈�^
//
//=======================================================
#include "title.h"
#include "object2D.h"

//�}�N����`
#define MAX_TEX	 (2)   //�g�p����e�N�X�`����

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CTitle::CTitle()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CTitle::~CTitle()
{

}
//-------------------------------------------------------
//�^�C�g���̏���������
//-------------------------------------------------------
HRESULT CTitle::Init(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	m_TitleSelect = TITLE_START;   //�^�C�g���Z���N�g

	//�I�u�W�F�N�g2D�̐�������
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_TITLE);

	//BGM�̍Đ�
	pSound->PlaySound(SOUND_LABEL_BGM_TITLE);

	return S_OK;
}
//-------------------------------------------------------
//�^�C�g���̏I������
//-------------------------------------------------------
void CTitle::Uninit(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�̒�~
	pSound->StopSound();

	//�V�[���̏I������
	CScene::Uninit();
}
//-------------------------------------------------------
//�^�C�g����ʂ̍X�V����
//-------------------------------------------------------
void CTitle::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInstance()->GetInputPad();

	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	if (m_TitleCounter <= 50)
	{
		//���_�J���[�̐ݒ� 

	}

	else
	{
		//���_�J���[�̐ݒ�

	}

	if (m_TitleCounter >= 110)
	{
		m_TitleCounter = 0;
	}

	m_TitleCounter++;

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		//���[�h�ݒ�(�`���[�g���A���Ɉڍs)
		CManager::SetMode(MODE_GAME);
		//CManager::GetFade()->Set(CScene::MODE_TUTORIAL);

		CScene::Update();

		//SE�̍Đ�
		pSound->PlaySound(SOUND_LABEL_SE_DECISION);
	}
}
//-------------------------------------------------------
//�^�C�g����ʂ̕`�揈��
//-------------------------------------------------------
void CTitle::Draw(void)
{
	//�V�[���̕`�揈��
	CScene::Draw();
}