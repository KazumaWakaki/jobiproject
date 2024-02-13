//=============================================================================
//
// [object.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _OBJECT_H_  //���̃}�N����`������ĂȂ�������
#define _OBJECT_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_OBJECT  (4096)  //�I�u�W�F�N�g�̐�
#define PRIORITY       (8)  //�I�u�W�F�N�g�̐�

//�I�u�W�F�N�g�N���X
class CObject
{
public:

	//�^�C�v���
	typedef enum
	{
		TYPE_NONE = 0,  //�Ȃ�
		TYPE_PLAYER,  //�v���C���[
		TYPE_ENEMY,  //�G
		TYPE_BG,  //�w�i
		TYPE_BULLET,  //�e
		TYPE_EXPLOSION,  //����
		TYPE_EFFECT,  //�G�t�F�N�g
		TYPE_BLOCK,  //�u���b�N
		TYPE_ITEM,  //�A�C�e��
		TYPE_BILLBOARD,  //�r���{�[�h
		TYPE_MODEL,  //���f��
		TYPE_LIFE,  //���C�t
		TYPE_GAUGE,  //�Q�[�W
		TYPE_MAX
	}TYPE;

	//��ԊǗ�
	typedef enum
	{
		STATE_APPEAR = 0,  //�o�����(�_��)
		STATE_NORMAL,  //�ʏ���
		STATE_DAMAGE,  //�_���[�W���
		STATE_WAIT,  //�o���҂�
		STATE_DEATH,  //���S���
		STATE_MAX
	}STATE;

	CObject(int nPriority = 3);  //�R���X�g���N�^
	virtual ~CObject();  //�f�X�g���N�^

	//�������z�֐�
	virtual HRESULT Init(void) = 0;  //����������
	virtual void Uninit(void) = 0;	   //�I������
	virtual void Update(void) = 0;	   //�X�V����
	virtual void Draw(void) = 0;	   //�`�揈��

	//�ݒ�(���z�֐�)
	virtual void SetPosition(D3DXVECTOR3 pos) = 0;        //�ʒu�̐ݒ�
	virtual void SetPositionOld(D3DXVECTOR3 posOld) = 0;  //�ߋ��̈ʒu�̐ݒ�
	virtual void SetMove(D3DXVECTOR3 move) = 0;           //�ړ��ʂ̐ݒ�
	virtual void SetRotation(D3DXVECTOR3 rot) = 0;        //�����̐ݒ�
	virtual void SetScale(D3DXVECTOR3 scale) = 0;         //�g�嗦�̐ݒ菈��
	virtual void SetSize(D3DXVECTOR3 size) = 0;           //�T�C�Y�̐ݒ�

	//�擾(���z�֐�)
	virtual D3DXVECTOR3 GetPosition(void) = 0;     //�ʒu�̎擾
	virtual D3DXVECTOR3 GetPositionOld(void) = 0;  //�ߋ��̈ʒu�̎擾
	virtual D3DXVECTOR3 GetMove(void) = 0;         //�ړ��ʂ̎擾
	virtual D3DXVECTOR3 GetRotation(void) = 0;     //�����̎擾
	virtual D3DXVECTOR3 GetScale(void) = 0;        //�g�嗦�̎擾
	virtual D3DXVECTOR3 GetSize(void) = 0;         //�T�C�Y�̎擾

	//�����o�ϐ�
	static void ReleaseAll(void);  //�S�폜����
	static void UpdateAll(void);   //�S�X�V����
	static void DrawAll(void);	   //�S�`�揈��

	//�擾
	TYPE GetType(void) { return m_type; };  //�^�C�v�擾
	static CObject *GetObject(int nPriority, int nIdx);  //�I�u�W�F�N�g�擾
	STATE GetState(void) { return m_state; };  //��Ԃ̎擾

	//�ݒ�
	void SetType(const TYPE type);  //�^�C�v�ݒ�
	void SetState(const STATE state, int nCounterState);  //��ԊǗ��ݒ�
	void UpdateState(void);  //��ԍX�V

protected:
	void Release(void);

private:
	static CObject *m_apObject[PRIORITY][MAX_OBJECT];  //�I�u�W�F�N�g�N���X�̃|�C���^
	static int m_nNumAll;                              //�I�u�W�F�N�g����
	int m_nlD;                                         //�������g��ID
	int m_nPriority;                                   //�D�揇�ʂ̈ʒu
	int m_nCounterState;                               //��ԊǗ��J�E���^�[
	TYPE m_type;                                       //�^�C�v���
	STATE m_state;                                     //��ԊǗ�
};

#endif 