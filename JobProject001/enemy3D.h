//=============================================================================
//
// [enemy3D.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _ENEMY3D_H_  //���̃}�N����`������ĂȂ�������
#define _ENEMY3D_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "objectX.h"

//�}�N����`
#define ENEMYSPEED (3.0f)  //�ړ����̃X�s�[�h
#define ENEMYSPEEDUP (0.15f)  //�ړ��ʍX�V���̃X�s�[�h
#define ENEMY_COLLISION (50)  //�����蔻��
#define MAX_ENEMY (30)  //�ő吔
#define USUALLY_COR_X (75.0f)  //�ʏ�G�̊g�嗦���␳X
#define USUALLY_COR_Y (168.0f)  //�ʏ�G�̊g�嗦���␳Y
#define USUALLY_COR_Z (66.0f)  //�ʏ�G�̊g�嗦���␳Z
#define BOSS_COR_X (1255.0f)  //�{�X�̊g�嗦���␳X
#define BOSS_COR_Y (1600.0f)  //�{�X�̊g�嗦���␳Y
#define BOSS_COR_Z (920.0f)  //�{�X�̊g�嗦���␳Z

class CBullet3D;
class CPlayer3D;
class CModelSet;
class CLife;

//�G�N���X
class CEnemy3D : public CObjectX
{
public:
	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_USUALLY = 0,  //�ʏ�G
		TYPE_BOSS,  //�{�X
		TYPE_TUTORIAL_ENE,  //�`���[�g���A���G
		TYPE_MAX
	}TYPE;

	//��ԊǗ�
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,  //�ʏ���
		ENEMYSTATE_DAMAGE,  //�_���[�W���
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	//�{�X�̐퓬�Ԑ����
	typedef enum
	{
		BOSS_BATTEL_0 = 0,  //�����i�K
		BOSS_BATTEL_1,  //�i�K1
		BOSS_BATTEL_2,  //�i�K2
		BOSS_BATTEL_3,  //�i�K3
		BOSS_BATTEL_MAX
	}BOSS_BATTEL;

	//�`���[�g���A���G��ԊǗ�
	typedef enum
	{
		TUTORIAL_ENESTATE_NORMAL = 0,  //�m�[�}�����[�h
		TUTORIAL_ENESTATE_ATTACKMODE,  //�A�^�b�N���[�h
		TUTORIAL_ENESTATE_MAX
	}TUTORIAL_ENESTATE;

	CEnemy3D();   //�R���X�g���N�^
	~CEnemy3D();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);   //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��
	static CEnemy3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life);  //��������
	static void PlayerAttack(CPlayer3D *pPlayer);  //�v���C���[�ߐڍU������
	static void ShootBullet(CPlayer3D *pPlayer);  //�e��������
	static void EnemyBattelState(CModelSet *pModelSet);  //�G�ʂ̐퓬�Ԑ���Ԃ��Ƃ̏���
	void UpdateEnemyState(void);  //���
	static void LifeGauge(CLife *pLife);  //���C�t�Q�[�W

	//�擾
	int GetLife(void) { return m_Life; };  //�̗͂̎擾
	BOSS_BATTEL GetBossBattel(void) { return m_BossBattel; };  //�{�X�̐퓬�Ԑ���Ԃ̎擾

	//�ݒ�
	void SetLife(int Life);  //�̗͂̐ݒ�
	void SetBossDownState(bool BossDownState);  //�{�X���_�E�����Ă邩�̐ݒ�
	void SetEnemyState(ENEMYSTATE state, int nCounterState);  //��Ԃ̐ݒ�
	void SetBossBattel(BOSS_BATTEL BossBattel);  //�{�X�̐퓬�Ԑ���Ԃ̐ݒ�

	//�����蔻�菈��
	static void HitEnemy(int nDamage, int nCnt);  //�q�b�g����
	static bool CollisionBullet(CBullet3D *pBullet);  //�e�Ƃ̓����蔻��

private:
	int m_nIdxModel[TYPE_MAX];  //���f�����蓖��
	int m_Life;  //�̗�
	int m_nID;  //�ԍ�
	int m_nCntHit;  //�_���[�W��Ԃ̃J�E���g
	int m_nCounterState;  //��ԊǗ��J�E���^�[
	int m_nCounterMove;  //�ړ��J�E���^�[
	int m_nCntAttack;  //�v���C���[�̋ߐڍU���J�E���^�[
	int m_nCntEnemyBullet;  //�e�J�E���^�[
	int m_nCntDownSpeed;  //�{�X���_�E������X�s�[�h�J�E���^�[
	bool m_BossDownState;  //�{�X�̃_�E���Ǘ�
	bool m_LifeGaugeSize;  //���C�t�Q�[�W�T�C�Y�̊Ǘ�
	ENEMYSTATE m_state;  //��ԊǗ�
	BOSS_BATTEL m_BossBattel;  //�{�X�̐퓬�Ԑ����
	TUTORIAL_ENESTATE m_TutorialEne;  //�`���[�g���A���G��ԊǗ�
	static bool m_CreateCore;  //�r������R�A���o���p
	static bool m_LifeState;  //���C�t�Q�[�W�Ǘ�
	static CEnemy3D *m_apObject[MAX_ENEMY];  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif