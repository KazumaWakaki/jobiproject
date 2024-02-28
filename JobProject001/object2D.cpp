//=============================================================================
//
// 2D�I�u�W�F�N�g�������� [object2D.cpp]
// Author ��� ��^
//
//=============================================================================
#include "object2D.h"
#include "manager.h"

//�}�N����`
#define AMIMEMAX        (8)  //�A�j���[�V�������x
#define POSITION_X (130.0f)  //���_���WX
#define POSITION_Y (100.0f)  //���_���WY

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CObject2D::CObject2D(int nPriority) : CObject(nPriority)
{
	//�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_nCounterAnim = 0;
	m_nPatternAnim = 0;
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CObject2D::~CObject2D()
{

}
//-------------------------------------------------------
//����������
//-------------------------------------------------------
HRESULT CObject2D::Init()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture[TYPE_TITLE] = pTexture->Regist("data\\texture\\Robot_Runners_title.jpg");
	m_nIdxTexture[TYPE_TUTORIAL] = pTexture->Regist("data\\texture\\tutorial001.jpg");
	m_nIdxTexture[TYPE_RESULT] = pTexture->Regist("data\\texture\\Robot_Runners_result.jpg");
	m_nIdxTexture[TYPE_CROSS] = pTexture->Regist("data\\texture\\cross.png");
	m_nIdxTexture[TYPE_RESPAWN] = pTexture->Regist("data\\texture\\restart.jpg");
	m_nIdxTexture[TYPE_RESPAWNBG] = pTexture->Regist("data\\texture\\BG001.jpg");

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
	                            D3DUSAGE_WRITEONLY,
	                            FVF_VERTEX_2D,
	                            D3DPOOL_MANAGED,
	                            &m_pVtxBuff,
	                            NULL);

	//�����Ɏ��s�����ꍇ
	if (m_pVtxBuff == NULL)
	{
		return E_FAIL;
	}

	//���_���ݒ�
	//SetVtx();

	return (S_OK);
}
//-------------------------------------------------------
//�I������
//-------------------------------------------------------
void CObject2D::Uninit()
{
	//����o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	//�폜����
	Release();
}
//-------------------------------------------------------
//�X�V����
//-------------------------------------------------------
void CObject2D::Update()
{
	//�L�[�{�[�h�̎擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//�Q�[���p�b�h�̎擾
	CInputPad *pInputPad;
	pInputPad = CManager::GetInstance()->GetInputPad();

	//���X�|�[���̎�
	if (m_typetex == TYPE_RESPAWN)
	{
		//�W�����v�L�[�������ꂽ��
		if (pInputKeyboard->GetRelease(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
		{
			//�I������
			Uninit();
		}
	}

	//���X�|�[���w�i�̎�
	if (m_typetex == TYPE_RESPAWNBG)
	{
		//�W�����v�L�[�������ꂽ��
		if (pInputKeyboard->GetRelease(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
		{
			//�I������
			Uninit();
		}
	}
}
//-------------------------------------------------------
//�`�揈��
//-------------------------------------------------------
void CObject2D::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAddress(m_nIdxTexture[GetTypeTex()]));

	//�I�u�W�F�N�g�̕`��  �l�p�`
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  //�v���~�e�B�u�̎��
	                       0,
	                       2);                   //���_���\���̂̃T�C�Y
}
//-------------------------------------------------------
//�`�揈��(�G�t�F�N�g)
//-------------------------------------------------------
void CObject2D::DrawEffect()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));


	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAddress(m_nIdxTexture[GetTypeTex()]));

	//���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�I�u�W�F�N�g�̕`��  �l�p�`
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,  //�v���~�e�B�u�̎��
		0,
		2);  //���_���\���̂̃T�C�Y}

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CObject2D *CObject2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, int SetTypeTex)
{
	CObject2D *pObject2D = NULL;

	//�I�u�W�F�N�g2D�̐���
	pObject2D = new CObject2D;

	//pObject2D��NULL����Ȃ���
	if (pObject2D != NULL)
	{
		//����������
		pObject2D->Init();

		//�ʒu�̐ݒ�
		pObject2D->SetPosition(pos);

		//�����̐ݒ�
		pObject2D->SetRotation(rot);

		//�T�C�Y�ݒ�
		pObject2D->SetSize(size);

		//
		pObject2D->SetVtx();

		//�F�ݒ�
		pObject2D->SetCol(col);

		//�I�u�W�F�N�g2D�̃e�N�X�`���^�C�v
		pObject2D->SetTypeTex(SetTypeTex);

		//nCount����
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCount�ƑI�����ꂽ�e�N�X�`���^�C�v����v������
			if (nCount == SetTypeTex)
			{
				//�e�N�X�`���̊��蓖��
				pObject2D->BindTexture(pObject2D->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pObject2D;
}
//-------------------------------------------------------
//���_���̐���
//-------------------------------------------------------
void CObject2D::SetVtx(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���(UI)
//-------------------------------------------------------
void CObject2D::SetVtxUI(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_scale.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(m_scale.x, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���(�w�i)
//-------------------------------------------------------
void CObject2D::SetVtxBG(float g_aTexV, float g_aTexU)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(g_aTexU, g_aTexV);
	pVtx[1].tex = D3DXVECTOR2(g_aTexU + 1.0f, g_aTexV);
	pVtx[2].tex = D3DXVECTOR2(g_aTexU, g_aTexV + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_aTexU + 1.0f, g_aTexV + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���(�G�t�F�N�g)
//-------------------------------------------------------
void CObject2D::SetVtxEffect(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f );

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���(�A�j���[�V����)
//-------------------------------------------------------
void CObject2D::SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[1].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[2].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));
	pVtx[3].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���
//-------------------------------------------------------
void CObject2D::SetVtxLife(int posR)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(posR + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(posR + m_size.x, m_pos.y + m_size.y, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//�ʒu�̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//�ߋ��̈ʒu�̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//�ړ��ʂ̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//�g�嗦�̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//�T�C�Y�̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;
}
//-------------------------------------------------------
//�e�N�X�`���^�C�v�̐ݒ菈��
//-------------------------------------------------------
void CObject2D::SetTypeTex(int Type)
{
	m_typetex = Type;
}
//-------------------------------------------------------
//���_���̐F�ύX
//-------------------------------------------------------
void CObject2D::SetCol(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//�e�N�X�`���̊��蓖��
//-------------------------------------------------------
void CObject2D::BindTexture(int nIdx)
{
	m_nIdxTexture[GetTypeTex()] = nIdx;
}