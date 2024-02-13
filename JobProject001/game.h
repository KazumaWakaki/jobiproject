//=============================================================================
//
//[game.h]
//Author ��� ��^
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "manager.h"

//�}�N����`
#define TIME_END	(120)	//�]�C

// �O���錾
class CScore;

//�Q�[���N���X
class CGame : public CScene
{
public:
	//�Q�[���̏��
	typedef enum
	{
		GAMESTATE_NONE = 0,    //�������Ă��Ȃ����
		GAMESTATE_NORMAL,      //�ʏ���
		GAMESTATE_RESET,       //���Z�b�g���
		GAMESTATE_END,         //�I�����
		GAMESTATE_MAX
	}GAMESTATE;

	CGame();   //�R���X�g���N�^
	~CGame();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��

	//�擾
	GAMESTATE GetGameState(void) { return m_gameState; };
	//CTime *GetTime(void);

	//�ݒ�
	static void SetGameState(GAMESTATE state, int nCounter);
	void SetEnablePause(bool Pause);

private:
	GAMESTATE m_gameState;    //�Q�[���̏��
	int m_nCounterGameState;  //��ԊǗ��J�E���^�[
	bool m_bPause;            //�|�[�Y��Ԃ�ON/OFF

	//�|�C���^
	static CGame *m_apObject;           //�I�u�W�F�N�g�N���X�̃|�C���^
	static CSound *m_pSound;			//���̃|�C���^
	//CTime *m_pTime;                     //�^�C�}�[�̃|�C���^
	static CCamera *m_pCamera;			//�J�����̃|�C���^
	static CLight *m_pLight;			//���C�g�̃|�C���^
	static CDebugProc *m_pDebugProc;	//�f�o�b�O�\���̃|�C���^
	static CTexture *m_pTexture;		//�e�N�X�`���̃|�C���^
	static CModel *m_pModel;		    //���f���̃|�C���^
};

#endif