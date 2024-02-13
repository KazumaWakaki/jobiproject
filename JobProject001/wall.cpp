//=============================================================================
//
//�ǂ̏��� [wall.cpp]
//Author ��� ��^
//
//=============================================================================
#include "manager.h"
#include "wall.h"

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CWall::CWall(int nPriority) : CObject3D(nPriority)
{
	//�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CWall::~CWall()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CWall::Init()
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture[TYPE_WALL001] = pTexture->Regist("data\\texture\\neonwall001.jpg");
	m_nIdxTexture[TYPE_HAIKEI001] = pTexture->Regist("data\\texture\\sougen001.jpg");

	//3D�I�u�W�F�N�g�̏���������
	CObject3D::Init();

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CWall::Uninit()
{
	//3D�I�u�W�F�N�g�̏I������
	CObject3D::Uninit();
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CWall::Update()
{
	//3D�I�u�W�F�N�g�̍X�V����
	//CObject3D::Update();

	//���_���̌Ăяo��(�c)
	CObject3D::SetVtxHeight();
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CWall::Draw()
{
	//3D�I�u�W�F�N�g�̕`�揈��
	CObject3D::Draw();
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int SetTypeTex)
{
	CWall *pWall;

	//�ǂ̐���
	pWall = new CWall;

	//pWall��NULL����Ȃ���
	if (pWall != NULL)
	{
		//����������
		pWall->Init();

		//�ǂ̈ʒu�̐ݒ�
		pWall->SetPosition(pos);

		//�ǂ̌����̐ݒ�
		pWall->SetRotation(rot);

		//�ǂ̃T�C�Y�ݒ�
		pWall->SetSize(size);

		//�ǂ̃e�N�X�`���^�C�v
		pWall->SetTypeTex(SetTypeTex);

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ�e�N�X�`���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pWall->BindTexture(pWall->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pWall;
}