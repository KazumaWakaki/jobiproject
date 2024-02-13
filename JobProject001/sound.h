//=============================================================================
//
// [sound.h]
// Author ��؈�^
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
//�T�E���h�ꗗ
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM_GAME = 0,  //�Q�[��BGM
	SOUND_LABEL_BGM_TITLE,  //�^�C�g��BGM
	SOUND_LABEL_BGM_RESULT,  //���U���gBGM
	SOUND_LABEL_SE_FIRING,  //����SE
	SOUND_LABEL_SE_JAMP,  //�W�����vSE
	SOUND_LABEL_SE_DAMAGE,  //�_���[�WSE
	SOUND_LABEL_SE_DEATH,  //���SSE
	SOUND_LABEL_SE_EXPLOSION,   //����SE
	SOUND_LABEL_SE_CHECKPOINT,  //�`�F�b�N�|�C���g
	SOUND_LABEL_SE_DECISION,  //����SE
	SOUND_LABEL_SE_MELEE,  //�ߐڍU��SE
	SOUND_LABEL_SE_RUSHATTACK,  //�ːi�U��SE
	SOUND_LABEL_SE_LONGATTACK,  //�ːi�U��SE
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
//�T�E���h���̍\���̒�`
//*****************************************************************************
typedef struct
{
	char *pFilename;	//�t�@�C����
	int nCntLoop;		//���[�v�J�E���g
} SOUNDINFO;

//*****************************************************************************
//�v���g�^�C�v�錾
//*****************************************************************************

//�X�R�A�N���X
class CSound
{
public:
	CSound();   //�R���X�g���N�^
	~CSound();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:
	IXAudio2 *g_pXAudio2 = NULL;								 //XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			 //�}�X�^�[�{�C�X
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	 //�\�[�X�{�C�X
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					 //�I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					 //�I�[�f�B�I�f�[�^�T�C�Y
	static SOUNDINFO g_aSoundInfo[SOUND_LABEL_MAX];

};
#endif