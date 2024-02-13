//=============================================================================
//
//[object3D.h]
//Author ��� ��^
//
//=============================================================================
#ifndef _OBJECT3D_H_  //���̃}�N����`������ĂȂ�������
#define _OBJECT3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�}�N����`
#define COUNTAMIME (8)       //�A�j���[�V�������x
#define PATTERNAMIME (8)     //�A�j���[�V�����p�^�[����
#define PATTERNTEX (0.125f)  //�e�N�X�`���̃p�^�[����

//�I�u�W�F�N�g3D�N���X
class CObject3D : public CObject
{
public:
	CObject3D(int nPriority = 3);
	~CObject3D();  //�f�X�g���N�^

	//�����o�֐�
	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size);  //��������
	virtual HRESULT Init(void);                                                    //����������
	virtual void Uninit(void);	                                                   //�I������
	virtual void Update(void);	                                                   //�X�V����
	virtual void Draw(void);	                                                   //�`�揈��
	virtual void DrawAnim(void);	                                               //�`�揈��(�A�j���[�V����)
	virtual void DrawEffect(void);                                                 //�`�揈��(�G�t�F�N�g)
	void BindTexture(int nIdx);                                                    //�e�N�X�`���̊��蓖��

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos);            //�ʒu�̐ݒ菈��
	void SetPositionOld(D3DXVECTOR3 posOld);      //�ʒu�̐ݒ菈��
	void SetMove(D3DXVECTOR3 move);               //�ړ��ʂ̐ݒ菈��
	void SetRotation(D3DXVECTOR3 rot);            //�����̐ݒ菈��
	void SetScale(D3DXVECTOR3 scale);             //�g�嗦�̐ݒ菈��
	void SetSize(D3DXVECTOR3 size);               //�T�C�Y�̐ݒ菈��
	//void SetSize2D(float fWidth, float fHeight);  //�T�C�Y2D�̐ݒ菈��
	void SetTypeTex(int Type);                    //�e�N�X�`���^�C�v�̐ݒ菈��
	void SetCol(const D3DXCOLOR col);             //�F�ݒ�

	//�擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; };        //�ʒu�̎擾
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //�ߋ��̈ʒu�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; };           //�ړ��ʂ̎擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; };        //�����̎擾
	D3DXVECTOR3 GetScale(void) { return m_scale; };         //�g�嗦�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; };           //�T�C�Y�̎擾
	D3DXCOLOR GetCol(void) { return m_Col; };               //�F�̎擾
	int GetTypeTex(void) { return m_typetex; };             //�e�N�X�`���^�C�v�̎擾

	//���_���̐���
	void SetVtxWidth(void);                 //���_���̐���(��)
	void SetVtxHeight(void);                //���_���̐���(�c)
	void SetVtx(const int m_nPatternAnim);  //���_���̐���(�A�j���[�V����)
	void SetVtxEffect(void);                //���_���̐���(�G�t�F�N�g)

	int m_nCounterAnim;  //�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;  //�A�j���[�V�����p�^�[��No.

private:
	LPDIRECT3DTEXTURE9 m_pTexture;       //�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 //���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;               //���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;                   //�ʒu
	D3DXVECTOR3 m_posOld;                //�ߋ��̈ʒu
	D3DXVECTOR3 m_move;                  //�ړ���
	D3DXVECTOR3 m_rot;                   //��]��
	D3DXVECTOR3 m_scale;                 //�g�嗦
	D3DXVECTOR3 m_size;                  //�T�C�Y��
	D3DXCOLOR m_Col;                     //�F
	int m_typetex;                       //�e�N�X�`���^�C�v
	int m_nIdxTexture;
	float m_fWidth;						 //��
	float m_fHeight;					 //����
};

#endif