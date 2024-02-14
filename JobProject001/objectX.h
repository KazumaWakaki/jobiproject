//=============================================================================
//
//[objectX.h]
//Author ��� ��^
//
//=============================================================================
#ifndef _OBJECTX_H_  //���̃}�N����`������ĂȂ�������
#define _OBJECTX_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�}�N����`
#define INIT_VTX_MIN (D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))  //���f���̍ŏ��̒��_���W�̏����l
#define INIT_VTX_MAX (D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))  //���f���̍ő�̒��_���W�̏����l

//�I�u�W�F�N�g3D�N���X
class CObjectX : public CObject
{
public:

	CObjectX();  //�R���X�g���N�^
	~CObjectX();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);  //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);  //�`�揈��
	static CObjectX *CObjectX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, TYPE type);  //��������

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos);  //�ʒu�̐ݒ菈��
	void SetPositionOld(D3DXVECTOR3 posOld);  //�ʒu�̐ݒ菈��
	void SetMove(D3DXVECTOR3 move);  //�ړ��ʂ̐ݒ菈��
	void SetRotation(D3DXVECTOR3 rot);  //�����̐ݒ菈��
	void SetScale(D3DXVECTOR3 scale);  //�g�嗦�̐ݒ菈��
	void SetSize(D3DXVECTOR3 size);  //�T�C�Y�̐ݒ菈��
	void SetType(const TYPE type);  //�^�C�v�ݒ�
	void SetTypeTex(int Type);  //�e�N�X�`���^�C�v�̐ݒ菈��
	void BindModel(int nIdx);  //���f���̊��蓖��
	void SetMat(int nIdx, D3DXMATERIAL mat);  //���̃}�e���A����ݒ�
	void ResetMat();//Drawmat��

	//�擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; };  //�ʒu�̎擾
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //�ߋ��̈ʒu�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; };  //�ړ��ʂ̎擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; };  //�����̎擾
	D3DXVECTOR3 GetScale(void) { return m_scale; };  //�g�嗦�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; };  //�T�C�Y�̎擾
	int GetTypeTex(void) { return m_typetex; };  //�e�N�X�`���^�C�v�̎擾

protected:

	int m_nIdxModel;  //���f��

private:
	LPD3DXMESH m_pMesh;  //���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;  //�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;  //�}�e���A���̐�
	D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_posOld;  //�ߋ��̈ʒu
	D3DXVECTOR3 m_move;  //�ړ���
	D3DXVECTOR3 m_rot;  //����
	D3DXVECTOR3 m_scale;  //�g�嗦
	D3DXVECTOR3 m_size;  //�T�C�Y��
	D3DXMATRIX  m_mtxWorld;  //���[���h�}�g���b�N�X
	D3DXMATERIAL m_DrawMat[32];  //
	LPDIRECT3DTEXTURE9 m_apTexture[8];  //�e�N�X�`���ւ̃|�C���^
	TYPE m_type;  //�^�C�v���
	int m_typetex;  //�e�N�X�`���^�C�v
	float m_fWidth;  //��
	float m_fHeight;  //����
};

#endif