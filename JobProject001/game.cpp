//=======================================================
//
// �Q�[������ [game.cpp]
// Author ��؈�^
//
//=======================================================
#include "game.h"
#include "modelset.h"
#include "player3D.h"
#include "enemy3D.h"
#include "block3D.h"
#include "wall.h"
#include "life.h"

//�}�N����`
#define WALL_MAX  (9)  //�w�i�ǂ̐��l
#define START_TIME	(420)	//��������

//�ÓI�����o�ϐ�
CGame *CGame::m_apObject = NULL;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CGame::CGame()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	//m_pTime = NULL;
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CGame::~CGame()
{

}
//-------------------------------------------------------
//�Q�[����ʂ̏���������
//-------------------------------------------------------
HRESULT CGame::Init(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//�V�[���̏���������
	CScene::Init();

	//�J�����̎擾
	CCamera *pCamera;
	pCamera = CManager::GetInstance()->GetCamera();

	//�J�����̏�����
	pCamera->Init();

	//---------------------------------------------------------------
	//�ǂ̐���
	//---------------------------------------------------------------
	CWall::Create(D3DXVECTOR3(200.0f, 150.0f, 2000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), D3DXVECTOR3(5000.0f, 400.0f, 0.0f), CWall::TYPE_WALL001);
	CWall::Create(D3DXVECTOR3(-200.0f, 150.0f, 2000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(5000.0f, 400.0f, 0.0f), CWall::TYPE_WALL001);

	//---------------------------------------------------------------
	//�u���b�N�̔z�u
	//---------------------------------------------------------------
	//CBlock3D::Create(D3DXVECTOR3(0.0f, 10.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 0.1f), CBlock3D::BLOCK_NEON);  //�f�o�b�O�p
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, -5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 30.0f), CBlock3D::BLOCK_NEONFLOOR);  //�`���[�g���A���p�y��
	CBlock3D::Create(D3DXVECTOR3(0.0f, 60.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 4.0f, 20.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 20.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, -0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 40.0f), CBlock3D::BLOCK_NEONFLOOR);

	CBlock3D::Create(D3DXVECTOR3(300.0f, 0.0f, 2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 2.0f, 20.0f),  CBlock3D::BLOCK_NEONFLOOR);  //1�ڂ̓y��
	CBlock3D::Create(D3DXVECTOR3(600.0f, 0.0f, 1720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.1f), CBlock3D::BLOCK_NEON);  //��
	CBlock3D::Create(D3DXVECTOR3(00.0f, 0.0f, 2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.1f), CBlock3D::BLOCK_NEON);
	CBlock3D::Create(D3DXVECTOR3(500.0f, 20.0f, 4000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.0f, 2.0f, 30.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, 6500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 2.0f, 40.0f), CBlock3D::BLOCK_NEONFLOOR);  //�{�X�̓y��

	//---------------------------------------------------------------
	//���f���̐���
	//---------------------------------------------------------------
	CModelSet::Create(D3DXVECTOR3(0.0f, -100.0f, -5400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);  //�`���[�g���A���p

	CModelSet::Create(D3DXVECTOR3(0.0f, -100.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(-500.0f, -100.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(500.0f, -100.0f, 3100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(0.0f, -100.0f, 6000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);

	//---------------------------------------------------------------
	//�G3D�̐���
	//---------------------------------------------------------------
	CEnemy3D::Create(D3DXVECTOR3(0.0f, 70.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_TUTORIAL_ENE, 10000);
	CEnemy3D::Create(D3DXVECTOR3(1000.0f, 100.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(500.0f, 100.0f, 4700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(0.0f, 100.0f, 7300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_BOSS, 2000);

	//---------------------------------------------------------------
	//�v���C���[3D�̐���
	//---------------------------------------------------------------
	CPlayer3D::Create(D3DXVECTOR3(0.0f, 100.0f, -5500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//BGM�̍Đ�
	pSound->PlaySound(SOUND_LABEL_BGM_GAME);

	return (S_OK);
}
//-------------------------------------------------------
//�Q�[����ʂ̏I������
//-------------------------------------------------------
void CGame::Uninit(void)
{
	//�T�E���h�̎擾
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGM�̍Đ�
	pSound->StopSound();

	//�V�[���̏I������
	CScene::Uninit();

	if (m_apObject != NULL)
	{
		m_apObject = NULL;
	}
}
//-------------------------------------------------------
//�Q�[����ʂ̍X�V����
//-------------------------------------------------------
void CGame::Update(void)
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

//#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_R) == true)  //ENTER�L�[�������ꂽ
	{
		//���[�h�ݒ�(���U���g�Ɉڍs)
		CManager::SetMode(MODE_RESULT);
		//CManager::GetFade()->Set(CScene::MODE_RESULT);

		////�T�E���h�̍Đ�
		//PlaySound(SOUND_LABEL_SE_NEXT);
	}

//#endif

	switch (m_gameState)
	{
	case GAMESTATE_NORMAL:  //�ʏ���
		break;

	case GAMESTATE_RESET:  //���Z�b�g���

		m_nCounterGameState++;

		if (m_nCounterGameState >= 10)
		{
			m_nCounterGameState = 0;
			m_gameState = GAMESTATE_NORMAL;  //�ʏ��Ԃɐݒ�
		}

		break;

	case GAMESTATE_END:  //�I�����

		m_nCounterGameState--;

		if (m_nCounterGameState <= 0)
		{
			m_gameState = GAMESTATE_NONE;  //�������Ă��Ȃ���Ԃɐݒ�

			//���[�h�ݒ�(���U���g�Ɉڍs)
			//CManager::SetMode(MODE_RESULT);
			//CManager::GetFade()->Set(CScene::MODE_RESULT);

			////���[�h�ݒ�(���U���g��ʂɈڍs)
			//SetFade(MODE_RESULT);
		}

		break;
	}
}
//-------------------------------------------------------
//�Q�[����ʂ̕`�揈��
//-------------------------------------------------------
void CGame::Draw(void)
{
	//�V�[���̕`�揈��
	CScene::Draw();
}
//-------------------------------------------------------
//�Q�[���̏�Ԃ̐ݒ�
//-------------------------------------------------------
void CGame::SetGameState(GAMESTATE state, int nCounter)
{
	if (m_apObject != NULL)
	{
		m_apObject->m_gameState = state;
		m_apObject->m_nCounterGameState = nCounter;
	}
}
//-------------------------------------------------------
//�Q�[���̃|�[�Y��Ԃ̎擾
//-------------------------------------------------------
void CGame::SetEnablePause(bool Pause)
{
	m_bPause = Pause;
}
//-------------------------------------------------------
// �^�C�}�[�̎擾
//-------------------------------------------------------
//CTime *CGame::GetTime(void)
//{
//	return m_pTime;
//}