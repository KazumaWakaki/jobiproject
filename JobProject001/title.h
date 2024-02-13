//=============================================================================
//
// [title.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "manager.h"

//�^�C�g���N���X
class CTitle : public CScene
{
public:
	//�|�[�Y���j���[
	typedef enum
	{
		TITLE_START = 0,   //�X�^�[�g
		TITLE_EXIT,        //��߂�
		TITLE_MAX
	}TITLE_SELECT;

	CTitle();   //�R���X�g���N�^
	~CTitle();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��

private:
	int m_TitleSelect;                                          //�^�C�g���Z���N�g
	int m_TitleCounter;                                         //�Q�[�����̓_���^�C�~���O
	//int m_typetex;                                              //�e�N�X�`���^�C�v
	//int m_nIdxTexture;											//�e�N�X�`�����蓖��
};

#endif