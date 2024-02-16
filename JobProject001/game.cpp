//=======================================================
//
// ゲーム処理 [game.cpp]
// Author 若木一真
//
//=======================================================
#include "game.h"
#include "modelset.h"
#include "player3D.h"
#include "enemy3D.h"
#include "block3D.h"
#include "wall.h"
#include "life.h"

//マクロ定義
#define WALL_MAX  (9)  //背景壁の数値
#define START_TIME	(420)	//制限時間

//静的メンバ変数
CGame *CGame::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CGame::CGame()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}

	//m_pTime = NULL;
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CGame::~CGame()
{

}
//-------------------------------------------------------
//ゲーム画面の初期化処理
//-------------------------------------------------------
HRESULT CGame::Init(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//シーンの初期化処理
	CScene::Init();

	//カメラの取得
	CCamera *pCamera;
	pCamera = CManager::GetInstance()->GetCamera();

	//カメラの初期化
	pCamera->Init();

	//---------------------------------------------------------------
	//壁の生成
	CWall::Create(D3DXVECTOR3(200.0f, 150.0f, 2000.0f), D3DXVECTOR3(0.0f, -1.57f, 0.0f), D3DXVECTOR3(10000.0f, 400.0f, 0.0f), CWall::TYPE_WALL001);
	CWall::Create(D3DXVECTOR3(-200.0f, 150.0f, 2000.0f), D3DXVECTOR3(0.0f, 1.57f, 0.0f), D3DXVECTOR3(10000.0f, 400.0f, 0.0f), CWall::TYPE_WALL001);

	//---------------------------------------------------------------
	//ブロックの配置
	//---------------------------------------------------------------
	//チュートリアル
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, -5000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 30.0f), CBlock3D::BLOCK_NEONFLOOR);  //チュートリアル用土台
	CBlock3D::Create(D3DXVECTOR3(0.0f, 60.0f, -3500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 4.0f, 20.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, -2500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 20.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 2.0f, 40.0f), CBlock3D::BLOCK_NEONFLOOR);

	//---------------------------------------------------------------
	//一段階
	CBlock3D::Create(D3DXVECTOR3(300.0f, 0.0f, 2300.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.0f, 2.0f, 20.0f),  CBlock3D::BLOCK_NEONFLOOR);  //1個目の土台
	CBlock3D::Create(D3DXVECTOR3(600.0f, 0.0f, 1720.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.1f), CBlock3D::BLOCK_NEON);  //壁
	CBlock3D::Create(D3DXVECTOR3(00.0f, 0.0f, 2820.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 0.1f), CBlock3D::BLOCK_NEON);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, 6500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 2.0f, 40.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(0.0f, 0.0f, 14500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 2.0f, 40.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(-500.0f, 200.0f, 19000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 2.0f, 20.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(-500.0f, 400.0f, 24000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 2.0f, 20.0f), CBlock3D::BLOCK_NEONFLOOR);

	//---------------------------------------------------------------
	//ボス前
	CBlock3D::Create(D3DXVECTOR3(-500.0f, -700.0f, 26500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 40.0f, 50.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(-1400.0f, 500.0f, 26500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 50.0f), CBlock3D::BLOCK_NEONFLOOR);
	CBlock3D::Create(D3DXVECTOR3(600.0f, 500.0f, 26500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(20.0f, 40.0f, 50.0f), CBlock3D::BLOCK_NEONFLOOR);

	//---------------------------------------------------------------
	//ボスの土台
	CBlock3D::Create(D3DXVECTOR3(-500.0f, 0.0f, 30000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 2.0f, 70.0f), CBlock3D::BLOCK_NEONFLOOR);

	//---------------------------------------------------------------
	//壁走り
	CBlock3D::Create(D3DXVECTOR3(1400.0f, 50.0f, 4000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 2.0f, 3.0f), CBlock3D::BLOCK_NEONWALL);
	CBlock3D::Create(D3DXVECTOR3(-1400.0f, 50.0f, 9000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.7f, 2.0f, 3.0f), CBlock3D::BLOCK_NEONWALL);
	CBlock3D::Create(D3DXVECTOR3(600.0f, 200.0f, 11000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.9f, 2.0f, 3.0f), CBlock3D::BLOCK_NEONWALL);
	CBlock3D::Create(D3DXVECTOR3(1000.0f, 200.0f, 17000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.9f, 2.0f, 3.0f), CBlock3D::BLOCK_NEONWALL);
	CBlock3D::Create(D3DXVECTOR3(-2000.0f, 300.0f, 21000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.9f, 2.0f, 3.0f), CBlock3D::BLOCK_NEONWALL);

	//---------------------------------------------------------------
	//モデルの生成
	//---------------------------------------------------------------
	//チェックポイント
	CModelSet::Create(D3DXVECTOR3(0.0f, -100.0f, -5400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);  //チュートリアル用

	CModelSet::Create(D3DXVECTOR3(0.0f, 0.0f, 120.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(-300.0f, 0.0f, 1700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(0.0f, 100.0f, 6000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(0.0f, 0.0f, 7000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);
	CModelSet::Create(D3DXVECTOR3(-300.0f, 100.0f, 13500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(30.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);

	CModelSet::Create(D3DXVECTOR3(-340.0f, 450.0f, 24000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(10.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_CHECKPOINT);

	//---------------------------------------------------------------
	//敵3Dの生成
	CEnemy3D::Create(D3DXVECTOR3(0.0f, 70.0f, 700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_TUTORIAL_ENE, 10000);
	CEnemy3D::Create(D3DXVECTOR3(1000.0f, 100.0f, 2400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(500.0f, 100.0f, 4700.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(0.0f, 100.0f, 7540.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(750.0f, 100.0f, 15000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(-800.0f, 100.0f, 15000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);
	CEnemy3D::Create(D3DXVECTOR3(-770.0f, 300.0f, 19000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_USUALLY, 200);

	//---------------------------------------------------------------
	//ボス
	//CEnemy3D::Create(D3DXVECTOR3(-500.0f, 80.0f, 32500.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.5f, 0.5f, 0.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy3D::TYPE_BOSS, 2000);

	//---------------------------------------------------------------
	//プレイヤー3Dの生成
	CPlayer3D::Create(D3DXVECTOR3(0.0f, 1000.0f, 24000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.3f, 0.3f, 0.3f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//BGMの再生
	pSound->PlaySound(SOUND_LABEL_BGM_GAME);

	return (S_OK);
}
//-------------------------------------------------------
//ゲーム画面の終了処理
//-------------------------------------------------------
void CGame::Uninit(void)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	//BGMの再生
	pSound->StopSound();

	//シーンの終了処理
	CScene::Uninit();

	if (m_apObject != NULL)
	{
		m_apObject = NULL;
	}
}
//-------------------------------------------------------
//ゲーム画面の更新処理
//-------------------------------------------------------
void CGame::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

//#if _DEBUG

	if (pInputKeyboard->GetTrigger(DIK_R) == true)  //ENTERキーが押された
	{
		//モード設定(リザルトに移行)
		CManager::SetMode(MODE_RESULT);
		//CManager::GetFade()->Set(CScene::MODE_RESULT);

		////サウンドの再生
		//PlaySound(SOUND_LABEL_SE_NEXT);
	}

//#endif

	switch (m_gameState)
	{
	case GAMESTATE_NORMAL:  //通常状態
		break;

	case GAMESTATE_RESET:  //リセット状態

		m_nCounterGameState++;

		if (m_nCounterGameState >= 10)
		{
			m_nCounterGameState = 0;
			m_gameState = GAMESTATE_NORMAL;  //通常状態に設定
		}

		break;

	case GAMESTATE_END:  //終了状態

		m_nCounterGameState--;

		if (m_nCounterGameState <= 0)
		{
			m_gameState = GAMESTATE_NONE;  //何もしていない状態に設定

			//モード設定(リザルトに移行)
			CManager::SetMode(MODE_RESULT);
			//CManager::GetFade()->Set(CScene::MODE_RESULT);

			////モード設定(リザルト画面に移行)
			//SetFade(MODE_RESULT);
		}

		break;
	}
}
//-------------------------------------------------------
//ゲーム画面の描画処理
//-------------------------------------------------------
void CGame::Draw(void)
{
	//シーンの描画処理
	CScene::Draw();
}
//-------------------------------------------------------
//ゲームの状態の設定
//-------------------------------------------------------
void CGame::SetGameState(GAMESTATE state, int nCounter)
{
	if (m_apObject != NULL)
	{
		m_apObject->m_gameState = state;
		m_apObject->m_nCounterGameState = nCounter;
	}
}
//-------------------------------------------------------
//ゲームのポーズ状態の取得
//-------------------------------------------------------
void CGame::SetEnablePause(bool Pause)
{
	m_bPause = Pause;
}
//-------------------------------------------------------
// タイマーの取得
//-------------------------------------------------------
//CTime *CGame::GetTime(void)
//{
//	return m_pTime;
//}