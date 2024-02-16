//=============================================================================
//
// [player3D.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _PLAYER3D_H_  //���̃}�N����`������ĂȂ�������
#define _PLAYER3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"
#include "enemy3D.h"
#include "life.h"
#include "gauge.h"

class CBullet3D;
class CLife;
class CGauge;

//�}�N����`
#define PLAYERSPEED (5.5f)  //�ړ����̃X�s�[�h
#define PLAYERSPEEDUP (0.2f)  //�ړ��ʍX�V���̃X�s�[�h
#define STEPSPEED (100.0f)  //�X�e�b�v���̃X�s�[�h
#define WALLRUNSPEED (8.0f)  //�Ǒ���̃X�s�[�h
#define WALLJAMPSPEED (250.0f)  //�Ǒ���W�����v�̃X�s�[�h
#define PLAYER_COL_X (95.0f)  //�v���C���[�̊g�嗦���␳X
#define PLAYER_COL_Y (400.0f)  //�v���C���[�̊g�嗦���␳Y
#define PLAYER_COL_Z (66.0f)  //�v���C���[�̊g�嗦���␳Z
#define PLALIFE (500)  //�̗�
#define PLASTAMINA_MAX (150)  //�X�^�~�i���
#define PLASTAMINA_HEAL (80)  //�X�^�~�i���񕜂���܂ł̎���
#define SLOW (80)  //�X���[�p

#if _DEBUG

//#define PLAYERSPEED (5.0f)  //�ړ����̃X�s�[�h

#endif

//�v���C���[3D�N���X
class CPlayer3D : public CObjectX
{
public:
	//�W�����v���
	typedef enum
	{
		PLAYERJUMP_GROUND = 0,  //�n��
		PLAYERJUMP_SKY,  //�W�����v���
		PLAYERJUMP_GETOFF,  //�~�����
		PLAYERJUMP_WALLRUN_R,  //�Ǒ����ԉE����
		PLAYERJUMP_WALLRUN_L,  //�Ǒ����ԍ�����
		PLAYERJUMP_MAX
	}PLAYERJAMP;

	//���{���̍U��3�i�K
	typedef enum
	{
		SWORDATTACK_0 = 0,  //�U�����Ă��Ȃ�
		SWORDATTACK_1,  //��i�K��
		SWORDATTACK_2,  //��i�K��
		SWORDATTACK_3,  //�O�i�K��
		SWORDATTACK_MAX
	}SWORDATTACK;

	//���X�|�[�����
	typedef enum
	{
		STATERES_NONE = 0,  //�ʏ�
		STATERES_RESPAWN,  //���X�|�[���ҋ@
		STATERES_MAX
	}STATERES;

	//�X�e�b�v���
	typedef enum
	{
		STEPSTATE_NONE = 0,  //�ʏ�
		STEPSTATE_STEP,  //�X�e�b�v���
		STEPSTATE_OUTSTAMINA,  //�X�^�~�i�؂���
		STEPSTATE_MAX
	}STEPSTATE;

	CPlayer3D();   //�R���X�g���N�^
	~CPlayer3D();  //�f�X�g���N�^

	//�����o�֐�
	virtual HRESULT Init(void);  //����������
	virtual void Uninit(void);	 //�I������
	virtual void Update(void);  //�X�V����
	virtual void Draw(void);	 //�`�揈��
	static CPlayer3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size);  //��������
	void StepMode(void);  //�X�e�b�v���

	//�擾
	int GetLife(void) { return m_Life; };  //�̗͂̎擾
	bool GetStepPossible(void) { return m_StepPossible; };  //�X�e�b�v�\��Ԑ؂�ւ��擾
	bool GetRestart(void) { return m_Restart; };  //���X�^�[�g��Ԑ؂�ւ��擾
	PLAYERJAMP GetJamp(void) { return m_jump; }  //�W�����v���Ă邩�̎擾
	SWORDATTACK GetSwordAttack(void) { return m_SwordAttack; };  //���{���̍U���i�K�̎擾
	STATERES GetStateRes(void) { return m_StateRes; };  //���X�|�[����Ԃ̎擾
	D3DXVECTOR3 GetStartPos(void) { return m_StartPos; };  //�ۑ�����Ă���X�^�[�g�ʒu�̎擾
	D3DXVECTOR3 GetKeepPos(void) { return m_KeepPos; };  //�ۑ�����Ă���ʒu�̎擾

	//�ݒ�
	void SetLife(int Life);  //�̗͂̐ݒ�
	void SetStepPossible(bool StepPossible);  //�X�e�b�v�\��Ԑ؂�ւ��̐ݒ�
	void SetRestart(bool Restart);  //���X�^�[�g��Ԑ؂�ւ��ݒ�
	void SetPlayerJump(PLAYERJAMP Jamp);  //�W�����v��Ԃ̐ݒ�
	void SetSwordAttack(SWORDATTACK SwordAttack);  //���{���̍U���i�K�̐ݒ�
	void SetStateRes(STATERES StateRes);  //���X�|�[����Ԃ̐ݒ�
	void SetKeepPos(D3DXVECTOR3 KeepPos);  //�ۑ�����Ă���ʒu�̐ݒ�

	//�����蔻��
	static void HitPlayer(int nDamage);  //�v���C���[�̃q�b�g����
	static bool CollisionEnemy(CEnemy3D *pEnemy);  //�G�Ƃ̓����蔻��
	static bool CollisionBullet(CBullet3D *pBullet);  //�e�Ƃ̓����蔻��
	static void LifeMove(CLife *pLife);  //���C�t�ݒ菈��
	static void StepGaugeMove(CGauge *pGauge);  //�X�e�b�v�Q�[�W�ݒ菈��

private:
	int m_nIdxTexture;  //�e�N�X�`���ۑ�
	int m_nIdxMode;  //���f�����蓖��
	int m_nCntDown;  //�W�����v�̃J�E���g
	int m_nCntAttack;  //�A�^�b�N�J�E���g
	int m_nCntStep;  //�X�e�b�v�̃J�E���g
	int m_Life;  //�̗�
	int m_StepGauge;  //�X�e�b�v�Q�[�W
	int m_StepGaugeCnt;  //�X�e�b�v�J�E���g�Q�[�W
	bool m_Step;  //�X�e�b�v��Ԑ؂�ւ�
	bool m_StepPossible;  //�X�e�b�v�\��Ԑ؂�ւ�
	bool m_Restart;  //���X�^�[�g��Ԑ؂�ւ�
	static bool m_BossState;  //�{�X�������Ǘ�
	PLAYERJAMP m_jump;  //�v���C���[�̃W�����v
	SWORDATTACK m_SwordAttack;  //���{���̍U��3�i�K
	STATERES m_StateRes;  //���X�|�[�����
	STEPSTATE m_StepState;  //�X�e�b�v���
	D3DXVECTOR3 m_StartPos;  //�X�^�[�g�ʒu
	D3DXVECTOR3 m_KeepPos;  //�ʒu�ۑ�
	static CPlayer3D *m_apObject;  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif