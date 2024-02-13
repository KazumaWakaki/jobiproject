//=============================================================================
//
//[bullet3D.h]
//Author ��� ��^
//
//=============================================================================
#ifndef _BULLET3D_H_  //���̃}�N����`������ĂȂ�������
#define _BULLET3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"
#include "player3D.h"

//�}�N����`
#define MAX_BULLET (128)  //�e�̍ő吔
#define BULLET_COL_XZ	 (27.0f)  //�e�̊g�嗦���␳XZ
#define BULLET_COL_Y (55.0f)  //�e�̊g�嗦���␳Y

//�O���錾
class CPlayer3D;
class CBlock3D;
class CEnemy3D;

//�e�N���X
class CBullet3D : public CObjectX
{
public:
	//�e�̎��
	typedef enum
	{
		BULLETTYPE_PLAYER = 0,  //�v���C���[
		BULLETTYPE_ENEMY,  //�G
		BULLETTYPE_MAX
	}BULLETTYPE;

	CBullet3D();   //�R���X�g���N�^
	~CBullet3D();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);	 //�X�V����
	void Draw(void);	 //�`�揈��
	static CBullet3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int type);  //�e����

	//�擾
	int GetBulletType(void) { return m_type; };  //�e�̎�ނ̎擾

	//�ݒ�
	void SetTypeBullet(int Type);  //�e�̎�ރ^�C�v�̐ݒ�

	//�����蔻��
	static bool CollisionBlock(CBlock3D *pBlock);   //�u���b�N�Ƃ̓����蔻��

private:
	int m_nLife;	     //����
	int m_nIdxModel[BULLETTYPE_MAX];     //���f�����蓖��
	int m_type;          //�e�̃^�C�v
	int m_nID;           //�ԍ�
	int m_nCntHit;  //�_���[�W��Ԃ̃J�E���g
	static CBullet3D *m_apObject[MAX_BULLET];  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif