//=============================================================================
//
// [explosion.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _EXPLOSION_H_  //���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "billboard.h"

//�����N���X
class CExplosion : public CBillboard
{
public:
	CExplosion();   //�R���X�g���N�^
	~CExplosion();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);                          //����������
	void Uninit(void);	                         //�I������
	void Update(void);	                         //�X�V����
	void Draw(void);	                         //�`�揈��
	static CExplosion *Create(D3DXVECTOR3 pos);  //��������

	//�����o�֐�
	void Anim(void);

private:
	int m_nIdxTexture;  //�e�N�X�`��
	int m_nCounterAnim;	//�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;	//�A�j���[�V�����p�^�[��No.
};

#endif