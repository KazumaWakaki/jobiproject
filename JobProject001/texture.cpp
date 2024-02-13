//=============================================================================
//
// �e�N�X�`���Ǘ� [texture.cpp]
// Author ��� ��^
//
//=============================================================================
#include "texture.h"
#include "manager.h"

//�ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[MAX_TEXTURE] = {};
char CTexture::m_FileName[MAX_TEXTURE][512] = {};
int  CTexture::m_nNumAll = 0;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CTexture::CTexture()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CTexture::~CTexture()
{

}
//-------------------------------------------------------
//�S�Ẵe�N�X�`���̓ǂݍ���
//-------------------------------------------------------
HRESULT CTexture::Load(void)
{
	return (S_OK);
}
//-------------------------------------------------------
//�S�Ẵe�N�X�`���̔j��
//-------------------------------------------------------
void CTexture::Unload(void)
{
	//MAX_TEXTURE����
	for (int nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		//�e�N�X�`���̔j��
		if (m_apTexture[nCntTexture] != NULL)
		{
			m_apTexture[nCntTexture]->Release();
			m_apTexture[nCntTexture] = NULL;
		}
	}
}
//-------------------------------------------------------
//�e�N�X�`����ݒ肷��
//-------------------------------------------------------
int CTexture::Regist(const char *pFilename)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	int nIdx;

	nIdx = m_nNumAll + 1;  //�ۑ�

	//m_nNumAll����
	for (int nCntTexture = 0; nCntTexture < m_nNumAll; nCntTexture++)
	{
		if (strcmp(&m_FileName[nCntTexture][0], pFilename) == 0)
		{
			nIdx = nCntTexture;

			return nIdx;
		}
	}

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pFilename, &m_apTexture[nIdx]);

	strcpy(&m_FileName[nIdx][0], pFilename);

	m_nNumAll++;

	return nIdx;
}
//-------------------------------------------------------
//�A�h���X��Ԃ�
//-------------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	if (nIdx <= m_nNumAll && 0 <= nIdx)
	{
		return m_apTexture[nIdx];
	}

	return NULL;
}