//=============================================================================
//
// [renderer.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _RENDERER_H_  //���̃}�N����`������ĂȂ�������
#define _RENDERER_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�����_���[�N���X
class CRenderer
{
public:
	CRenderer();  //�R���X�g���N�^
	~CRenderer(); //�f�X�g���N�^

	HRESULT Init(HWND hWnd, bool bWindow);  //����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��
	LPDIRECT3DDEVICE9 GetDevice(void);      //�f�o�C�X�̎擾

private:

	LPDIRECT3D9 m_pD3D;              //Direct3D�I�u�W�F�N�g�̐���
	LPDIRECT3DDEVICE9 m_pD3DDevice;  //�f�o�C�X�̐錾
};

#endif