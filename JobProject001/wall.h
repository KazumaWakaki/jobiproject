//=============================================================================
//
// [wall.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _WALL_H_  //���̃}�N����`������ĂȂ�������
#define _WALL_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object3D.h"

//3D�ǃN���X
class CWall : public CObject3D
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_WALL001 = 0,  //��
		TYPE_HAIKEI001,  //�т̔w�i
		TYPE_MAX
	}TYPE;

	CWall(int nPriority = 3);
	~CWall();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);	    //�I������
	virtual void Update(void);	//�X�V����
	virtual void Draw(void);	    //�`�揈��
	static CWall *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int SetTypeTex);  //��������

private:
	LPDIRECT3DTEXTURE9 m_pTexture;  //�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_pos;  //�ʒu
	D3DXVECTOR3 m_rot;  //��]��
	D3DXVECTOR3 m_size;  //�T�C�Y��
	int m_typetex;  //�e�N�X�`���^�C�v
	int m_nIdxTexture[TYPE_MAX];  //�e�N�X�`��
};

#endif