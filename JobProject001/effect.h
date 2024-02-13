//=============================================================================
//
// [effect.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _EFFECT_H_  //���̃}�N����`������ĂȂ�������
#define _EFFECT_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "billboard.h"

//�}�N����`
#define EFFECTSPEED (60.0f)   //�X�s�[�h

//�G�t�F�N�g�N���X
class CEffect : public CBillboard
{
public:
	//�G�t�F�N�g�̎��
	typedef enum
	{
		EFFECTTYPE_BEAM = 0,  //�r�[��
		EFFECTTYPE_BLINKING,  //�_��
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect();   //�R���X�g���N�^
	~CEffect();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);	 //�X�V����
	void Draw(void);	 //�`�揈��
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex);  //�G�t�F�N�g����

private:
	D3DXCOLOR m_col;    //�F
	int m_nLife;		//����
	int m_nIdxTexture[EFFECTTYPE_MAX];  //�e�N�X�`��
};

#endif