//=============================================================================
//
// �r���{�[�h���� [billboard.cpp]
// Author ��� ��^
//
//=============================================================================
#include "billboard.h"
#include "manager.h"

//-------------------------------------------------------
//�R���X�g���N�^
//-------------------------------------------------------
CBillboard::CBillboard()
{
	//�ϐ��̃N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//-------------------------------------------------------
//�f�X�g���N�^
//-------------------------------------------------------
CBillboard::~CBillboard()
{

}
//=======================================================
//�r���{�[�h�̏���������
//=======================================================
HRESULT CBillboard::Init(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//�r���{�[�h���̏�����
	//m_pos = D3DXVECTOR3(-200.0f, 0.0f, 0.0f);  //�ʒu

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���̐���
	//SetVtx();

	//��ނ̐ݒ�
	SetType(TYPE_BILLBOARD);

	return (S_OK);
}
//=======================================================
//�r���{�[�h�̏I������
//=======================================================
void CBillboard::Uninit(void)
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �p��
	Release();
}
//=======================================================
//�r���{�[�h�̍X�V����
//=======================================================
void CBillboard::Update(void)
{

}
//=======================================================
//�r���{�[�h�̕`�揈��
//=======================================================
void CBillboard::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();  //�f�o�C�X�̎擾
	D3DXMATRIX mtxTrans;   //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;   //�r���[�}�g���b�N�X�擾�p

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);  //�t�s������߂�
	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetAddress(m_nIdxTexture));

	//�r���{�[�h�̕`��  �l�p�`
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//-------------------------------------------------------
//��������
//-------------------------------------------------------
CBillboard *CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CBillboard *pBillboard;

	//�r���{�[�h�̐���
	pBillboard = new CBillboard;

	if (pBillboard != NULL)
	{
		//����������
		pBillboard->Init();

		//�r���{�[�h�̈ʒu�̐ݒ�
		pBillboard->SetPosition(pos);

		//�r���{�[�h�̃T�C�Y�ݒ�
		pBillboard->SetSize(size);
	}

	else
	{//�����Ɏ��s�����ꍇ
		return NULL;
	}

	return pBillboard;
}
//-------------------------------------------------------
//���_���̐���
//-------------------------------------------------------
void CBillboard::SetVtx(void)
{
	VERTEX_3D *pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���(�e)
//-------------------------------------------------------
void CBillboard::SetVtxBullet(void)
{
	VERTEX_3D *pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//���_���̐���(���C�t)
//-------------------------------------------------------
void CBillboard::SetVtxLife(void)
{
	VERTEX_3D *pVtx;  //���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(- m_size.x, + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x, + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x, - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x, - m_size.y, 0.0f);

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//�e�N�X�`�����W�ݒ�
//-------------------------------------------------------
void CBillboard::SetVtx(const int nPatternAnim, const int nTexWidth, const int nTexHeight)
{
	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//���_���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[1].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth)));
	pVtx[2].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)nPatternAnim, (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));
	pVtx[3].tex = D3DXVECTOR2(1.0f / nTexWidth * (float)(nPatternAnim + 1), (1.0f / nTexHeight * (float)(nPatternAnim / nTexWidth + 1)));

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
//-------------------------------------------------------
//�ʒu�̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//�ߋ��̈ʒu�̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//�ړ��ʂ̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//�����̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//�g�嗦�̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//�T�C�Y�̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//-------------------------------------------------------
//�e�N�X�`���^�C�v�̐ݒ菈��
//-------------------------------------------------------
void CBillboard::SetTypeTex(int Type)
{
	m_typetex = Type;
}
//==========================================================
//�e�N�X�`���ݒ�
//==========================================================
void CBillboard::BindTexture(int nIdx)
{
	m_nIdxTexture = nIdx;
}