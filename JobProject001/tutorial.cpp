//=======================================================
//
// �`���[�g���A������
// Author ��؈�^
//
//=======================================================
#include "tutorial.h"
#include "object2D.h"

//�}�N����`
#define MAX_TEX	 (2)   //�g�p����e�N�X�`����

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CTutorial::CTutorial()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CTutorial::~CTutorial()
{

}
//-------------------------------------------------------
//�^�C�g���̏���������
//-------------------------------------------------------
HRESULT CTutorial::Init(void)
{
	//�I�u�W�F�N�g2D�̐�������
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_TUTORIAL);

	return S_OK;
}
//-------------------------------------------------------
//�^�C�g���̏I������
//-------------------------------------------------------
void CTutorial::Uninit(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�̍Đ�
	pSound->StopSound();

	//�V�[���̏I������
	CScene::Uninit();
}
//-------------------------------------------------------
//�^�C�g����ʂ̍X�V����
//-------------------------------------------------------
void CTutorial::Update(void)
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
	{
		//���[�h�ݒ�(�Q�[���Ɉڍs)
		CManager::SetMode(MODE_GAME);

		//SE�̍Đ�
		//pSound->PlaySound(SOUND_LABEL_SE_DECISION);
	}
}
//-------------------------------------------------------
//�^�C�g����ʂ̕`�揈��
//-------------------------------------------------------
void CTutorial::Draw(void)
{
	//�V�[���̕`�揈��
	CScene::Draw();
}