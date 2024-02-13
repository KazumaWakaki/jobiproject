//=============================================================================
//
// [manager.h]
// Author ��� ��^
//
//=============================================================================
#ifndef _MANAGER_H_  //���̃}�N����`������ĂȂ�������
#define _MANAGER_H_  //2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "texture.h"
#include "model.h"
#include "object.h"
#include "debugproc.h"

//�O���錾
class CDebugProc;

//�V�[���N���X
class CScene : CObject
{
public:
	typedef enum
	{
		MODE_TITLE = 0,   //�^�C�g�����
		MODE_GAME,        //�Q�[�����
		MODE_RESULT,      //���U���g���
		MODE_MAX
	}MODE;

	CScene();   //�R���X�g���N�^
	~CScene();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(void);  //����������
	void Uninit(void);	 //�I������
	void Update(void);   //�X�V����
	void Draw(void);	 //�`�揈��
	static CScene *Create(MODE mode);

	//�擾
	D3DXVECTOR3 GetPosition(void) { return m_pos; };        //�ʒu�̎擾
	D3DXVECTOR3 GetPositionOld(void) { return m_posOld; };  //�ߋ��̈ʒu�̎擾
	D3DXVECTOR3 GetMove(void) { return m_move; };           //�ړ��ʂ̎擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; };        //�����̎擾
	D3DXVECTOR3 GetScale(void) { return m_scale; };         //�g�嗦�̎擾
	D3DXVECTOR3 GetSize(void) { return m_size; };           //�T�C�Y�̎擾

	//�ݒ�
	void SetPosition(D3DXVECTOR3 pos);            //�ʒu�̐ݒ菈��
	void SetPositionOld(D3DXVECTOR3 posOld);      //�ߋ��̈ʒu�̐ݒ菈��
	void SetMove(D3DXVECTOR3 move);               //�ړ��ʂ̐ݒ菈��
	void SetRotation(D3DXVECTOR3 rot);            //�����̐ݒ菈��
	void SetScale(D3DXVECTOR3 scale);             //�g�嗦�̐ݒ菈��
	void SetSize(D3DXVECTOR3 size);               //�T�C�Y�̐ݒ菈��
	void SetMode(MODE mode) { m_mode = mode; }

private:
	MODE m_mode;  //���[�h
	D3DXVECTOR3 m_pos;    //�ʒu
	D3DXVECTOR3 m_posOld; //�ߋ��̈ʒu
	D3DXVECTOR3 m_move;   //�ړ���
	D3DXVECTOR3 m_rot;    //��]��
	D3DXVECTOR3 m_scale;  //�g�嗦
	D3DXVECTOR3 m_size;   //�T�C�Y��
	float m_fWidth;		  //��
	float m_fHeight;	  //����
};

//�}�l�[�W���N���X
class CManager
{
public:
	CManager();   //�R���X�g���N�^
	~CManager();  //�f�X�g���N�^

	//�����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //����������
	void Uninit(void);  //�I������
	HRESULT Update(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);  //�X�V����
	void Draw(void);  //�`�揈��

	//�擾
	CRenderer *GetRenderer(void) { return m_pRenderer; };  //�����_���[�̐�������
	CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; };  //�L�[�{�[�h�̐�������
	CInputPad *GetInputPad(void) { return m_pInputPad; };  //�Q�[���p�b�h�̐�������
	CSound *CManager::GetSound(void) { return m_pSound; };  //�T�E���h�̐�������
	CCamera *CManager::GetCamera(void) { return m_pCamera; };  //�J�����̐�������
	CLight *CManager::GetLight(void) { return m_pLight; };  //���C�g�̐�������
	CDebugProc *GetDebugProc(void) { return m_pDebugProc; };  //�f�o�b�O�\���̎擾
	CTexture *GetTexture(void) { return m_pTexture; };  //�e�N�X�`���̎擾
	CModel *GetModel(void) { return m_pModel; };  //���f���̎擾
	static CManager *GetInstance(void);  //�C���X�^���X�̎擾
	static HRESULT Release(void);

	//�V�[��
	static void SetMode(CScene::MODE mode);  //���[�h�̐ݒ�
	CScene *GetScene(void) { return m_pScene; }  //�V�[���̎擾
	static void UpdateFade(void);  //�t�F�C�h�̍X�V����

private:
	CRenderer *m_pRenderer;  //�����_���[�̃|�C���^
	CInputKeyboard *m_pInputKeyboard;  //�L�[�{�[�h�̃|�C���^
	CInputPad *m_pInputPad;  //�Q�[���p�b�h�̃|�C���^
	CSound *m_pSound;  //���̃|�C���^
	CCamera *m_pCamera;  //�J�����̃|�C���^
	CLight *m_pLight;  //���C�g�̃|�C���^
	CDebugProc *m_pDebugProc;  //�f�o�b�O�\���̃|�C���^
	CTexture *m_pTexture;  //�e�N�X�`���̃|�C���^
	CModel *m_pModel;  //���f���̃|�C���^
	CScene *m_pScene;  //�V�[���̃|�C���^
	static CManager *pManager;  //�}�l�[�W���[�̃|�C���^
};
#endif