//=============================================================================
//
//[object2D.h]
//Author ��� ��^
//
//=============================================================================
#ifndef _OBJECT2D_H_  //���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�}�N����`
#define COUNTAMIME (8)  //�A�j���[�V�������x
#define PATTERNAMIME (8)  //�A�j���[�V�����p�^�[����
#define PATTERNTEX (0.125f)  //�e�N�X�`���̃p�^�[����

//�I�u�W�F�N�g2D�N���X
class CObject2D : public CObject
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_TITLE = 0,  //�^�C�g��
		TYPE_TUTORIAL,  //�`���[�g���A��
		TYPE_RESULT,  //���U���g
		TYPE_CROSS,  //�N���X�w�A
		TYPE_RESPAWN,  //���X�|�[��
		TYPE_RESPAWNBG,  //���X�|�[���w�i
		TYPE_MAX
	}TYPE;

	CObject2D(int nPriority = 3);  //�R���X�g���N�^
	~CObject2D();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);  //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);  //�`�揈��
	virtual void DrawEffect(void);  //�`�揈��(�G�t�F�N�g)
	static CObject2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int SetTypeTex);  //��������
	void BindTexture(int nIdx);  //�e�N�X�`���̊��蓖��

	//�擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; };  //�ʒu�̎擾
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //�ߋ��̈ʒu�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; };  //�ړ��ʂ̎擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; };  //�����̎擾
	D3DXVECTOR3 GetScale(void) { return m_scale; };  //�g�嗦�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; };  //�T�C�Y�̎擾
	int GetTypeTex(void) { return m_typetex; };  //�e�N�X�`���^�C�v�̎擾

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos);  //�ʒu�̐ݒ菈��
	void SetPositionOld(D3DXVECTOR3 posOld);  //�ߋ��̈ʒu�̐ݒ菈��
	void SetMove(D3DXVECTOR3 move);  //�ړ��ʂ̐ݒ菈��
	void SetRotation(D3DXVECTOR3 rot);  //�����̐ݒ菈��
	void SetScale(D3DXVECTOR3 scale);  //�g�嗦�̐ݒ菈��
	void SetSize(D3DXVECTOR3 size);  //�T�C�Y�̐ݒ菈��
	void SetTypeTex(int Type);  //�e�N�X�`���^�C�v�̐ݒ菈��

	//���_���̐ݒ�p
	void SetVtx(void);  //���_���̐���
	void SetVtxUI(void);  //���_���̐���(UI)
	void SetVtxBG(float g_aTexV, float g_aTexU);  //���_���̐���(�w�i)
	void SetVtxEffect(void);  //���_���̐���(�G�t�F�N�g)
	void SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight);  //���_���̐���(�A�j���[�V����)
	void SetVtxLife(int posR);  //���_���̐���(�̗�)
	void SetCol(const D3DXCOLOR col);  //�F�̐ݒ�

	//�A�j���[�V�����p
	int m_nCounterAnim;  //�A�j���[�V�����J�E���^�[
	int m_nPatternAnim;  //�A�j���[�V�����p�^�[��No.

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	 //���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_posOld;  //�ߋ��̈ʒu
	D3DXVECTOR3 m_move;  //�ړ���
	D3DXVECTOR3 m_rot;  //��]��
	D3DXVECTOR3 m_scale;  //�g�嗦
	D3DXVECTOR3 m_size;  //�T�C�Y��
	D3DXCOLOR m_col;  //�F
	float m_fWidth;  //��
	float m_fHeight;  //����
	int m_typetex;  //�e�N�X�`���^�C�v
	int m_nIdxTexture[TYPE_MAX];  //�e�N�X�`�����蓖��
};

#endif