//=============================================================================
//
// [billboard.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _BILLBOARD_H_  //���̃}�N����`������ĂȂ�������
#define _BILLBOARD_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�I�u�W�F�N�g3D�N���X
class CBillboard : public CObject
{
public:
	CBillboard();   //�R���X�g���N�^
	~CBillboard();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);  //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);  //�`�揈��
	static CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);  //��������
	void BindTexture(int nIdx);  //�e�N�X�`�����蓖��
	void SetVtx(void);  //���_���̐���
	void SetVtxBullet(void);  //���_���̐���(�e)
	void SetVtxLife(void);  //���_���̐���(���C�t)
	void SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight);  //���_���̐���(�A�j���[�V����)

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos);        //�ʒu�̐ݒ菈��
	void SetPositionOld(D3DXVECTOR3 posOld);  //�ʒu(�ߋ�)�̐ݒ菈��
	void SetMove(D3DXVECTOR3 move);           //�ړ��ʂ̐ݒ菈��
	void SetRotation(D3DXVECTOR3 rot);        //�����̐ݒ菈��
	void SetScale(D3DXVECTOR3 scale);         //�g�嗦�̐ݒ菈��
	void SetSize(D3DXVECTOR3 size);           //�T�C�Y�̐ݒ菈��
	void SetTypeTex(int Type);                //�e�N�X�`���^�C�v�̐ݒ菈��

	//�擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; };  //�ʒu�̎擾
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //�ߋ��̈ʒu�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; };  //�ړ��ʂ̎擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; };  //�����̎擾
	D3DXVECTOR3 GetScale(void) { return m_scale; };  //�g�嗦�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; };  //�T�C�Y�̎擾
	int GetTypeTex(void) { return m_typetex; };  //�e�N�X�`���^�C�v�̎擾

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;  //���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;  //���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_posOld;  //�ߋ��̈ʒu
	D3DXVECTOR3 m_move;  //�ړ���
	D3DXVECTOR3 m_rot;  //��]��
	D3DXVECTOR3 m_scale;  //�g�嗦
	D3DXVECTOR3 m_size;  //�T�C�Y��
	int m_typetex;  //�e�N�X�`���^�C�v
	int m_nIdxTexture;  //�e�N�X�`�����蓖��
};

#endif