//=======================================================
//
// ���U���g����
// Author ��؈�^
//
//=======================================================
#include "result.h"
#include "object2D.h"

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CResult::CResult()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CResult::~CResult()
{

}
//-------------------------------------------------------
//���U���g��ʂ̏���������
//-------------------------------------------------------
HRESULT CResult::Init(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	m_RetryMenu = RETRY_MENU_QUIT;   //�|�[�Y���j���[

	//�I�u�W�F�N�g2D�̐�������
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_RESULTCLEAR);

	//�I�u�W�F�N�g2D�̐�������
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_RESULTEND);

	//BGM�̍Đ�
	pSound->PlaySound(SOUND_LABEL_BGM_RESULT);

	return S_OK;
}
//-------------------------------------------------------
//���U���g�̏I������
//-------------------------------------------------------
void CResult::Uninit(void)
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
//���U���g�̍X�V����
//-------------------------------------------------------
void CResult::Update(void)
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

	//D���������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_RetryMenu = (m_RetryMenu + 1) % 2;

		//�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_SELECT);
	}

	//A���������Ƃ�
	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_RetryMenu = (m_RetryMenu + 1) % 2;

		//�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_SELECT);
	}

	if (m_RetryMenu == RETRY_MENU_QUIT)
	{
		//���_�J���[�̐ݒ�
		//pVtx[m_RetryMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//pVtx[RETRY_MENU_RETRY * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_RETRY * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_RETRY * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_RETRY * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	if (m_RetryMenu == RETRY_MENU_RETRY)
	{
		//���_�J���[�̐ݒ�
		//pVtx[m_RetryMenu * 4 + 4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		//pVtx[m_RetryMenu * 4 + 7].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//pVtx[RETRY_MENU_QUIT * 4 + 4].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_QUIT * 4 + 5].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_QUIT * 4 + 6].col = D3DCOLOR_RGBA(100, 100, 100, 255);
		//pVtx[RETRY_MENU_QUIT * 4 + 7].col = D3DCOLOR_RGBA(100, 100, 100, 255);
	}

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true  //ENTER�L�[�������ꂽ
	//||  pInputKeyboard->GetTrigger(DIK_SPACE) == true)  //SPACE�L�[�������ꂽ
	//{
	//	//����L�[(ENTER�L�[)�������ꂽ
	//	switch (m_RetryMenu)
	//	{
	//	case RETRY_MENU_QUIT:    //�^�C�g���ɍs��

	//		//���[�h�ݒ�(�Q�[���Ɉڍs)
	//		CManager::SetMode(MODE_GAME);

	//		//InitCamera();

	//		//TITLESetCamera(600.0f, 500.0f);

	//		//�T�E���h�̍Đ�
	//		//PlaySound(SOUND_LABEL_SE_NEXT);

	//		break;

	//	case RETRY_MENU_RETRY:   //�Q�[������蒼��

	//		//���[�h�ݒ�(�^�C�g����ʂɈڍs)
	//		CManager::SetMode(MODE_TITLE);

	//		////�J�����̏��������� 
	//		//InitCamera();
	//		// 
	//		//TITLESetCamera(70.0f, 200.0f);

	//		//�T�E���h�̍Đ�
	//		//PlaySound(SOUND_LABEL_SE_NEXT);

	//		break;
	//	}
	//}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true  //ENTER�L�[�������ꂽ
	||  pInputKeyboard->GetTrigger(DIK_SPACE) == true   //SPACE�L�[�������ꂽ 
	||  pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))  //A�{�^���������ꂽ��)
	{
		//���[�h�ݒ�(�^�C�g���Ɉڍs)
		CManager::SetMode(MODE_TITLE);
		//CManager::GetFade()->Set(CScene::MODE_TITLE);

		//BreakShadow(pPlayer->nldxShadow); //�g�p���Ă��Ȃ���Ԃɂ���

		//SE�̍Đ�
		pSound->PlaySound(SOUND_LABEL_SE_DECISION);
	}
}
//-------------------------------------------------------
//���U���g�̕`�揈��
//-------------------------------------------------------
void CResult::Draw(void)
{
	//�V�[���̕`�揈��
	CScene::Draw();
}