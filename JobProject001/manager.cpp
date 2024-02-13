//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author 若木 一真
//
//=============================================================================
#include "manager.h"
#include "title.h"
#include "game.h"
#include"result.h"

//静的メンバ変数
CManager *CManager::pManager = NULL;

//===================================================================================================
// シーンの処理
//===================================================================================================
//-------------------------------------------------------
//シーンのコンストラクタ
//-------------------------------------------------------
CScene::CScene()
{

}
//-------------------------------------------------------
//シーンのデストラクタ
//-------------------------------------------------------
CScene::~CScene()
{

}
//-------------------------------------------------------
//シーンの初期化処理
//-------------------------------------------------------
HRESULT CScene::Init(void)
{
	return (S_OK);
}
//-------------------------------------------------------
//シーンの終了処理
//-------------------------------------------------------
void CScene::Uninit(void)
{
	Release();  //削除処理
}
//-------------------------------------------------------
//シーンの更新処理
//-------------------------------------------------------
void CScene::Update(void)
{

}
//-------------------------------------------------------
//シーンの描画処理
//-------------------------------------------------------
void CScene::Draw(void)
{

}
//-------------------------------------------------------
//シーンの生成
//-------------------------------------------------------
CScene *CScene::Create(MODE mode)
{
	CScene *pScene = NULL;

	switch (mode)
	{
	case MODE_TITLE:

		pScene = new CTitle;  //タイトルシーンの生成

		break;

	case MODE_GAME:

		pScene = new CGame;  //ゲームシーンの生成

		break;

	case MODE_RESULT:

		pScene = new CResult;  //リザルトシーンの生成

		break;
	}

	pScene->m_mode = mode;  //モードを入れる

	if (pScene != NULL)
	{
		pScene->Init();  //初期化処理
	}

	//生成に失敗した場合
	else
	{
		return NULL;
	}

	return pScene;
}
//-------------------------------------------------------
//モードの取得
//-------------------------------------------------------
//CScene::MODE CScene::GetMode(void)
//{
//	//現在のモードを返す
//
//}
//-------------------------------------------------------
//位置の設定処理
//-------------------------------------------------------
void CScene::SetPosition(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//-------------------------------------------------------
//過去の位置の設定処理
//-------------------------------------------------------
void CScene::SetPositionOld(const D3DXVECTOR3 posOld)
{
	m_posOld = posOld;
}
//-------------------------------------------------------
//移動量の設定処理
//-------------------------------------------------------
void CScene::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CScene::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//-------------------------------------------------------
//拡大率の設定処理
//-------------------------------------------------------
void CScene::SetScale(const D3DXVECTOR3 scale)
{
	m_scale = scale;
}
//-------------------------------------------------------
//サイズの設定処理
//-------------------------------------------------------
void CScene::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}
//===================================================================================================
// マネージャーの処理
//===================================================================================================
//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CManager::CManager()
{

}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CManager::~CManager()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	/////////////////////////////////
	//レンダラーの生成
	/////////////////////////////////
	m_pRenderer = NULL;

	//m_pRendererがNULLの時
	if (m_pRenderer == NULL)
	{
		//レンダラーのメモリ確保
		m_pRenderer = new CRenderer;
	}

	//レンダラーの初期化処理
	m_pRenderer->Init(hWnd, TRUE);

	/////////////////////////////////
	//キーボードの生成
	/////////////////////////////////
	m_pInputKeyboard = NULL;

	//m_pInputKeyboardがNULLの時
	if (m_pInputKeyboard == NULL)
	{
		//キーボードのメモリ確保
		m_pInputKeyboard = new CInputKeyboard;
	}

	//キーボードの初期化処理
	m_pInputKeyboard->Init(hInstance, hWnd);

	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	/////////////////////////////////
	//ゲームパッドの生成
	/////////////////////////////////
	m_pInputPad = NULL;

	//m_pInputPadがNULLの時
	if (m_pInputPad == NULL)
	{
		//ゲームパッドのメモリ確保
		m_pInputPad = new CInputPad;
	}

	//ゲームパッドの初期化処理
	m_pInputPad->Init();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInputPad();

	/////////////////////////////////
	//サウンドの生成
	/////////////////////////////////
	m_pSound = NULL;

	//m_pRendererがNULLの時
	if (m_pSound == NULL)
	{
		//サウンドのメモリ確保
		m_pSound = new CSound;
	}

	//サウンドの初期化処理
	m_pSound->Init(hWnd);

	/////////////////////////////////
	//カメラの生成
	/////////////////////////////////
	m_pCamera = NULL;

	//m_pCameraがNULLの時
	if (m_pCamera == NULL)
	{
		//カメラのメモリ確保
		m_pCamera = new CCamera;
	}

	//カメラの初期化処理
	m_pCamera->Init();

	/////////////////////////////////
	//ライトの生成
	/////////////////////////////////
	m_pLight = NULL;

	//m_pLightがNULLの時
	if (m_pLight == NULL)
	{
		//ライトのメモリ確保
		m_pLight = new CLight;
	}

	//ライトの初期化処理
	m_pLight->Init();

	/////////////////////////////////
	//デバッグ表示の生成
	/////////////////////////////////
	m_pDebugProc = NULL;

	//m_pDebugProcがNULLの時
	if (m_pDebugProc == NULL)
	{
		//デバッグ表示のメモリ確保
		m_pDebugProc = new CDebugProc;

		//デバッグ表示の初期化処理
		m_pDebugProc->Init();
	}

	/////////////////////////////////
	//テクスチャの生成
	/////////////////////////////////
	m_pTexture = NULL;

	//m_pTextureがNULLの時
	if (m_pTexture == NULL)
	{
		//テクスチャのメモリ確保
		m_pTexture = new CTexture;

		//テクスチャの読み込み
		CTexture::Load();
	}

	/////////////////////////////////
	//モデルの生成
	/////////////////////////////////
	m_pModel = NULL;

	//m_pModelがNULLの時
	if (m_pModel == NULL)
	{
		//モデルのメモリ確保
		m_pModel = new CModel;

		//モデルの読み込み
		CModel::Load();
	}

	//モード設定(タイトルに移行)
	SetMode(CScene::MODE_TITLE);

#if _DEBUG

	//モード設定(タイトルに移行)
	SetMode(CScene::MODE_GAME);

#endif

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CManager::Uninit(void)
{
	//全てのオブジェクトを破棄
	CObject::ReleaseAll();

	//キーボードの終了処理
	m_pInputKeyboard->Uninit();
	m_pInputKeyboard = NULL;

	//ゲームパッドの終了処理
	m_pInputPad->Uninit();
	m_pInputPad = NULL;

	//レンダラーの終了処理
	m_pRenderer->Uninit();
	m_pRenderer = NULL;

	//サウンドの終了処理
	m_pSound->Uninit();
	m_pSound = NULL;

	//カメラの終了処理
	m_pCamera->Uninit();
	m_pCamera = NULL;

	//ライトの終了処理
	m_pLight->Uninit();
	m_pLight = NULL;

	//デバッグ表示の終了処理
	m_pDebugProc->Uninit();
	m_pDebugProc = NULL;

	//テクスチャの終了処理
	m_pTexture->Unload();
	m_pTexture = NULL;

	//モデルの終了処理
	m_pModel->Unload();
	m_pModel = NULL;
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
HRESULT CManager::Update(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//キーボードの更新処理
	m_pInputKeyboard->Update();

	//ゲームパッドの更新処理
	m_pInputPad->Update();

	//レンダラーの更新処理
	m_pRenderer->Update();

	//カメラの更新処理
	m_pCamera->Update();

	//ライトの更新処理
	m_pLight->Update();

	//デバッグ表示の更新処理
	m_pDebugProc->Update();

	return (S_OK);
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CManager::Draw(void)
{
	//レンダラーの描画処理
	m_pRenderer->Draw();
}
//-------------------------------------------------------
//モードの設定
//-------------------------------------------------------
void CManager::SetMode(CScene::MODE mode)
{
	//現在のモードの破棄
	if (GetInstance()->m_pScene != NULL)
	{
		GetInstance()->m_pScene->Uninit();

		GetInstance()->m_pScene = NULL;  //使用していない状態にする
	}

	CObject::ReleaseAll();  //全削除処理

	//新しいモードの生成
	if (GetInstance()->m_pScene == NULL)
	{
		GetInstance()->m_pScene = CScene::Create(mode);
	}

	//フェードの生成
	//if (m_pFade == NULL)
	//{
	//	m_pFade = CFade::Create(mode);
	//}	
}
//-------------------------------------------------------
//フェイド処理
//-------------------------------------------------------
void CManager::UpdateFade(void)
{
	//フェードの生成
	//if (m_pFade == NULL)
	//{
	//	m_pFade->Update();
	//}
}
//-------------------------------------------------------
//インスタンス取得処理
//-------------------------------------------------------
CManager *CManager::GetInstance(void)
{
	if (pManager == NULL)
	{
		return pManager = new CManager;
	}

	else
	{
		return pManager;
	}
}
//-------------------------------------------------------
//削除処理
//-------------------------------------------------------
HRESULT CManager::Release(void)
{
	if (pManager == NULL)
	{

	}

	else if (pManager != NULL)
	{
		//全てのオブジェクトを破棄
		CObject::ReleaseAll();
	}

	return (S_OK);
}