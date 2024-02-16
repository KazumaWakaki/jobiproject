//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author 若木 一真
//
//=============================================================================
#include "camera.h"
#include "manager.h"
#include "player3D.h"

//マクロ定義
#define MOVE_SPEED  (3.0f)  //移動スピード
#define ROLL_SPEED  (0.03f)  //回転スピード
#define ROLLDIG_SPEED  (0.02f)  //斜めの回転スピード
#define ROLL_X  (0.5f)  //X軸の最大向き

//静的メンバ変数
CCamera *CCamera::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CCamera::CCamera()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CCamera::~CCamera()
{

}
//=======================================================
//カメラの初期化処理
//=======================================================
HRESULT CCamera::Init(void)
{
	//ローカル変数宣言
	D3DXVECTOR3 StartRot;

	//値の初期化
	m_posV = D3DXVECTOR3(0.0f, 160.0f, 0.0f);
	m_posR = D3DXVECTOR3(0.0f, 150.0f, 100.0f);
	m_vecU = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	fLength = 90.0f;  //Y面の視点から注視点までの距離

	//PRIORITY分回す
	for (int nCntPriority = 0; nCntPriority < PRIORITY; nCntPriority++)
	{
		//MAX_OBJECT分回す
		for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
		{
			CObject *pObj;  //オブジェクトクラスのポインタ

			//オブジェクトを取得
			pObj = CObject::GetObject(nCntPriority, nCntObj);

			//pObjがNULLじゃなかった時
			if (pObj != NULL)
			{
				CObject::TYPE type;  //種類

				//種類を取得
				type = pObj->GetType();

				//種類がプレイヤーの場合
				if (type == CObject::TYPE_PLAYER)
				{
					//初期位置をプレイヤーの後方に設定する
					StartRot = -pObj->GetRotation();

					//目標位置まで移動する
					m_posV.x = StartRot.y + (-D3DX_PI * 0.5f);
				}
			}
		}
	}

	return (S_OK);
}
//=======================================================
//カメラの終了処理
//=======================================================
void CCamera::Uninit(void)
{
	m_apObject = NULL;
}
//=======================================================
//カメラの更新処理
//=======================================================
void CCamera::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInstance()->GetInputPad();

	/////////////////////////////////
	//視点回転
	/////////////////////////////////
	//左に視点を向ける
	if (pInputKeyboard->GetPress(DIK_J) == true
		|| pInputPad->CInputPad::GetJoyStickRX(0) < 0)
	{
		//左上移動
		if (pInputKeyboard->GetPress(DIK_I) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) > 0)
		{
			m_rot.y -= ROLLDIG_SPEED;
			m_rot.x += ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		//左下移動
		else if (pInputKeyboard->GetPress(DIK_K) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) < 0)
		{
			m_rot.y -= ROLLDIG_SPEED;
			m_rot.x -= ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		else
		{
			m_rot.y -= ROLL_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}
	}

	//右に視点を向ける
	else if (pInputKeyboard->GetPress(DIK_L) == true
		|| pInputPad->CInputPad::GetJoyStickRX(0) > 0)
	{
		//右上移動
		if (pInputKeyboard->GetPress(DIK_I) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) > 0)
		{
			m_rot.y += ROLLDIG_SPEED;
			m_rot.x += ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		//右下移動
		else if (pInputKeyboard->GetPress(DIK_K) == true
			|| pInputPad->CInputPad::GetJoyStickRY(0) < 0)
		{
			m_rot.y += ROLLDIG_SPEED;
			m_rot.x -= ROLLDIG_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}

		else
		{
			m_rot.y += ROLL_SPEED;

			m_posR.x = m_posV.x + sinf(m_rot.y) * fLength;
			m_posR.z = m_posV.z + cosf(m_rot.y) * fLength;
		}
	}

	//上に視点を向ける
	else if (pInputKeyboard->GetPress(DIK_I) == true
		|| pInputPad->CInputPad::GetJoyStickRY(0) > 0)
	{
		m_rot.x += ROLL_SPEED;
	}

	//下に視点を向ける
	else if (pInputKeyboard->GetPress(DIK_K) == true
		|| pInputPad->CInputPad::GetJoyStickRY(0) < 0)
	{
		m_rot.x -= ROLL_SPEED;
	}

	//角度の補正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y += -D3DX_PI * 2;
	}

	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}

	//角度の補正
	if (m_rot.z > D3DX_PI)
	{
		m_rot.z += -D3DX_PI * 2;
	}

	if (m_rot.z < -D3DX_PI)
	{
		m_rot.z += D3DX_PI * 2;
	}

	if (m_rot.x > ROLL_X)
	{
		m_rot.x = ROLL_X;
	}

	if (m_rot.x < -ROLL_X)
	{
		m_rot.x = -ROLL_X;
	}

	//注視点を相対位置に設定
	//m_posR =
	//{
	//	m_posV.x + sinf(m_rot.y) * fLength,
	//	m_posV.y - 20,
	//	m_posV.z + cosf(m_rot.y) * fLength
	//};

	//m_posV.x = m_posR.x + sinf(m_rot.y) * -fLength;
	//m_posV.y = m_posR.y + 3.0f;
	//m_posV.z = m_posR.z + cosf(m_rot.y) * -fLength;

#if _DEBUG

	//m_posR.y = m_posV.y + 50.0f;

#endif

	m_posR.x = m_posV.x + sinf(m_rot.y) * cosf(m_rot.x) * fLength;
	m_posR.y = m_posV.y + sinf(m_rot.x) * fLength;
	m_posR.z = m_posV.z + cosf(m_rot.y) * cosf(m_rot.x) * fLength;

	SetPosV(m_posV);  //視点の設定
	SetPosR(m_posR);  //注視点の設定
	SetRotation(m_rot);  //向きの設定

	//-------------------------------------------------------
	//カメラのデバック表示
	//-------------------------------------------------------
	CManager::GetInstance()->GetDebugProc()->Print("カメラの視点 [%f, %f, %f]\n", m_posV.x, m_posV.y, m_posV.z);
	CManager::GetInstance()->GetDebugProc()->Print("カメラの注視点 [%f, %f, %f]\n", m_posR.x, m_posR.y, m_posR.z);
	CManager::GetInstance()->GetDebugProc()->Print("カメラの向き [%f, %f, %f]\n", m_rot.x, m_rot.y, m_rot.z);
}
//=======================================================
//カメラの設定処理
//=======================================================
void CCamera::SetCamera(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	//プロジェクションマトリックスを作成(透視投影)
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		1.0f,
		20000.0f);

	//プロジェクションマトリックスを設定(平行投影)
	//D3DXMatrixOrthoLH(&mtxProjection,
	//				  (float)SCREEN_WIDTH,
	//				  (float)SCREEN_HEIGHT,
	//				  1.0f,
	//				  1000.0f);

	//プロジェクションマトリックスの設定
	pDevice->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	//ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView,
					   &m_posV,
					   &m_posR,
					   &m_vecU);

	//ビューマトリックスの設定
	pDevice->SetTransform(D3DTS_VIEW, &mtxView);
}
//=======================================================
//カメラの追従処理
//=======================================================
void CCamera::MoveCamera(CPlayer3D *pPlayer)
{
	//pPlayerがNULLじゃなかった時
	if (pPlayer != NULL)
	{
		CObject::TYPE type;  //種類
	
		//種類を取得
		type = pPlayer->GetType();
	
		//種類がプレイヤーの場合
		if (type == CObject::TYPE_PLAYER)
		{
			D3DXVECTOR3 rot = m_apObject->GetRot();  //向き
			D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
			D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //プレイヤーの移動量の取得
			D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //プレイヤーの向きの取得
	
			///////////////////////////////////////////
			//視点
			///////////////////////////////////////////
			m_apObject->m_posV.x = posPlayer.x;
			m_apObject->m_posV.y = posPlayer.y + 150.0f;
			m_apObject->m_posV.z = posPlayer.z;

#if _DEBUG

			//m_apObject->m_posV.y = posPlayer.y + 200.0f;
			//m_apObject->m_posV.z = posPlayer.z - 300.0f;

#endif

			//注視点の目標位置を算出
			m_apObject->m_posRDest = D3DXVECTOR3
			(
				posPlayer.x - sinf(rotPlayer.y),
				posPlayer.y + sinf(rotPlayer.x),
				posPlayer.z - cosf(rotPlayer.y)
			);
			
			//注視点を補正
			D3DXVECTOR3 RDeff = D3DXVECTOR3
			(
				m_apObject->m_posRDest.x - m_apObject->m_posR.x,
				m_apObject->m_posRDest.y - m_apObject->m_posR.y,
				m_apObject->m_posRDest.z - m_apObject->m_posR.z
			);
	
			//慣性の付与
			//m_apObject->m_posR.x += RDeff.x * 0.05f;
			//m_apObject->m_posR.z += RDeff.z * 0.05f;

			//視点注視点間の距離を求める
			float fLength_X = sqrtf((m_apObject->m_posR.x * m_apObject->m_posR.x) + (m_apObject->m_posV.x *m_apObject->m_posV.x));
			float fLength_Y = sqrtf((m_apObject->m_posR.y * m_apObject->m_posR.y) + (m_apObject->m_posV.y *m_apObject->m_posV.y));
			float fLength_Z = sqrtf((m_apObject->m_posR.z * m_apObject->m_posR.z) + (m_apObject->m_posV.z * m_apObject->m_posV.z));
	
			//視点の目標位置を算出
			m_apObject->m_posVDest = D3DXVECTOR3
			(
				movePlayer.x - sinf(rotPlayer.x * fLength_X),
				movePlayer.y - cosf(rotPlayer.y * fLength_Y),
				movePlayer.z - cosf(rotPlayer.z * fLength_Z)
			);
	
			//視点を補正
			D3DXVECTOR3 VDeff = D3DXVECTOR3
			(
				m_apObject->m_posVDest.x - m_apObject->m_posV.x,
				m_apObject->m_posVDest.y - m_apObject->m_posV.y,
				m_apObject->m_posVDest.z - m_apObject->m_posV.z
			);
	
			//慣性の付与
			//m_apObject->m_posV += VDeff * 0.01f;

			//プレイヤーの向きをカメラと同じにする
			rotPlayer.y = rot.y + D3DX_PI;
			rotPlayer.x = rot.x - D3DX_PI;

			pPlayer->SetRotation(rotPlayer);
		}
	}
}
//=======================================================
//プレイヤー死亡時カメラの向きの処理
//=======================================================
void CCamera::PlayerTriggerCamera(CPlayer3D *pPlayer)
{
	//pPlayerがNULLじゃなかった時
	if (pPlayer != NULL)
	{
		CObject::TYPE type;  //種類

		//種類を取得
		type = pPlayer->GetType();

		//種類がプレイヤーの場合
		if (type == CObject::TYPE_PLAYER)
		{
			D3DXVECTOR3 rot = m_apObject->GetRot();  //向き
			int PlaRes = pPlayer->GetStateRes();  //プレイヤーのリスポーン状態取得

			//プレイヤーのリスポーン状態が待機のとき
			if (pPlayer->GetStateRes() == pPlayer->STATERES_RESPAWN)
			{
				rot.y = 0.0f;  //カメラの向きを初期化する
			}

			//カメラの向きの設定
			m_apObject->SetRotation(rot);
		}
	}
}
//=======================================================
//プレイヤーが壁走りしているときの処理
//=======================================================
void CCamera::PlayerWallRunCamera(CPlayer3D *pPlayer)
{
	//pPlayerがNULLじゃなかった時
	if (pPlayer != NULL)
	{
		CObject::TYPE type;  //種類

		//種類を取得
		type = pPlayer->GetType();

		//種類がプレイヤーの場合
		if (type == CObject::TYPE_PLAYER)
		{
			D3DXVECTOR3 rot = m_apObject->GetRot();  //向き
			int PlaJamp = pPlayer->GetJamp();  //プレイヤーのジャンプ状態取得

			////プレイヤーの壁走り状態が右からとき
			//if (PlaJamp == pPlayer->PLAYERJUMP_WALLRUN_R)
			//{
			//	rot.z = 1.2f;  //カメラの向きを初期化する
			//}

			////プレイヤーの壁走り状態が左からとき
			//if (PlaJamp == pPlayer->PLAYERJUMP_WALLRUN_L)
			//{
			//	rot.x = -1.2f;  //カメラの向きを初期化する
			//}

			//カメラの向きの設定
			m_apObject->SetRotation(rot);
		}
	}
}
//-------------------------------------------------------
//視点の設定処理
//-------------------------------------------------------
void CCamera::SetPosV(const D3DXVECTOR3 posV)
{
	m_posV = posV;
}
//-------------------------------------------------------
//注視点の設定処理
//-------------------------------------------------------
void CCamera::SetPosR(const D3DXVECTOR3 posR)
{
	m_posR = posR;
}
//-------------------------------------------------------
//上方向ベクトルの設定処理
//-------------------------------------------------------
void CCamera::SetVecU(const D3DXVECTOR3 vecU)
{
	m_vecU = vecU;
}
//-------------------------------------------------------
//向きの設定処理
//-------------------------------------------------------
void CCamera::SetRotation(const D3DXVECTOR3 rot)
{
	m_rot = rot;
}