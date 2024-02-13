//=============================================================================
//
// [life.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _LIFE_H_  //���̃}�N����`������Ȃ�������
#define _LIFE_H_  //2�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"

class CPlayer3D;
class CEnemy3D;

//���C�t�N���X
class CLife : public CObject2D
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_LIFEGAUGE = 0,  //���C�t�Q�[�W
		TYPE_LIFEFRAME,  //���C�t�g
		TYPE_BOSSLIFEGAUGE,  //�{�X�̃��C�t�Q�[�W
		TYPE_MAX
	}TYPE;

	//�Q�[�W�̒i�K����
	typedef enum
	{
		LIFE_500 = 0,  //�̗�500
		LIFE_400,  //�̗�400
		LIFE_300,  //�̗�300
		LIFE_200,  //�̗�200
		LIFE_100,  //�̗�100
		LIFE_MAX
	}LIFETYPE;

	CLife();   //�R���X�g���N�^
	~CLife();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);  //�I������
	void Update(void);  //�X�V����
	void Draw(void);  //�`�揈��
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //���C�t����

	//�擾
	int GetLife(void) { return m_nLife; };  //���C�t�̒i�K�擾

	//�ݒ�
	void SetLife(int nLife);

private:
	int m_nID;  //�ԍ�
	int m_nLife;  //����
	int m_nIdxTexture[TYPE_MAX];  //�e�N�X�`��
	static CLife *m_apObject;  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif