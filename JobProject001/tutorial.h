//=============================================================================
//
// [tutorial.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "manager.h"

//�^�C�g���N���X
class CTutorial : public CScene
{
public:
	CTutorial();   //�R���X�g���N�^
	~CTutorial();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��

private:

};

#endif