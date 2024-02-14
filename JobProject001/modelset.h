//=============================================================================
//
// [modelset.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _MODELSET_H_  //���̃}�N����`������ĂȂ�������
#define _MODELSET_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"
#include "model.h"

class CPlayer3D;
class CEnemy3D;
class CBullet3D;

//�}�N����`
#define CHECKPOINT_COR (30.0f)  //�`�F�b�N�|�C���g�̊g�嗦���␳
#define BOSSCORE_COR_X (41.0f)  //�{�X�R�A�̊g�嗦���␳X
#define BOSSCORE_COR_Y (100.0f)  //�{�X�R�A�̊g�嗦���␳Y
#define BOSSCORE_COR_Z (50.0f)  //�{�X�R�A�̊g�嗦���␳Z

//���f���ݒ�N���X
class CModelSet : public CObjectX
{
public:
	//���f���^�C�v���
	typedef enum
	{
		TYPE_SWORD = 0,  //���{��
		TYPE_CHECKPOINT,  //�`�F�b�N�|�C���g
		TYPE_BOSSCORE,  //�{�X�R�A
		TYPE_BEAM_PLA,  //�r�[���v���C���[
		TYPE_BEAM_ENE,  //�r�[���G
		TYPE_MAX
	}TYPE;

	//���{���̍U��3�i�K
	typedef enum
	{
		SWORDROT_0 = 0,  //�U�����Ă��Ȃ�
		SWORDROT_1,  //��i�K��
		SWORDROT_2,  //��i�K��
		SWORDROT_3,  //�O�i�K��
		SWORDROT_MAX
	}SWORDROT;

	//�{�X�R�A�̏��
	typedef enum
	{
		BOSSCORESTATE_NONE = 0,  //�Ȃ�
		BOSSCORESTATE_BREAK,  //�󂳂ꂽ
		BOSSCORESTATE_LIVE,  //�����Ă�
		BOSSCORESTATE_MAX
	}BOSSCORESTATE;

	CModelSet();   //�R���X�g���N�^
	~CModelSet();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);	 //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);  //�`�揈��
	static CModelSet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex);  //��������
	void SwordRotMove(void);  //���{�������ړ�����

	//�����蔻�菈��
	static bool ModelCollision(CPlayer3D *pPlayer);  //�v���C���[�Ƃ̓����蔻�菈��
	static bool CollisionBullet(CBullet3D *pBullet);  //�e�Ƃ̓����蔻��

	//�ړ�����
	static void SwordMove(CPlayer3D *pPlayer);  //���{���U���ړ��ʏ���
	static void CoreMove(CEnemy3D *pEnemy);  //�{�X�̃R�A�ړ��ʏ���

	//�擾
	int GetnCntBreakCore(void) { return m_nCntBreakCore; };  //�R�A�̔j�󂳂ꂽ���J�E���^�[�̎擾
	SWORDROT GetSwordRot(void) { return m_SwordRot; }  //���{���̍U��3�i�K
	BOSSCORESTATE GetBossCoreState(void) { return m_BossCoreState; }  //�R�A����ꂽ���̎擾

	//�ݒ�
	void SetnCntBreakCore(int nCntBreakCore);  //�R�A�̔j�󂳂ꂽ���J�E���^�[�̐ݒ�
	void SetBreakCore(bool BreakCore);  //�R�A����ꂽ���̊m�F�̐ݒ�
	void SetSwordRot(SWORDROT SwordRot);  //���{���̍U��3�i�K
	void SetBossCoreState(BOSSCORESTATE BossCoreState);  //�R�A����ꂽ���̐ݒ�

private:
	int m_AttackSwordCnt;  //���̍U���J�E���g
	int m_nCntDown;  //�W�����v�̃J�E���g
	int m_nID;  //�ԍ�
	int m_nIdxTexture[TYPE_MAX];   //�e�N�X�`���ۑ�
	int m_nIdxModel[TYPE_MAX];     //���f�����蓖��
	int m_nCntSword;  //���{���̓����J�E���g
	int m_nCntSwordAttack;  //���{���̌����J�E���g
	int m_nCntSwordRot;  //���{���̌����J�E���g
	int m_nCntBeamScale;  //�r�[���̃X�P�[���J�E���g
	static int m_nCntBreakCore;  //�R�A�̔j�󂳂ꂽ���J�E���^�[
	bool m_BreakCore;  //�R�A����ꂽ���̊m�F�p
	BOSSCORESTATE m_BossCoreState;  //�R�A����ꂽ���̊Ǘ�
	D3DXVECTOR3 m_SwordTag;  //���{���̃^�[�Q�b�g
	D3DXVECTOR3 m_SwordRotTag;  //���{���̌����^�[�Q�b�g
	SWORDROT m_SwordRot;  //���{���̍U��3�i�K
	static CModelSet *m_apObject[MAX_MODEL];  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif