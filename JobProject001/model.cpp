//=============================================================================
//
// ���f���Ǘ� [model.cpp]
// Author ��� ��^
//
//=============================================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"

//�ÓI�����o�ϐ�
CModel::Model CModel::m_apModel[MAX_MODEL] = {};
char CModel::m_FileName[MAX_MODEL][512] = {};
int  CModel::m_nNumAll = 0;

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CModel::CModel()
{

}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CModel::~CModel()
{

}
//-------------------------------------------------------
//�S�Ẵ��f���̓ǂݍ���
//-------------------------------------------------------
HRESULT CModel::Load(void)
{
	return (S_OK);
}
//-------------------------------------------------------
//�S�Ẵ��f���̔j��
//-------------------------------------------------------
void CModel::Unload(void)
{
	//MAX_MODEL����
	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		//���b�V���̔j��
		if (m_apModel[nCntModel].m_pMesh != NULL)
		{
			m_apModel[nCntModel].m_pMesh->Release();
			m_apModel[nCntModel].m_pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_apModel[nCntModel].m_pBuffMat != NULL)
		{
			m_apModel[nCntModel].m_pBuffMat->Release();
			m_apModel[nCntModel].m_pBuffMat = NULL;
		}
	}
}
//-------------------------------------------------------
//���f����ݒ肷��
//-------------------------------------------------------
int CModel::Regist(const char *pFilename)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	int nIdx;

	nIdx = m_nNumAll + 1;  //�ۑ�

						   //m_nNumAll����
	for (int nCntModel = 0; nCntModel < m_nNumAll; nCntModel++)
	{
		if (strcmp(&m_FileName[nCntModel][0], pFilename) == 0)
		{
			nIdx = nCntModel;

			return nIdx;
		}
	}

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_apModel[nIdx].m_pBuffMat,
		NULL,
		&m_apModel[nIdx].m_dwNumMat,
		&m_apModel[nIdx].m_pMesh);

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	D3DXMATERIAL *pMat;  //�}�e���A���ւ̃|�C���^

	m_apModel[nIdx].pIndxTex = new int[(int)m_apModel[nIdx].m_dwNumMat];

	//�}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_apModel[nIdx].m_pBuffMat->GetBufferPointer();

	//�}�e���A���̕�������
	for (int nCntMat = 0; nCntMat < (int)m_apModel[nIdx].m_dwNumMat; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//�e�N�X�`����ۑ�����
			m_apModel[nIdx].pIndxTex[nCntMat] = pTexture->Regist(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_apModel[nIdx].pIndxTex[nCntMat] = -1;
		}
	}

	strcpy(&m_FileName[nIdx][0], pFilename);

	m_nNumAll++;

	return nIdx;
}
//-------------------------------------------------------
//�A�h���X��Ԃ�
//-------------------------------------------------------
CModel::Model *CModel::GetAddress(int nIdx)
{
	return &m_apModel[nIdx];
}