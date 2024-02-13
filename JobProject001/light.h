//=============================================================================
//
// [light.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _LIGHT_H_                  //���̃}�N����`������ĂȂ�������
#define _LIGHT_H_                  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_LIGHT  (3)  //���C�g�̍ő吔

//�����_���[�N���X
class CLight
{
public:
	CLight();  //�R���X�g���N�^
	~CLight(); //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);   //�I������
	void Update(void);   //�X�V����

private:
	D3DLIGHT9 m_aLight[MAX_LIGHT];  //���C�g���
	int m_nCurrentLight;
};

#endif
