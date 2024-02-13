//=============================================================================
//
// [result.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "manager.h"

//�}�N����`
#define MAX_TEX	 (4)	    //�g�p����e�N�X�`����
#define RES_SCO	 (1)	    //���U���g�ɐ��l��`�悷���
#define RES_TIME (600)		//�����L���O��ʂɑJ�ڂ��鎞��

//���U���g�N���X
class CResult : public CScene
{
public:
	//�|�[�Y���j���[
	typedef enum
	{
		RETRY_MENU_QUIT = 0,   //�^�C�g���ɂ���
		RETRY_MENU_RETRY,      //�Q�[������蒼��
		RETRY_MENU_MAX
	}RETRY_MENU;

	//�\���̂��`
	typedef struct
	{
		D3DXVECTOR3 pos;  //�ʒu
		int nScore;  //�l
		int nDigit;  //��
		int nSpace;  //��
		int nWidth;  //����
		int nHeight;  //�c��
		int nTexture;  //�e�N�X�`��
	}Result;

	CResult();   //�R���X�g���N�^
	~CResult();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��

private:
	Result m_aResult[RES_SCO];	//���U���g�̏��
	int m_nResultCounter;		//�����L���O�ɑJ�ڂ���^�C�~���O�J�E���^�[
	int m_nTotalScore;			//�g�[�^���X�R�A
	int m_RetryMenu;            //���g���C���j���[
};

#endif