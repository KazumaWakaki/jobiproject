//=============================================================================
//
// モデル配置処理 [modelset.cpp]
// Author 若木 一真
//
//=============================================================================
#include "modelset.h"
#include "manager.h"
#include "player3D.h"
#include "bullet3D.h"

//マクロ定義
#define POS_Y (0.0f)  //位置Yの調整

//静的メンバ変数
CModelSet *CModelSet::m_apObject[MAX_MODEL] = {};
int CModelSet::m_nCntBreakCore = 0;
//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CModelSet::CModelSet()
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] == NULL)
		{
			m_apObject[nCnt] = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CModelSet::~CModelSet()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CModelSet::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //モデルのポインタ

	m_nIdxModel[TYPE_SWORD] = pModel->Regist("data\\MODEL\\sword.x");  //日本刀
	m_nIdxModel[TYPE_CHECKPOINT] = pModel->Regist("data\\MODEL\\neonfloor001.x");  //チェックポイント
	m_nIdxModel[TYPE_BOSSCORE] = pModel->Regist("data\\MODEL\\core.x");  //ボスコア
	m_nIdxModel[TYPE_BEAM_PLA] = pModel->Regist("data\\MODEL\\beameffect.x");  //ビーム
	m_nIdxModel[TYPE_BEAM_ENE] = pModel->Regist("data\\MODEL\\beameffect.x");  //ビーム
	m_nIdxModel[TYPE_WALL] = pModel->Regist("data\\MODEL\\wall001.x");  //周りの壁
	m_nIdxModel[TYPE_JAMP_BOARD] = pModel->Regist("data\\MODEL\\jamp_board.x");  //ジャンプ看板
	m_nIdxModel[TYPE_STEP_BOARD] = pModel->Regist("data\\MODEL\\step_board.x");  //ステップ看板

	//モデルの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(TYPE_MODEL);

	//値の初期化
	m_AttackSwordCnt = 0;
	m_nCntSwordRot = 200;
	m_BreakCore = false;
	m_BossCoreState = BOSSCORESTATE_NONE;
	m_SwordTag = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CModelSet::Uninit()
{
	int nID = m_nID;

	//オブジェクトの削除処理
	CObjectX::Uninit();

	if (m_apObject[nID] != NULL)
	{
		m_apObject[nID] = NULL;
	}
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CModelSet::Update()
{
	//日本刀向き移動処理
	SwordRotMove();

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	D3DXVECTOR3 pos = GetPosition();  //位置の取得
	D3DXVECTOR3 rot = GetRotation();  //向きの取得
	D3DXVECTOR3 scale = GetScale();  //スケールの取得
	int typetex = GetTypeTex();  //タイプ判定用

#if _DEBUG

	//Bキーが押された時
	if (pInputKeyboard->GetPress(DIK_B) == true)
	{
		rot.x += 0.05f;
	}

	//Nキーが押された時
	if (pInputKeyboard->GetPress(DIK_N) == true)
	{
		rot.y += 0.05f;
	}

	//Mキーが押された時
	if (pInputKeyboard->GetPress(DIK_M) == true)
	{
		rot.z += 0.05f;
	}

	//ENTERキーが押された時
	if (pInputKeyboard->GetPress(DIK_RETURN) == true)
	{
		rot.x = 0.0f;
		rot.y = 0.0f;
		rot.z = 0.0f;
	}

#endif

	//位置の補正
	if (pos.x >= 10000.0f)
	{
		pos.x = 10000.0f;
	}

	//角度の補正
	if (rot.x > D3DX_PI)
	{
		rot.x += -D3DX_PI * 2;
	}
	
	if (rot.x < -D3DX_PI)
	{		 
		rot.x += D3DX_PI * 2;
	}

	//角度の補正
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	//角度の補正
	if (rot.z > D3DX_PI)
	{
		rot.z = -D3DX_PI;
	}

	if (rot.z < -D3DX_PI)
	{
		rot.z = D3DX_PI;
	}

	if (typetex == TYPE_BEAM_PLA || typetex == TYPE_BEAM_ENE)
	{
		m_nCntBeamScale++;

		scale.z += 0.08f;
	}

	SetPosition(pos);
	SetRotation(rot);
	SetScale(scale);

	if (m_nCntBeamScale >70)
	{
		Uninit();
	}

	CEnemy3D::EnemyBattelState(this);  //敵別の戦闘態勢状態ごとの処理

	//オブジェクトのタイプが日本刀のとき
	if (typetex == TYPE_SWORD)
	{
		//-------------------------------------------------------
		//モデルのデバック表示
		//-------------------------------------------------------
		CManager::GetInstance()->GetDebugProc()->Print("日本刀位置 [%f, %f, %f]\n", pos.x, pos.y, pos.z);
		CManager::GetInstance()->GetDebugProc()->Print("日本刀向き [%f, %f, %f]\n", rot.x, rot.y, rot.z);
	}
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CModelSet::Draw()
{
	int typetex = GetTypeTex();  //タイプ判定用

	//if (typetex != TYPE_CHECKPOINT)
	{
		//モデルXの描画処理
		CObjectX::Draw();
	}
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CModelSet *CModelSet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex)
{
	CModelSet *pModelSet = NULL;

	//モデルの生成
	pModelSet = new CModelSet;

	if (pModelSet != NULL)
	{
		//初期化処理
		pModelSet->Init();
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	pModelSet->SetPosition(pos);  //位置の設定
	pModelSet->SetRotation(rot);  //向きの設定
	pModelSet->SetScale(scale);  //拡大率の設定
	pModelSet->SetSize(size);  //サイズ設定
	pModelSet->SetTypeTex(SetTypeTex);  //テクスチャタイプ設定

	//nCount分回す
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		//nCountと選択されたモデルが一致した時
		if (nCount == SetTypeTex)
		{
			//モデルの割り当て
			pModelSet->BindModel(pModelSet->m_nIdxModel[nCount]);
		}
	}

	return pModelSet;
}
//-------------------------------------------------------
//プレイヤーとの当たり判定処理
//-------------------------------------------------------
bool CModelSet::ModelCollision(CPlayer3D *pPlayer)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//サウンドの取得
	CSound *pSound = CManager::GetInstance()->GetSound();

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 m_scale = m_apObject[nCnt]->GetScale();  //拡大率の取得
			CObject::TYPE type;  //種類
			type = pPlayer->GetType();   //種類を取得

			 //種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //プレイヤーの向きの取得
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //プレイヤーの拡大率の取得
				D3DXVECTOR3 PLACOL = posPlayer;  //プレイヤーの向きで当たり判定
				int typetex = m_apObject[nCnt]->GetTypeTex();  //タイプ判定用

				//チェックポイントの時
				if (typetex == TYPE_CHECKPOINT)
				{
					D3DXVECTOR3  KeepPos;  //プレイヤーの位置を保存用

					//プレイヤーと重なった時
					if (pos.x - m_scale.x * CHECKPOINT_COR < posPlayer.x + scalePlayer.x * PLAYER_COL_X
						&&  pos.x + m_scale.x * CHECKPOINT_COR > posPlayer.x - scalePlayer.x * PLAYER_COL_X
						&&  pos.y - m_scale.y * CHECKPOINT_COR < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  pos.z - m_scale.z * CHECKPOINT_COR < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 120.0f
						&&  pos.z + m_scale.z * CHECKPOINT_COR > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 120.0f)
					{
						KeepPos = pPlayer->GetPosition();  //現在のプレイヤーの位置を保存
						KeepPos.x = pos.x;  //チェックポイントの真ん中に位置調整
						KeepPos.y = pos.y + 200.0f;  //チェックポイントの真ん中に位置調整
						pPlayer->SetKeepPos(KeepPos);  //保存されている位置の設定
						m_apObject[nCnt]->Uninit();  //終了処理

						//SEの再生
						pSound->PlaySound(SOUND_LABEL_SE_CHECKPOINT);

						return TRUE;
					}
				}
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//弾との当たり判定
//-------------------------------------------------------
bool CModelSet::CollisionBullet(CBullet3D *pBullet)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	//サウンドの取得
	CSound *pSound = CManager::GetInstance()->GetSound();

	//種類を取得
	CObject::TYPE type = pBullet->GetType();

	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != nullptr)
		{
			//種類が弾の場合
			if (type == CObject::TYPE_BULLET)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //スケールの取得
				D3DXVECTOR3 posBullet = pBullet->GetPosition();  //弾の位置取得
				D3DXVECTOR3 scaleBullet = pBullet->GetScale();  //弾のスケール取得
				int typetex = m_apObject[nCnt]->GetTypeTex();  //テクスチャタイプ取得

				//ボスコアの時
				if (typetex == TYPE_BOSSCORE)
				{
					//プレイヤーの弾と重なった時
					if (pos.x + scale.x * BOSSCORE_COR_X > posBullet.x - scaleBullet.x * BULLET_COL_XZ
						&&  pos.x - scale.x * BOSSCORE_COR_X < posBullet.x + scaleBullet.x * BULLET_COL_XZ
						&&  pos.y + scale.y * BOSSCORE_COR_Y > posBullet.y - scaleBullet.y * BULLET_COL_Y
						&&  pos.y - scale.y < posBullet.y + scaleBullet.y
						&&  pos.z + scale.z * BOSSCORE_COR_Z > posBullet.z - scaleBullet.z * BULLET_COL_XZ
						&&  pos.z - scale.z * BOSSCORE_COR_Z < posBullet.z + scaleBullet.z * BULLET_COL_XZ)
					{
						pBullet->Uninit();  //弾を消す

						m_apObject[nCnt]->SetBreakCore(true);
						pos.x = 10000.0f;  //コアの位置を飛ばす
						m_apObject[nCnt]->m_nCntBreakCore += 1;

						//コアが二個破壊されたとき
						if (m_apObject[nCnt]->m_nCntBreakCore == 2)
						{
							m_apObject[nCnt]->SetBossCoreState(BOSSCORESTATE_BREAK);  //コアが壊れた状態にする
							m_apObject[nCnt]->m_nCntBreakCore += 1;
						}

						//コアが追加で三個破壊されたとき
						if (m_apObject[nCnt]->m_nCntBreakCore == 6)
						{
							m_apObject[nCnt]->SetBossCoreState(BOSSCORESTATE_BREAK);  //コアが壊れた状態にする
						}

						m_apObject[nCnt]->SetPosition(pos);  //位置の設定

						return TRUE;
					}
				}

				//-------------------------------------------------------
				//モデルのデバック表示
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("コア破壊カウンター [%d]\n", m_apObject[nCnt]->m_nCntBreakCore);
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//日本刀向き移動処理
//-------------------------------------------------------
void CModelSet::SwordRotMove(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

	D3DXVECTOR3 pos = GetPosition();  //位置の取得
	D3DXVECTOR3 posOld = GetPositionOld();  //過去の位置の取得
	D3DXVECTOR3 rot = GetRotation();  //向きの取得
	int typetex = GetTypeTex();  //タイプ判定用
	posOld = pos;  //過去の位置に現在の位置を入れる

	//オブジェクトのタイプが日本刀のとき
	if (typetex == TYPE_SWORD)
	{
		//攻撃キーを押したとき
		if (pInputKeyboard->GetTrigger(DIK_V) == true && m_SwordRot == SWORDROT_0
			|| pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0) && m_SwordRot == SWORDROT_0)
		{
			m_nCntSwordRot = 0;
			m_SwordRot = SWORDROT_1;
		}

		if (m_SwordRot == SWORDROT_1)
		{
			rot.x = -1.57f;

			if (m_nCntSwordRot < 15)
			{
				m_SwordRotTag = rot;
				m_SwordRotTag.y += 0.2f;  //目標地点Y
			}

			D3DXVECTOR3 RotDest = m_SwordRotTag - GetRotation();
			rot.y = GetRotation().y + RotDest.y * 0.8f;  //慣性をつける

			if (m_nCntSwordRot > 50)
			{
				//値の初期化
				rot.x = 0.0f;
				rot.y = 0.0f;
				m_nCntSwordRot = 0;
				m_SwordRot = SWORDROT_0;  //攻撃していないにする
			}

			m_nCntSwordRot++;
		}

		SetPosition(pos);  //位置の設定
		SetRotation(rot);  //向きの設定
		SetSwordRot(m_SwordRot);

		//-------------------------------------------------------
		//モデルのデバック表示
		//-------------------------------------------------------
		CManager::GetInstance()->GetDebugProc()->Print("攻撃段階 [%d]\n", m_SwordRot);
		CManager::GetInstance()->GetDebugProc()->Print("攻撃カウント [%d]\n", m_nCntSwordRot);
	}
}
//-------------------------------------------------------
//日本刀の移動処理
//-------------------------------------------------------
void CModelSet::SwordMove(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			//キーボードの取得
			CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

			//ゲームパッドの取得
			CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //向きの取得
			SWORDROT SwordRot = m_apObject[nCnt]->GetSwordRot();  //日本刀の攻撃3段階の取得
			CObject::TYPE type;  //種類
			CPlayer3D::PLAYERJAMP jamp = pPlayer->GetJamp();  //プレイヤーのジャンプ状態取得
			type = pPlayer->GetType();   //種類を取得
			int typetex = m_apObject[nCnt]->GetTypeTex();  //タイプ判定用

			//種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
				D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //プレイヤーの移動量の取得
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //プレイヤーの向きの取得

				//オブジェクトのタイプが日本刀のとき
				if (typetex == TYPE_SWORD)
				{
					pos.x = posPlayer.x + sinf(rotPlayer.y + D3DX_PI * -0.85f) * 150.0f;
					pos.y = posPlayer.y + 100.0f + sinf(rotPlayer.x + D3DX_PI) * 150.0f;
					pos.z = posPlayer.z + cosf(rotPlayer.y + D3DX_PI * -0.85f) * 150.0f;

#if 1
					if (SwordRot == SWORDROT_0)
					{
						rot.y = rotPlayer.y - D3DX_PI;
						rot.x = rotPlayer.x + D3DX_PI;
					}
#endif

					//プレイヤーのリスポーン状態が通常のとき
					if (pPlayer->GetStateRes() == pPlayer->STATERES_NONE)
					{
						//プレイヤーが地面にいるとき
						if (jamp == pPlayer->PLAYERJUMP_GROUND)
						{
							//前左右移動している時
							if (pInputKeyboard->GetPress(DIK_W) == true || pInputPad->CInputPad::GetJoyStickLY(0) > 0
								|| pInputKeyboard->GetPress(DIK_A) == true || pInputPad->CInputPad::GetJoyStickLX(0) < 0
								|| pInputKeyboard->GetPress(DIK_D) == true || pInputPad->CInputPad::GetJoyStickLX(0) > 0)
							{
								if (m_apObject[nCnt]->m_nCntSword < 15)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y += 3.0f;  //目標地点
								}
								else if (m_apObject[nCnt]->m_nCntSword < 30)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y -= 3.0f;  //目標地点
								}

								D3DXVECTOR3 PosDest = m_apObject[nCnt]->m_SwordTag - m_apObject[nCnt]->GetPosition();
								pos.y = m_apObject[nCnt]->GetPosition().y + PosDest.y * 0.1f;  //慣性をつける

								if (m_apObject[nCnt]->m_nCntSword > 45)
								{
									m_apObject[nCnt]->m_nCntSword = 0;  //カウントを戻す
								}
							}

							//後ろ移動している時
							if (pInputKeyboard->GetPress(DIK_S) == true
								|| pInputPad->CInputPad::GetJoyStickLY(0) < 0)
							{
								if (m_apObject[nCnt]->m_nCntSword < 15)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y -= 3.0f;  //目標地点
								}

								else if (m_apObject[nCnt]->m_nCntSword < 30)
								{
									m_apObject[nCnt]->m_SwordTag = pos;
									m_apObject[nCnt]->m_SwordTag.y += 3.0f;  //目標地点
								}

								D3DXVECTOR3 PosDest = m_apObject[nCnt]->m_SwordTag - m_apObject[nCnt]->GetPosition();
								pos.y = m_apObject[nCnt]->GetPosition().y + PosDest.y * 0.1f;  //慣性をつける

								if (m_apObject[nCnt]->m_nCntSword > 45)
								{
									m_apObject[nCnt]->m_nCntSword = 0;  //カウントを戻す
								}
							}
						}

						m_apObject[nCnt]->m_nCntSword++;
					}

					m_apObject[nCnt]->SetPosition(pos);  //位置の設定
					m_apObject[nCnt]->SetRotation(rot);  //向きの設定

					//-------------------------------------------------------
					//モデルのデバック表示
					//-------------------------------------------------------
					//CManager::GetInstance()->GetDebugProc()->Print("剣上下カウント [%d]\n", m_apObject[nCnt]->m_nCntSword);
					//CManager::GetInstance()->GetDebugProc()->Print("ジャンプ [%d]\n", jamp);
				}
			}
		}
	}
}
//-------------------------------------------------------
//ボスのコア移動量処理
//-------------------------------------------------------
void CModelSet::CoreMove(CEnemy3D *pEnemy)
{
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			//キーボードの取得
			CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

			//ゲームパッドの取得
			CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();

			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //向きの取得
			CObject::TYPE type;  //種類
			type = pEnemy->GetType();   //種類を取得
			int typetex = m_apObject[nCnt]->GetTypeTex();  //タイプ判定用

			//種類が敵の場合
			if (type == CObject::TYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //敵の位置の取得
				D3DXVECTOR3 rotEnemy = pEnemy->GetRotation();  //敵の向きの取得
				CEnemy3D::BOSS_BATTEL BossBattel = pEnemy->GetBossBattel();  //ボスの戦闘態勢状態

				//ボスコアのとき
				if (typetex == TYPE_BOSSCORE)
				{
					rot.y += 0.005f;

					if (BossBattel == CEnemy3D::BOSS_BATTEL_1)
					{
						if (m_apObject[nCnt]->m_BreakCore == false)
						{
							if (m_apObject[nCnt]->m_nID == 5)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * 150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 150.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

							if (m_apObject[nCnt]->m_nID == 6)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * -150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 150.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 400.0f;
							}
						}
					}

					if (BossBattel == CEnemy3D::BOSS_BATTEL_2)
					{
						if (m_apObject[nCnt]->m_BreakCore == false)
						{
							if (m_apObject[nCnt]->m_nID == 7)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * 0.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 300.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

							if (m_apObject[nCnt]->m_nID == 8)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * 150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 300.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

							if (m_apObject[nCnt]->m_nID == 9)
							{
								pos.x = posEnemy.x + sinf(rotEnemy.y + D3DX_PI * -0.85f) * -150.0f;
								pos.y = posEnemy.y + sinf(rotEnemy.x + D3DX_PI) * 300.0f;
								pos.z = posEnemy.z + cosf(rotEnemy.y + D3DX_PI * -0.85f) * 300.0f;
							}

						}
					}

					m_apObject[nCnt]->SetPosition(pos);  //位置の設定
					m_apObject[nCnt]->SetRotation(rot);  //向きの設定

					//-------------------------------------------------------
					//モデルのデバック表示
					//-------------------------------------------------------
					//CManager::GetInstance()->GetDebugProc()->Print("剣上下カウント [%d]\n", m_apObject[nCnt]->m_nCntSword);
					//CManager::GetInstance()->GetDebugProc()->Print("ジャンプ [%d]\n", jamp);
				}
			}
		}
	}
}
//-------------------------------------------------------
//コアの破壊された数カウンターの設定
//-------------------------------------------------------
void CModelSet::SetnCntBreakCore(int nCntBreakCore)
{
	m_nCntBreakCore += nCntBreakCore;
}
//-------------------------------------------------------
//コアが壊れたかの確認の設定
//-------------------------------------------------------
void CModelSet::SetBreakCore(bool BreakCore)
{
	m_BreakCore = BreakCore;
}
//-------------------------------------------------------
//日本刀の攻撃3段階の設定
//-------------------------------------------------------
void CModelSet::SetSwordRot(SWORDROT SwordRot)
{
	m_SwordRot = SwordRot;
}
//-------------------------------------------------------
//ボスがダウンしてるかの設定
//-------------------------------------------------------
void CModelSet::SetBossCoreState(BOSSCORESTATE BossCoreState)
{
	m_BossCoreState = BossCoreState;
}