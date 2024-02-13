//=============================================================================
//
// [texture.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _TEXTURE_H_  //���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_TEXTURE  (256)  //�e�N�X�`���̍ő吔

//�e�N�X�`���N���X
class CTexture
{
public:
	CTexture();   //�R���X�g���N�^
	~CTexture();  //�f�X�g���N�^

	//�e�N�X�`�������֐�
	static HRESULT Load(void);  //�e�N�X�`���̐���(�ǂݍ���)
	static void Unload(void);   //�e�N�X�`���̔j��

	//�����o�֐�
	int Regist(const char *pFilename);        //�e�N�X�`����ݒ肷��
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);  //�A�h���X��Ԃ�

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];  //�e�N�X�`���z��
	static char m_FileName[MAX_TEXTURE][512];            //�e�N�X�`���̖��O�m�F�p
	static int m_nNumAll;                                //����
};

#endif