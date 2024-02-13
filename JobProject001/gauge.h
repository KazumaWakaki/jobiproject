//=============================================================================
//
// [gauge.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _GAUGE_H_  //���̃}�N����`������Ȃ�������
#define _GAUGE_H_  //2�d�C���N���[�h�h�~�̃}�N����`

#include "object2D.h"
#include "player3D.h"

class CGauge;

//�Q�[�W�N���X
class CGauge : public CObject2D
{
public:
	//�Q�[�W�^�C�v���
	typedef enum
	{
		GAUGETYPE_STEP = 0,  //�X�e�b�v�Q�[�W
		GAUGETYPE_S,  //�X�e�b�v�Q�[�W�g
		GAUGETYPE_MAX
	}GAUGETYPE;

	//�e�N�X�`���^�C�v���
	typedef enum
	{
		TYPE_STEPFRAME = 0,  //�X�e�b�v�Q�[�W�g
		TYPE_STEPGAUGE_GREEN,  //�X�e�b�v�Q�[�W��
		TYPE_STEPGAUGE_ORANGE,  //�X�e�b�v�Q�[�W�I�����W
		TYPE_STEPGAUGE_RED,  //�X�e�b�v�Q�[�W��
		TYPE_MAX
	}TEXTYPE;

	CGauge();   //�R���X�g���N�^
	~CGauge();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);  //�I������
	void Update(void);  //�X�V����
	void Draw(void);  //�`�揈��
	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //�Q�[�W����

	//�擾
	D3DXVECTOR3 GetStepGauge(void) { return m_nStepGauge; };  //�X�e�b�v�Q�[�W�̒i�K�擾

	//�ݒ�
	void SetStepGauge(D3DXVECTOR3 StepGauge);

private:
	int m_nID;  //�ԍ�
	D3DXVECTOR3 m_nStepGauge;  //�X�e�b�v�Q�[�W
	int m_nIdxTexture[TYPE_MAX];  //�e�N�X�`��
	static CGauge *m_apObject;  //�I�u�W�F�N�g�N���X�̃|�C���^
};

#endif