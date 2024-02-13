//=============================================================================
//
// プレイヤー3D処理 [player3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "bullet3D.h"
#include "explosion.h"
#include "game.h"
#include "modelset.h"
#include "block3D.h"
#include "camera.h"
#include "effect.h"

//マクロ定義
#define PLAYERJAMPSPEED (3.0f)  //ジャンプ時の落下スピード
#define JAMPCNT (10)  //重力がかかるまでのカウント
#define BULLETSPEED (10.0f)  //プレイヤーの弾スピード
#define ATTACKCNT (20)  //アタックカウント
#define LONGCNT (62)  //ロングカウント
#define ATTACKGAGE (100)  //アタックゲージ
#define PLAYER_COR_REFLECTION (200.0f)  //反射時の当たり判定

//静的メンバ変数
CPlayer3D *CPlayer3D::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CPlayer3D::CPlayer3D()
{
	if (m_apObject == NULL)
	{
		m_apObject = this;
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CPlayer3D::~CPlayer3D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CPlayer3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	CModel *pModel = CManager::GetInstance()->GetModel();  //モデルのポインタ

	//モデルを宣言
	m_nIdxModel = pModel->Regist("data\\MODEL\\rob001.x");  //プレイヤー

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(TYPE_PLAYER);

	//状態管理設定
	CObjectX::SetState(CObject::STATE_NORMAL, 0);

	//ライフの設定
	m_Life = PLALIFE;

	m_apObject->SetLife(m_Life);

	//値を初期化
	m_nCntDown = 0;
	m_nCntAttack = 0;
	m_nCntStep = 0;
	m_StepGaugeCnt = 0;
	m_Step = false;
	m_StepPossible = false;
	m_jump = PLAYERJUMP_GROUND;
	m_SwordAttack = SWORDATTACK_0;
	m_StateRes = STATERES_NONE;
	m_StepState = STEPSTATE_NONE;
	m_StartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_KeepPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_StepGauge = PLASTAMINA_MAX;  //スタミナ上限からスタート

	//日本刀の生成
	CModelSet::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_SWORD);

	//クロスヘア生成
	CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(50.0f, 5.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_CROSS);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CPlayer3D::Uninit()
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();

	m_apObject = NULL;
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CPlayer3D::Update()
{
	D3DXVECTOR3 pos = GetPosition();  //位置の取得
	D3DXVECTOR3 move = GetMove();	//移動量の取得
	D3DXVECTOR3 rot = GetRotation();  //向きの取得
	D3DXVECTOR3 scale = GetSize();  //サイズの取得

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//サウンドの取得
	CSound *pSound = CManager::GetInstance()->GetSound();

	SetPositionOld(pos);  //過去の位置設定

	//状態管理設定
	CObject::UpdateState();

	//プレイヤーの近接攻撃
	CEnemy3D::PlayerAttack(this);

	//敵の銃攻撃
	CEnemy3D::ShootBullet(this);

	///////////////////////////////////////////
	//リスポーン状態が通常の時
	///////////////////////////////////////////
	if (m_StateRes == STATERES_NONE)
	{
		///////////////////////////////////////////
		//プレイヤーキーボード操作
		///////////////////////////////////////////
		//Dキーが押されている時
		if (pInputKeyboard->GetPress(DIK_D) == true
			|| pInputPad->CInputPad::GetJoyStickLX(0) > 0)
		{
			//Dキーが押されている時にWキーが押されている時
			if (pInputKeyboard->GetPress(DIK_W) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) > 0)
			{
				//右上移動
				move.x += sinf(rot.y + D3DX_PI * -0.75f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * -0.75f) * PLAYERSPEED;
			}

			//Dキーが押されている時にSキーが押されている時
			else if (pInputKeyboard->GetPress(DIK_S) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
			{
				//右下移動
				move.x += sinf(rot.y + D3DX_PI * -0.25f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * -0.25f) * PLAYERSPEED;
			}

			else
			{
				//Dキーが押された
				move.x += sinf(rot.y + D3DX_PI * -0.5f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * -0.5f) * PLAYERSPEED;
			}
		}

		//Aキーが押されている時
		else if (pInputKeyboard->GetPress(DIK_A) == true
			|| pInputPad->CInputPad::GetJoyStickLX(0) < 0)
		{
			//Aキーが押されている時にWキーが押されている時
			if (pInputKeyboard->GetPress(DIK_W) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) > 0)
			{
				//左上移動
				move.x += sinf(rot.y + D3DX_PI * 0.75f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * 0.75f) * PLAYERSPEED;
			}

			//Aキーが押されている時にSキーが押されている時
			else if (pInputKeyboard->GetPress(DIK_S) == true
				|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
			{
				//左下移動
				move.x += sinf(rot.y + D3DX_PI * 0.25f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * 0.25f) * PLAYERSPEED;
			}

			else
			{
				//Aキーが押された
				move.x += sinf(rot.y + D3DX_PI * 0.5f) * PLAYERSPEED;
				move.z += cosf(rot.y + D3DX_PI * 0.5f) * PLAYERSPEED;
			}
		}

		//Wキーが押されている時
		else if (pInputKeyboard->GetPress(DIK_W) == true
			|| pInputPad->CInputPad::GetJoyStickLY(0) > 0)
		{
			//Wキーが押された
			move.x += sinf(rot.y + D3DX_PI) * PLAYERSPEED;
			move.z += cosf(rot.y + D3DX_PI) * PLAYERSPEED;
		}

		//Sキーが押されている時
		else if (pInputKeyboard->GetPress(DIK_S) == true
			|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
		{
			//Sキーが押された
			move.x += sinf(rot.y) * PLAYERSPEED;
			move.z += cosf(rot.y) * PLAYERSPEED;
		}

		//ジャンプ
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_jump == PLAYERJUMP_GROUND   //SPACEが押された時
			|| pInputPad->GetTrigger(CInputPad::BUTTON_A, 0) && m_jump == PLAYERJUMP_GROUND)  //Aボタンが押された時
		{
			move.y = 100.0f;  //上に移動する
			pos.y -= move.y;  //慣性
			move.y -= 0.3f;  //重力を加える

			m_nCntDown = 0;

			m_jump = PLAYERJUMP_SKY;  //ジャンプしている状態にする

			//SEの再生
			pSound->PlaySound(SOUND_LABEL_SE_JAMP);
		}
	}

	///////////////////////////////////////////
	//リスポーン状態が待機の時
	///////////////////////////////////////////
	if (m_StateRes == STATERES_RESPAWN)
	{
		//SPACEキーが押されたとき
		if (pInputKeyboard->GetTrigger(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
		{
			//リスポーン状態を通常にする
			SetStateRes(STATERES_NONE);
		}
	}

	if (m_nCntDown > JAMPCNT)
	{
		//ステップ状態がfalseの時
		if (m_Step == false)
		{
			//重力を加える
			move.y -= 4.0f;
		}
	}

	//ステップ状態がtrueの時
	if (m_Step == true)
	{
		if (m_nCntStep > 10)
		{
			m_Step = false;
		}
	}

	//インクリメント
	m_nCntDown++;
	m_nCntStep++;

	//位置の更新
	pos += move;

	//移動量を更新
	move.x += (0.0f - move.x) * PLAYERSPEEDUP;
	move.y += (0.0f - move.y) * PLAYERSPEEDUP;
	move.z += (0.0f - move.z) * PLAYERSPEEDUP;

	//角度の補正
	if (rot.x > D3DX_PI)
	{
		rot.x += -D3DX_PI * 2;
	}

	if (rot.x < -D3DX_PI)
	{
		rot.x += D3DX_PI * 2;
	}

	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	///////////////////////////////////////////
	//設定処理
	///////////////////////////////////////////
	SetPosition(pos);  //位置の設定
	SetMove(move);  //移動量の設定
	SetRotation(rot);  //向きの設定
	SetLife(m_Life);  //ライフの設定

	///////////////////////////////////////////
	//処理の更新
	///////////////////////////////////////////
	CModelSet::SwordMove(this);  //剣の移動処理
	CBlock3D::CollisionPlayer(this);  //ブロックとの当たり判定
	CModelSet::ModelCollision(this);  //モデルとの当たり判定
	CCamera::MoveCamera(this);  //カメラ追従
	CCamera::PlayerTriggerCamera(this);  //プレイヤー死亡時カメラの向きの処理

	//ステップ状態以外の時
	if (m_StepState != STEPSTATE_STEP)
	{
		if (m_nCntStep > PLASTAMINA_HEAL)
		{
			m_StepGauge++;  //ゲージを回復する
			m_StepState = STEPSTATE_NONE;  //通常状態にする
		}
	}

	 //ステップ状態の時
	if (m_StepState == STEPSTATE_STEP)
	{
		StepMode();  //ステップ状態の更新
	}

	if (m_StepGauge > PLASTAMINA_MAX)
	{
		m_StepGauge = PLASTAMINA_MAX;  //スタミナ上限より回復しないようにする
	}

	if (m_Restart == true)
	{
		//ジャンプキーが押された時
		if (pInputKeyboard->GetRelease(DIK_SPACE) == true || pInputPad->GetTrigger(CInputPad::BUTTON_A, 0))
		{
			//リスタート状態を無効にする
			m_Restart = false;
		}
	}

	if (pos.y < -1000.0f)
	{
		//プレイヤーのヒット処理
		CPlayer3D::HitPlayer(1000);
	}

	//-------------------------------------------------------
	//プレイヤーのデバック表示
	//-------------------------------------------------------
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤー位置 [%f, %f, %f]\n", pos.x, pos.y, pos.z);
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤー移動量 [%f, %f, %f]\n", move.x, move.y, move.z);
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤー向き [%f, %f, %f]\n", rot.x, rot.y, rot.z);
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤー体力 [%d]\n", m_Life);
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤージャンプ [%d]\n", m_jump);
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CPlayer3D::Draw()
{
	//オブジェクトXの描画処理
	//CObjectX::Draw();  //プレイヤーを表示しない
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CPlayer3D *CPlayer3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size)
{
	CPlayer3D *pPlayer3D = NULL;

	//プレイヤーの生成
	pPlayer3D = new CPlayer3D;

	if (pPlayer3D != NULL)
	{
		//初期化処理
		pPlayer3D->Init();

		//位置の設定
		pPlayer3D->SetPosition(pos);

		//向きの設定
		pPlayer3D->SetRotation(rot);

		//拡大率の設定
		pPlayer3D->SetScale(scale);

		//拡大率設定
		pPlayer3D->SetSize(size);

		//モデルの割り当て
		pPlayer3D->BindModel(pPlayer3D->m_nIdxModel);

		//---------------------------------------------------------------
		//ライフの生成
		//---------------------------------------------------------------
		CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(300.0f, 30.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);
		CLife::Create(D3DXVECTOR3(10.0f, 650.0f, 0.0f), D3DXVECTOR3(410.0f, 40.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEFRAME);

		//---------------------------------------------------------------
		//ステップゲージの生成
		//---------------------------------------------------------------
		CGauge::Create(D3DXVECTOR3(590.0f, 380.0f, 0.0f), D3DXVECTOR3(100.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CGauge::TYPE_STEPFRAME);
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pPlayer3D;
}
//-------------------------------------------------------
//ステップ状態
//-------------------------------------------------------
void CPlayer3D::StepMode(void)
{
	D3DXVECTOR3 pos = GetPosition();  //位置の取得
	D3DXVECTOR3 move = GetMove();  //移動量の取得
	D3DXVECTOR3 rot = GetRotation();  //向きの取得
	D3DXVECTOR3 m_startpos = GetStartPos();  //スタート位置の取得

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	
	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//サウンドの取得
	CSound *pSound = CManager::GetInstance()->GetSound();

	//シフトキーかLBボタンが押された時
	if (pInputKeyboard->GetRelease(DIK_LSHIFT) == true && GetStepPossible() == false
		|| pInputPad->GetRelease(CInputPad::BUTTON_LB, 0) && GetStepPossible() == false)
	{
		//レティクルが向いている方向にステップする
		move.x += sinf(rot.y + D3DX_PI) * STEPSPEED;
		move.y += sinf(rot.x + D3DX_PI) * 170.0f;
		move.z += cosf(rot.y + D3DX_PI) * STEPSPEED;

		m_Step = true;
		m_nCntStep = 0;
		m_StepGaugeCnt = 0;
		m_StepState = STEPSTATE_NONE;  //通常状態にする
		SetStepPossible(true);  //ステップ可能状態を無効にする
	}

	//値の設定
	SetPosition(pos);
	SetMove(move);
	SetRotation(rot);
}
//-------------------------------------------------------
//プレイヤーのヒット処理
//-------------------------------------------------------
void CPlayer3D::HitPlayer(int nDamage)
{
	//サウンドの取得
	CSound *pSound = CManager::GetInstance()->GetSound();;

	if (m_apObject != NULL)
	{
		m_apObject->m_Life -= nDamage;

		if (m_apObject->m_Life <= 0)
		{
			D3DXVECTOR3 move = m_apObject->GetMove();
			D3DXVECTOR3 KeepPos = m_apObject->GetKeepPos();

			move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			KeepPos.z += 130;

			//初期化
			m_apObject->m_nCntDown = 0;
			m_apObject->m_nCntAttack = 0;
			m_apObject->m_nCntStep = 0;
			m_apObject->m_StepGaugeCnt = 0;
			m_apObject->m_Step = false;
			m_apObject->m_StepPossible = false;
			m_apObject->m_jump = PLAYERJUMP_GROUND;
			m_apObject->m_SwordAttack = SWORDATTACK_0;
			m_apObject->m_StateRes = STATERES_NONE;
			m_apObject->m_StepState = STEPSTATE_NONE;
			m_apObject->m_StepGauge = PLASTAMINA_MAX;  //スタミナ上限からスタート

			m_apObject->m_Restart = true;  //リスタート状態を有効にする
			m_apObject->SetStateRes(STATERES_RESPAWN);  //リスポーン状態を待機状態にする
			m_apObject->SetPosition(KeepPos);  //チェックポイントの位置に移動する
			m_apObject->SetMove(move);  //移動量を0にする
			m_apObject->SetLife(PLALIFE);  //ライフリセット

			//リスポーン待機文字生成
			CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 70.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CObject2D::TYPE_RESPAWN);

			//リスポーン待機状態の背景生成
			CObject2D::Create(D3DXVECTOR3(640.0f, 360.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(640.0f, 360.0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f), CObject2D::TYPE_RESPAWNBG);

			//SEの再生
			pSound->PlaySound(SOUND_LABEL_SE_DEATH);
		}
		else
		{
			m_apObject->SetState(CObject::STATE_DAMAGE, 20);  //ダメージ状態

			//SEの再生
			pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//敵との当たり判定
//-------------------------------------------------------
bool CPlayer3D::CollisionEnemy(CEnemy3D *pEnemy)
{	
	///////////////////////////////////////////
	//リスポーン状態が通常の時
	///////////////////////////////////////////
	if (m_apObject->m_StateRes == STATERES_NONE)
	{
		if (m_apObject != NULL)
		{
			D3DXVECTOR3 pos = m_apObject->GetPosition();  //位置の取得
			D3DXVECTOR3 m_Oldpos = m_apObject->GetPositionOld();  //過去の位置の取得
			D3DXVECTOR3 move = m_apObject->GetMove();  //移動量の取得
			D3DXVECTOR3 scale = m_apObject->GetScale();  //拡大率の取得
			CObject::TYPE type = pEnemy->GetType();   //種類を取得
			int typetex = 0;  //敵の種類用
			int PlaLife = m_apObject->GetLife();  //プレイヤーのライフ取得

			if (PlaLife >= 0)
			{
				//種類が敵の場合
				if (type == CObject::TYPE_ENEMY)
				{
					D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //敵の位置の取得
					D3DXVECTOR3 scaleEnemy = pEnemy->GetScale();  //敵の拡大率の取得
					typetex = pEnemy->GetTypeTex();  //敵の種類

					//敵が通常敵の時
					if (typetex == CEnemy3D::TYPE_USUALLY)
					{
						///////////////////////////////////
						//X軸の判定
						///////////////////////////////////
						//敵と重なった時
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * USUALLY_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * USUALLY_COR_Y)
						{
							if ((pos.z + scale.z * PLAYER_COL_Z + 50.0f > posEnemy.z - scaleEnemy.z * USUALLY_COR_Z
								&& pos.z - scale.z * PLAYER_COL_Z + 50.0f < posEnemy.z + scaleEnemy.z * USUALLY_COR_Z))
							{
								if (m_Oldpos.x - scale.x * PLAYER_COL_X > posEnemy.x + scaleEnemy.x * USUALLY_COR_X
									&&  pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * USUALLY_COR_X)
								{//右
									pos.x = posEnemy.x + scaleEnemy.x * USUALLY_COR_X + 29.0f;  //敵抜けないようにする
									move.x = 0.0f;  //移動量を0にする
								}

								if (m_Oldpos.x + scale.x * PLAYER_COL_X < posEnemy.x - scaleEnemy.x * USUALLY_COR_X
									&&  pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * USUALLY_COR_X)
								{//左
									pos.x = posEnemy.x - scaleEnemy.x * USUALLY_COR_X - 29.0f;  //敵抜けないようにする
									move.x = 0.0f;  //移動量を0にする
								}
							}
						}

						///////////////////////////////////
						//Z軸の判定
						///////////////////////////////////
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * USUALLY_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * USUALLY_COR_Y)
						{
							if ((pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * USUALLY_COR_X
								&& pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * USUALLY_COR_X))
							{
								if (m_Oldpos.z - scale.z * PLAYER_COL_Z > posEnemy.z + scaleEnemy.z * USUALLY_COR_Z - 70.0f
									&&  pos.z - scale.z * PLAYER_COL_Z < posEnemy.z + scaleEnemy.z * USUALLY_COR_Z - 70.0f)
								{//奥から
									pos.z = posEnemy.z + scaleEnemy.z * USUALLY_COR_Z - 50.0f;  //敵抜けないようにする
									move.z = 0.0f;  //移動量を0にする
								}

								if (m_Oldpos.z + scale.z * PLAYER_COL_Z < posEnemy.z - scaleEnemy.z * USUALLY_COR_Z - 120.0f
									&&  pos.z + scale.z * PLAYER_COL_Z > posEnemy.z - scaleEnemy.z * USUALLY_COR_Z - 120.0f)
								{//手前
									pos.z = posEnemy.z - scaleEnemy.z * USUALLY_COR_Z - 140.0f;  //敵抜けないようにする
									move.z = 0.0f;  //移動量を0にする
								}
							}
						}
					}

					//ボスの時
					else if (typetex == CEnemy3D::TYPE_BOSS)
					{
						///////////////////////////////////
						//X軸の判定
						///////////////////////////////////
						//敵と重なった時
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * BOSS_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * BOSS_COR_Y)
						{
							if ((pos.z + scale.z * PLAYER_COL_Z + 50.0f > posEnemy.z - scaleEnemy.z * BOSS_COR_Z
								&& pos.z - scale.z * PLAYER_COL_Z + 50.0f < posEnemy.z + scaleEnemy.z * BOSS_COR_Z))
							{
								if (m_Oldpos.x - scale.x * PLAYER_COL_X > posEnemy.x + scaleEnemy.x * BOSS_COR_X
									&&  pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * BOSS_COR_X)
								{//右
									pos.x = posEnemy.x + scaleEnemy.x * BOSS_COR_X + 29.0f;  //敵抜けないようにする
									move.x = 0.0f;  //移動量を0にする
								}

								if (m_Oldpos.x + scale.x * PLAYER_COL_X < posEnemy.x - scaleEnemy.x * BOSS_COR_X
									&&  pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * BOSS_COR_X)
								{//左
									pos.x = posEnemy.x - scaleEnemy.x * BOSS_COR_X - 29.0f;  //敵抜けないようにする
									move.x = 0.0f;  //移動量を0にする
								}
							}
						}

						///////////////////////////////////
						//Z軸の判定
						///////////////////////////////////
						if (pos.y - scale.y < posEnemy.y + scaleEnemy.y * BOSS_COR_Y
							&&  pos.y + scale.y * PLAYER_COL_Y > posEnemy.y - scaleEnemy.y * BOSS_COR_Y)
						{
							if ((pos.x + scale.x * PLAYER_COL_X > posEnemy.x - scaleEnemy.x * BOSS_COR_X
								&& pos.x - scale.x * PLAYER_COL_X < posEnemy.x + scaleEnemy.x * BOSS_COR_X))
							{
								if (m_Oldpos.z - scale.z * PLAYER_COL_Z > posEnemy.z + scaleEnemy.z * BOSS_COR_Z - 70.0f
									&&  pos.z - scale.z * PLAYER_COL_Z < posEnemy.z + scaleEnemy.z * BOSS_COR_Z - 70.0f)
								{//奥から
									pos.z = posEnemy.z + scaleEnemy.z * BOSS_COR_Z - 50.0f;  //敵抜けないようにする
									move.z = 0.0f;  //移動量を0にする
								}

								if (m_Oldpos.z + scale.z * PLAYER_COL_Z < posEnemy.z - scaleEnemy.z * BOSS_COR_Z - 120.0f
									&&  pos.z + scale.z * PLAYER_COL_Z > posEnemy.z - scaleEnemy.z * BOSS_COR_Z - 120.0f)
								{//手前
									pos.z = posEnemy.z - scaleEnemy.z * BOSS_COR_Z - 140.0f;  //敵抜けないようにする
									move.z = 0.0f;  //移動量を0にする
								}
							}
						}
					}

					//値の設定
					m_apObject->SetPosition(pos);
					m_apObject->SetMove(move);
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//弾との当たり判定
//-------------------------------------------------------
bool CPlayer3D::CollisionBullet(CBullet3D *pBullet)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();;

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();;

	//サウンドの取得
	CSound *pSound = CManager::GetInstance()->GetSound();;

	//種類を取得
	CObject::TYPE type = pBullet->GetType();

	if (m_apObject != NULL)
	{
		//種類が弾の場合
		if (type == CObject::TYPE_BULLET)
		{
			D3DXVECTOR3 pos = m_apObject->GetPosition();  //位置の取得
			D3DXVECTOR3 rot = m_apObject->GetRotation();  //向きの取得
			D3DXVECTOR3 scale = m_apObject->GetScale();  //拡大率の取得
			D3DXVECTOR3 posBullet = pBullet->GetPosition();  //弾の位置取得
			D3DXVECTOR3 rotBullet = pBullet->GetRotation();  //弾の向き取得
			D3DXVECTOR3 scaleBullet = pBullet->GetScale();  //弾の拡大率取得
			D3DXVECTOR3 PLACOL = pos;  //プレイヤーの向きで当たり判定
			D3DXVECTOR3 fAngle = D3DXVECTOR3(posBullet.x - pos.x, posBullet.y - pos.y, posBullet.z - pos.z);
			D3DXVec3Normalize(&fAngle, &fAngle);

			PLACOL.x = pos.x + sinf(rot.y) * PLAYER_COL_X;
			PLACOL.z = pos.z + 50.0f + cosf(rot.y) * PLAYER_COL_Z;

			//弾の範囲
			float fRangth = sqrtf((PLACOL.x - posBullet.x) * (PLACOL.x - posBullet.x) + (PLACOL.z - posBullet.z) * (PLACOL.z - posBullet.z));

			//プレイヤーから判定される距離
			float fLength = 50.0f;

			float fRot = rot.y + D3DX_PI - rotBullet.y;

			//角度の補正
			if (fRot > D3DX_PI)
			{
				fRot += -D3DX_PI * 2;
			}

			if (fRot < -D3DX_PI)
			{
				fRot += D3DX_PI * 2;
			}

			//プレイヤーと重なる前に攻撃キーを入力していた時(反射)
			if (fRangth > fLength
				&& fRangth < 1000.0f
				&& pInputKeyboard->GetTrigger(DIK_V) == true || pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0))
			{
				pBullet->Uninit();

				//弾発射
				CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_PLAYER);

				//エフェクトの生成
				CEffect::Create(D3DXVECTOR3(pos.x, pos.y + 30.0f, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(50.0f, 50.0f, 100.0f), CEffect::EFFECTTYPE_BEAM);
			}

			//プレイヤーに当たった時
			else if (fRangth < fLength)
			{
				//プレイヤーのヒット処理
				CPlayer3D::HitPlayer(100);

				return TRUE;
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//ライフ設定処理
//-------------------------------------------------------
void CPlayer3D::LifeMove(CLife *pLife)
{
	if (m_apObject != NULL)
	{
		CObject::TYPE type = pLife->GetType();  //種類

		//種類を取得
		int typetex = pLife->GetTypeTex();
		int nLife = pLife->GetLife();

		//種類がライフの場合
		if (type == CObject::TYPE_LIFE)
		{
			int m_lifePlayer = m_apObject->GetLife();  //プレイヤーのライフ取得

			if (m_lifePlayer == 500 &&
				nLife != CLife::LIFE_500)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(300.0f, 30.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_500;
			}

			if (m_lifePlayer == 400 &&
				nLife != CLife::LIFE_400)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(240.0f, 30.0f, 0.0f), D3DXVECTOR3(0.8f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_400;
			}

			if (m_lifePlayer == 300 &&
				nLife != CLife::LIFE_300)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(180.0f, 30.0f, 0.0f), D3DXVECTOR3(0.6f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_300;
			}

			if (m_lifePlayer == 200 &&
				nLife != CLife::LIFE_200)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(120.0f, 30.0f, 0.0f), D3DXVECTOR3(0.4f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_200;
			}

			if (m_lifePlayer == 100 &&
				nLife != CLife::LIFE_100)
			{
				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}

				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(60.0f, 30.0f, 0.0f), D3DXVECTOR3(0.2f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				nLife = CLife::LIFE_100;
			}

			if (m_lifePlayer == 0)
			{
				//---------------------------------------------------------------
				//ライフの生成
				//---------------------------------------------------------------
				CLife::Create(D3DXVECTOR3(117.0f, 650.0f, 0.0f), D3DXVECTOR3(0.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CLife::TYPE_LIFEGAUGE);

				if (typetex == CLife::TYPE_LIFEGAUGE)
				{
					pLife->Uninit();
				}
			}

			pLife->SetLife(nLife);
		}
	}
}
//-------------------------------------------------------
//ステップゲージ設定処理
//-------------------------------------------------------
void CPlayer3D::StepGaugeMove(CGauge *pGauge)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();;

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();;

	if (m_apObject != NULL)
	{
		//種類を取得
		CObject::TYPE type = pGauge->GetType();

		//種類を取得
		int typetex = pGauge->GetTypeTex();

		//種類がゲージの場合
		if (type == CObject::TYPE_GAUGE)
		{
			D3DXVECTOR3 pos = m_apObject->GetPosition();  //位置の取得
			D3DXVECTOR3 move = m_apObject->GetMove();  //移動量の取得
			D3DXVECTOR3 rot = m_apObject->GetRotation();  //向きの取得
			D3DXVECTOR3 GaugeSize = pGauge->GetSize();  //テクスチャサイズの取得
			D3DXVECTOR3 fAngle = D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z);
			D3DXVec3Normalize(&fAngle, &fAngle);

			if (GaugeSize.x > 100.0f)
			{
				GaugeSize.x = 100.0f;
			}

			if (m_apObject->m_StepState == STEPSTATE_NONE 
				|| m_apObject->m_StepState == STEPSTATE_OUTSTAMINA)
			{
				m_apObject->m_StepState = STEPSTATE_NONE;

				if (m_apObject->m_nCntStep > PLASTAMINA_HEAL)
				{
					m_apObject->m_StepState = STEPSTATE_NONE;  //通常状態にする

					if (m_apObject->m_StepGauge < PLASTAMINA_MAX)
					{
						GaugeSize.x += m_apObject->m_StepGauge * 0.01f;
					}
				}
			}

			if (m_apObject->m_StepGauge < 0)
			{
				m_apObject->m_StepGauge = 0;
				m_apObject->m_StepState = STEPSTATE_OUTSTAMINA;
			}

			//スタミナが切れていないとき
			if (m_apObject->m_StepState != STEPSTATE_OUTSTAMINA)
			{
				//シフトキーかLBボタンが押されてる時
				if (pInputKeyboard->GetPress(DIK_LSHIFT) == true
					|| pInputPad->GetPress(CInputPad::BUTTON_LB, 0))
				{
					m_apObject->m_nCntStep = 0;
					m_apObject->m_StepState = STEPSTATE_STEP;  //ステップ状態にする
					m_apObject->m_StepGaugeCnt++;
					m_apObject->m_StepGauge--;
					GaugeSize.x -= m_apObject->m_StepGaugeCnt * 0.01f;  //テクスチャを小さくしていく

					if (m_apObject->m_StepGaugeCnt > PLASTAMINA_MAX)
					{
						//レティクルが向いている方向にステップする
						move.x += sinf(rot.y + D3DX_PI) * STEPSPEED;
						move.y += fAngle.y * 170.0f;
						move.z += cosf(rot.y + D3DX_PI) * STEPSPEED;

						m_apObject->m_StepGaugeCnt = 0;
						m_apObject->m_Step = true;
						m_apObject->m_StepState = STEPSTATE_OUTSTAMINA;  //通常状態にする
					}
				}
			}

			//値の設定
			m_apObject->SetMove(move);
			pGauge->SetSize(GaugeSize);

			//-------------------------------------------------------
			//プレイヤーのデバック表示
			//-------------------------------------------------------
			CManager::GetInstance()->GetDebugProc()->Print("スタミナ [%d]\n", m_apObject->m_StepGauge);
			CManager::GetInstance()->GetDebugProc()->Print("ステップカウント [%d]\n", m_apObject->m_StepGaugeCnt);
			CManager::GetInstance()->GetDebugProc()->Print("ステップ状態[%d]\n", m_apObject->m_StepState);
		}
	}
}
//-------------------------------------------------------
//体力の設定
//-------------------------------------------------------
void CPlayer3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//ステップ可能状態切り替えの設定
//-------------------------------------------------------
void CPlayer3D::SetStepPossible(bool StepPossible)
{
	m_StepPossible = StepPossible;
}
//-------------------------------------------------------
//リスタート状態切り替えの設定
//-------------------------------------------------------
void CPlayer3D::SetRestart(bool Restart)
{
	m_Restart = Restart;
}
//-------------------------------------------------------
//ジャンプの設定
//-------------------------------------------------------
void CPlayer3D::SetPlayerJump(PLAYERJAMP Jamp)
{
	m_jump = Jamp;
}
//-------------------------------------------------------
//日本刀の攻撃段階の設定
//-------------------------------------------------------
void CPlayer3D::SetSwordAttack(SWORDATTACK SwordAttack)
{
	m_SwordAttack = SwordAttack;
}
//-------------------------------------------------------
//リスポーン状態の設定
//-------------------------------------------------------
void CPlayer3D::SetStateRes(STATERES StateRes)
{
	m_StateRes = StateRes;
}
//-------------------------------------------------------
//保存されている位置の設定
//-------------------------------------------------------
void CPlayer3D::SetKeepPos(D3DXVECTOR3 KeepPos)
{
	m_KeepPos = KeepPos;
}