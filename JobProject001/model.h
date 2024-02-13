//=============================================================================
//
// [model.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _MODEL_H_  //���̃}�N����`������ĂȂ�������
#define _MODEL_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_MODEL  (128)  //���f���̍ő吔

//���f���N���X
class CModel
{
public:
	//���f���\���̂̒�`
	typedef struct
	{
		LPD3DXMESH m_pMesh;       //���b�V��(���_���)�ւ̃|�C���^
		LPD3DXBUFFER m_pBuffMat;  //�}�e���A���ւ̃|�C���^
		DWORD m_dwNumMat;         //�}�e���A���̐�
		int *pIndxTex;            //�e�N�X�`���ۑ��p
	}Model;

	CModel();   //�R���X�g���N�^
	~CModel();  //�f�X�g���N�^

	//���f�������֐�
	static HRESULT Load(void);  //���f���̐���(�ǂݍ���)
	static void Unload(void);   //���f���̔j��

	//�����o�֐�
	int Regist(const char *pFilename);  //���f����ݒ肷��
	Model *GetAddress(int nIdx);         //���b�V���̃A�h���X��Ԃ�

private:
	static Model m_apModel[MAX_MODEL];
	static char m_FileName[MAX_MODEL][512];  //���f���̖��O�m�F�p
	static int m_nNumAll;                    //����
};

#endif