//=============================================================================
//
// ���C���֐� [main.cpp]
// Author ��� ��^
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "object.h"
#include "manager.h"
#include "input.h"

//�}�N����`
#define CLASS_NAME  "WindowClass"     //�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "�A������"  //�E�B���h�E�̖��O
#define ID_BUTTON_FINISH (101)        //�I���{�^����ID

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LPDIRECT3DDEVICE9 m_pD3DDevice = NULL;;
LPD3DXFONT g_pFont = NULL;               //�t�H���g�ւ̃|�C���^
LPDIRECT3DDEVICE9 GetDevice(void);
void DrawFPS(void);

//�O���[�o���ϐ��錾
int g_nCountFPS = 0;                     //FPS�J�E���^

//-------------------------------------------------------
//���C���֐�
//-------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdshow)
{
	DWORD dwCurrentTime;  //���ݎ���
	DWORD dwExecLastTime; //�Ō�ɏ�����������
	DWORD dwFrameCount;   //�t���[���J�E���g
	DWORD dwFPSLastTime;  //�Ō��FPS��

	dwCurrentTime = 0;               //����������
	dwExecLastTime = timeGetTime();  //���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &g_pFont);

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),             //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                     //�E�B���h�E�̃X�^�C��
		WindowProc,                     //�E�B���h�E�v���V�[�W��
		0,                              //0�ɂ���
		0,                              //0�ɂ���
		hInstance,                      //�C���X�^���X�n���h��
		LoadIcon(NULL,IDC_ARROW),	    //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),     //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),     //�N���C�A���g�̈�̔w�i�F
		NULL,                           //���j���[�o�[
		CLASS_NAME,                     //�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)
	};

	HWND hWnd;  //�E�B���h�E�n���h��
	MSG msg;    //���b�Z�[�W���i�[����ϐ�

	//�E�B���h�E�N���X�̔��^
	RegisterClassEx(&wcex);

	//�E�B���h�E�𐶐�
	hWnd = CreateWindowEx
	(
		0,
		CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,        //�E�B���h�E�̍���X���W
		CW_USEDEFAULT,        //�E�B���h�E�̍���Y���W
		SCREEN_WIDTH,         //��
		SCREEN_HEIGHT,        //����
		NULL,                 //�e�E�B���h�E�̃n���h��
		NULL,                 //���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,            //�C���X�^���X�n���h��
		NULL
	);

	//pManager��NULL����Ȃ���
	if (CManager::GetInstance() != NULL)
	{
		//���������������s�����ꍇ
		if (FAILED(CManager::GetInstance()->Init(hInstance, hWnd, TRUE)))
		{
			return -1;
		}
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdshow);  //�E�B���h�E�̕\����Ԃ�ݒ�
	UpdateWindow(hWnd);          //�N���C�A���g�̈���X�V

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			//windows�̏���
			if (msg.message == WM_QUIT)
			{
				//WM_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v���ʂ���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg); //���z�L�[���b�Z�[�W�𕶎��֕ϊ�
				DispatchMessage(&msg);
			}
		}

		else
		{
			//DirectX�̏���
			dwCurrentTime = timeGetTime();       //���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;                //�t���[���J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				//60����1�b�o��
				dwExecLastTime = dwCurrentTime;  //�����J�n�̎���[���ݎ���]��ۑ�

				//�}�l�[�W���̍X�V����
				CManager::GetInstance()->Update(hInstance, hWnd, TRUE);

				//�}�l�[�W���̕`�揈��
				CManager::GetInstance()->Draw();

				//FPS�̕\��
				DrawFPS();

				dwFrameCount++;    //�t���[���J�E���g�����Z
			}
		}
	}

	//�}�l�[�W���̔j��
	if (CManager::GetInstance() != NULL)
	{
		//�}�l�[�W���̏I������
		CManager::GetInstance()->Uninit();

		delete CManager::GetInstance();

		CManager::Release();
	}

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}
//-------------------------------------------------------
//�E�B���h�E�v���V�[�W��
//-------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	switch (uMsg)
	{
	case WM_DESTROY:  //�E�B���h�E�j���̃��b�Z�[�W

		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:  //�L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE:  //[ESC]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);  //�I�����b�Z�[�W

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}

			else
			{
				return 0;  //0��Ԃ��Ȃ��ƏI�����Ă��܂�
			}

			break;
		}

		break;

	case WM_CLOSE:  //����{�^�������̃��b�Z�[�W

		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		//�͂���I�������ꍇ
		if (nID == IDYES)
		{
			//�E�B���h�E��j������
			DestroyWindow(hWnd);
		}

		else
		{
			return 0;  //0��Ԃ��Ȃ��ƏI�����Ă��܂�
		}

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//==================================================================================
//FPS�̕\��
//==================================================================================
void DrawFPS(void)
{
	//RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//char aStr[256];

	////������ɑ��
	//wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);

	////�e�L�X�g�̕`��
	//g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}
//==================================================================================
//�f�o�C�X�̎擾
//==================================================================================
LPDIRECT3DDEVICE9  GetDevice(void)
{
	return m_pD3DDevice;
}
