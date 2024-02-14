//=============================================================================
//
// [effect.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _EFFECTBEAM_H_  //���̃}�N����`������ĂȂ�������
#define _EFFECTBEAM_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object3D.h"

//�}�N����`
#define EFFECTSPEED (60.0f)   //�X�s�[�h

//�G�t�F�N�g�N���X
class CEffectBeam : public CObject3D
{
public:
	//�G�t�F�N�g�̎��
	typedef enum
	{
		EFFECTTYPE_BEAM = 0,  //�r�[��
		EFFECTTYPE_BLINKING,  //�_��
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffectBeam();   //�R���X�g���N�^
	~CEffectBeam();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);  //�X�V����
	void Draw(void);	 //�`�揈��
	static CEffectBeam *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex);  //�G�t�F�N�g����

private:
	D3DXCOLOR m_col;  //�F
	int m_nLife;  //����
	int m_nIdxTexture[EFFECTTYPE_MAX];  //�e�N�X�`��
};

#endif