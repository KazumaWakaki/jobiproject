//=============================================================================
//
// 敵処理 [enemy3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "enemy3D.h"
#include "manager.h"
#include "game.h"
#include "explosion.h"
#include "bullet3D.h"
#include "block3D.h"
#include "modelset.h"
#include "effect.h"

//マクロ定義
#define BULLETSPEED (10.0f)   //敵の弾スピード
#define BESTPOS (700.0f)  //敵の動いてくる最近距離
#define BESTPOSBOSS (1300.0f)  //ボスの動いてくる最近距離
#define USUALLY_RANGE (1000.0f)  //通常敵の検知範囲
#define BOSS_RANGE (4000.0f)  //ボスの検知範囲

//静的メンバ変数
CEnemy3D *CEnemy3D::m_apObject[MAX_ENEMY] = {};
bool CEnemy3D::m_CreateCore = false;
bool CEnemy3D::m_LifeState = false;
//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CEnemy3D::CEnemy3D()
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
CEnemy3D::~CEnemy3D()
{

}
//-------------------------------------------------------
//敵の初期化処理
//-------------------------------------------------------
HRESULT CEnemy3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //モデルのポインタ

	//モデルを宣言
	m_nIdxModel[TYPE_USUALLY] = pModel->Regist("data\\MODEL\\usually_enemy.x");  //通常敵
	m_nIdxModel[TYPE_BOSS] = pModel->Regist("data\\MODEL\\Boss_enemy.x");     //ボス
	m_nIdxModel[TYPE_TUTORIAL_ENE] = pModel->Regist("data\\MODEL\\usually_enemy.x");  //チュートリアル敵

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//値を初期化
	m_Life = 100;
	m_nCntHit = 0;
	m_nCounterMove = 0;
	m_nCntEnemyBullet = 0;
	m_nCntDownSpeed = 0;
	m_nCntAttack = 0;
	m_BossDownState = false;
	m_CreateCore = false;
	m_LifeState = false;
	m_LifeGaugeSize = false;
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_BossBattel = BOSS_BATTEL_0;
	CObject::SetType(TYPE_ENEMY);
	CObjectX::SetState(CObject::STATE_NORMAL, 0);

	return (S_OK);
}
//-------------------------------------------------------
//敵の終了処理
//-------------------------------------------------------
void CEnemy3D::Uninit(void)
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
//敵の更新処理
//-------------------------------------------------------
void CEnemy3D::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();  //位置の取得
	D3DXVECTOR3 move = GetMove();   //移動量の取得
	D3DXVECTOR3 rot = GetRotation();  //向きの取得
	D3DXVECTOR3 posPlayer;
	int typetex = GetTypeTex();  //種類取得

	SetPositionOld(pos);  //過去の位置設定

	//状態管理設定
	CObject::UpdateState();

	//状態管理
	UpdateEnemyState();

	//移動設定
	//MoveEnemy();

	if (typetex == TYPE_USUALLY)
	{
		//重力を加える
		move.y -= 4.0f;
	}

	m_nCntHit++;

	//位置の更新
	pos += move;

	//移動量を更新
	move.x += (0.0f - move.x) * ENEMYSPEEDUP;
	move.y += (0.0f - move.y) * ENEMYSPEEDUP;

	//角度の補正
	if (rot.y > D3DX_PI)
	{
		rot.y += -D3DX_PI * 2;
	}

	if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2;
	}

	SetPosition(pos);  //位置の設定
	SetMove(move);  //移動量の設定
	SetRotation(rot);  //向きの設定

	CBlock3D::CollisionEnemy(this);  //ブロックとの当たり判定
	CPlayer3D::CollisionEnemy(this);  //プレイヤーと敵との当たり判定
	CModelSet::CoreMove(this);  //ボスコア移動処理
}
//-------------------------------------------------------
//敵の描画処理
//-------------------------------------------------------
void CEnemy3D::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CEnemy3D *CEnemy3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life)
{
	CEnemy3D *pEnemy3D;

	//敵の生成
	pEnemy3D = new CEnemy3D;

	if (pEnemy3D != NULL)
	{
		//初期化処理
		pEnemy3D->Init();

		//位置の設定
		pEnemy3D->SetPosition(pos);

		//位置の設定
		pEnemy3D->SetPositionOld(pos);

		//移動量の設定
		pEnemy3D->SetMove(move);

		//向きの設定
		pEnemy3D->SetRotation(rot);

		//拡大率の設定
		pEnemy3D->SetScale(scale);

		//サイズ
		pEnemy3D->SetSize(size);

		//テクスチャタイプ
		pEnemy3D->SetTypeTex(SetTypeTex);

		//ライフの設定
		pEnemy3D->SetLife(Life);

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pEnemy3D->BindModel(pEnemy3D->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pEnemy3D;
}
//-------------------------------------------------------
//プレイヤーの戦闘
//-------------------------------------------------------
void CEnemy3D::PlayerAttack(CPlayer3D *pPlayer)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad = CManager::GetInstance()->GetInputPad();;

	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	CObject::TYPE type;  //種類

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			//種類を取得
			type = pPlayer->GetType();

			//種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //向きの取得
				D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //拡大率の取得
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //プレイヤーの向きの取得
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //プレイヤーの拡大率の取得
				D3DXVECTOR3 PLACOL = posPlayer;  //プレイヤーとの向きで当たり判定
				D3DXVECTOR3 BOSSCOL = pos;  //ボスとの向きで当たり判定
				int typetex = m_apObject[nCnt]->GetTypeTex();  //敵の種類取得
				PLACOL.x = posPlayer.x + sinf(rotPlayer.y) * PLAYER_COL_X;
				PLACOL.z = posPlayer.z + cosf(rotPlayer.y) * PLAYER_COL_Z;
				BOSSCOL.x = pos.x + sinf(rot.y) * BOSS_COR_X;
				BOSSCOL.z = pos.z + cosf(rot.y) * BOSS_COR_Z;

				//敵の範囲
				float fRangth = sqrtf((PLACOL.x - pos.x) * (PLACOL.x - pos.x) + (PLACOL.z - pos.z) * (PLACOL.z - pos.z));
				float fRangthBoss = sqrtf((BOSSCOL.x - posPlayer.x) * (BOSSCOL.x - posPlayer.x) + (BOSSCOL.z - posPlayer.z) * (BOSSCOL.z - posPlayer.z));

				//プレイヤーから判定される距離
				float fLength = 500.0f;
				float fLengthBoss = 2000.0f;

				float fRot = rotPlayer.y + D3DX_PI - rot.y;

				//角度の補正
				if (fRot > D3DX_PI)
				{
					fRot += -D3DX_PI * 2;
				}

				if (fRot < -D3DX_PI)
				{
					fRot += D3DX_PI * 2;
				}

				m_apObject[nCnt]->m_nCntAttack++;

				//攻撃キーを押したとき攻撃カウンターが50以上だったら
				if (pInputKeyboard->GetTrigger(DIK_V) == true && m_apObject[nCnt]->m_nCntAttack > 50
					|| pInputPad->GetTrigger(CInputPad::BUTTON_RB, 0) && m_apObject[nCnt]->m_nCntAttack > 50)
				{
					m_apObject[nCnt]->m_nCntAttack = 0;  //0に戻す

					if (typetex == TYPE_USUALLY)
					{
						//通常敵に当たった
						if (fRangth < fLength
							&& fRot < 0.5f
							&& fRot > -0.5f)
						{
							//敵のヒット処理
							HitEnemy(200, nCnt);
						}
					}

					if (typetex == TYPE_BOSS)
					{
						if (m_apObject[nCnt]->m_BossDownState == true)
						{
							//ボスに当たった
							if (fRangthBoss < fLengthBoss
								&& fRot < 0.5f
								&& fRot > -0.5f)
							{
								//敵のヒット処理
								HitEnemy(200, nCnt);
							}
						}
					}

					if (typetex == TYPE_TUTORIAL_ENE)
					{
						//チュートリアル敵に当たった
						if (fRangth < fLength
							&& fRot < 0.5f
							&& fRot > -0.5f)
						{
							//敵のヒット処理
							HitEnemy(200, nCnt);
						}
					}
				}

				if (typetex == TYPE_BOSS)
				{
					//-------------------------------------------------------
					//敵のデバック表示
					//-------------------------------------------------------
					//CManager::GetInstance()->GetDebugProc()->Print("ボスとの距離 [%f] : ボスの半径[ %f ]\n", fLengthBoss, fRangthBoss);
				}

				//-------------------------------------------------------
				//敵のデバック表示
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("敵の向き [%f, %f, %f]\n", rot.x, rot.y, rot.z);
				//CManager::GetInstance()->GetDebugProc()->Print("プレイヤーと敵の向き差分 [%f]\n", fRot);
				//CManager::GetInstance()->GetDebugProc()->Print("攻撃段階 [%d]\n", pPlayer->GetSwordAttack());
				//CManager::GetInstance()->GetDebugProc()->Print("攻撃カウント [%d]\n", m_apObject[nCnt]->m_nCntAttack);
			}
		}
	}
}
//-------------------------------------------------------
//弾を撃つ処理
//-------------------------------------------------------
void CEnemy3D::ShootBullet(CPlayer3D *pPlayer)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //向きの取得
			D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //スケールの取得
			int typetex = m_apObject[nCnt]->GetTypeTex();  //種類取得
			CObject::TYPE type = pPlayer->GetType();  //オブジェクトの種類を取得

			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置の取得
				D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //プレイヤーの過去の位置の取得
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //プレイヤーのスケール取得
				int PlaLife = pPlayer->GetLife();  //プレイヤーのライフ取得

				if (PlaLife <= 0)
				{
					if (typetex == TYPE_BOSS)
					{
						m_apObject[nCnt]->Uninit();
					}
				}

				//プレイヤーのリスタート状態が無効の時
				if (pPlayer->GetRestart() == false)
				{
					//=============================================
					//通常敵
					//=============================================
					if (typetex == TYPE_USUALLY)
					{
						float fAngleY = atan2f(posOldPlayer.z - pos.z, pos.x - posOldPlayer.x);

						D3DXVECTOR3 fAngle = D3DXVECTOR3(posOldPlayer.x - pos.x, (posOldPlayer.y + 50.0f) - pos.y, posOldPlayer.z - pos.z);
						D3DXVec3Normalize(&fAngle, &fAngle);

						rot.y = fAngleY + 1.57f;

						//プレイヤーが範囲内に入った時
						if (pos.x - scale.x * USUALLY_COR_X - USUALLY_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  pos.x + scale.x * USUALLY_COR_X + USUALLY_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
							&&  pos.y - scale.y * USUALLY_COR_Y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
							&&  pos.z - scale.z * USUALLY_COR_Z - USUALLY_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
							&&  pos.z + scale.z * USUALLY_COR_Z + USUALLY_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
						{
							if (m_apObject[nCnt]->m_nCntEnemyBullet == 60)
							{
								D3DXMATERIAL redMat;
								ZeroMemory(&redMat, sizeof(redMat));
								redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
								redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

								m_apObject[nCnt]->SetMat(1, redMat);
							}

							if (m_apObject[nCnt]->m_nCntEnemyBullet == 100)
							{
								m_apObject[nCnt]->ResetMat();

								//弾発射
								CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

								//ビーム生成
								CModelSet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, rot.y, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BEAM_ENE);

								m_apObject[nCnt]->m_nCntEnemyBullet = 0;  //リセット
							}

							m_apObject[nCnt]->m_nCntEnemyBullet++;  //敵の弾カウンター
						}

						//-------------------------------------------------------
						//敵のデバック表示
						//-------------------------------------------------------
						CManager::GetInstance()->GetDebugProc()->Print("敵の位置 [%f, %f, %f]\n", pos.x, pos.y, pos.z);
					}

					//=============================================
					//ボス
					//=============================================
					if (typetex == TYPE_BOSS)
					{
						float fAngleY = atan2f(posOldPlayer.z - pos.z, pos.x - posOldPlayer.x);

						D3DXVECTOR3 fAngle = D3DXVECTOR3(posOldPlayer.x - pos.x, (posOldPlayer.y + 50.0f) - pos.y, posOldPlayer.z - pos.z);
						D3DXVec3Normalize(&fAngle, &fAngle);

						rot.y = fAngleY + 1.57f;

						//プレイヤーがボスの見える範囲内に入った時
						if (pos.x - scale.x * USUALLY_COR_X - BOSS_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  pos.x + scale.x * USUALLY_COR_X + BOSS_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
							&&  pos.z - scale.z * USUALLY_COR_Z - BOSS_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
							&&  pos.z + scale.z * USUALLY_COR_Z + BOSS_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
						{
							if (m_apObject[nCnt]->m_LifeState == false)
							{
								//---------------------------------------------------------------
								//ライフゲージ生成
								//---------------------------------------------------------------
								CLife::Create(D3DXVECTOR3(100.0f, 80.0f, 0.0f), D3DXVECTOR3(1000.0f, 10.0f, 0.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), CLife::TYPE_BOSSLIFEGAUGE);

								m_apObject[nCnt]->m_LifeState = true;
							}

							//プレイヤーがボスの攻撃範囲内に入った時
							if (pos.x - scale.x * USUALLY_COR_X - BOSS_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
								&&  pos.x + scale.x * USUALLY_COR_X + BOSS_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
								&&  pos.z - scale.z * USUALLY_COR_Z - BOSS_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
								&&  pos.z + scale.z * USUALLY_COR_Z + BOSS_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
							{
								m_apObject[nCnt]->m_BossBattel = BOSS_BATTEL_1;  //ボスの戦闘態勢状態を一段階にする

								//ボスがダウン状態じゃないとき
								if (m_apObject[nCnt]->m_BossDownState == false)
								{
									if (m_apObject[nCnt]->m_nCntEnemyBullet == 60)
									{
										D3DXMATERIAL redMat;
										ZeroMemory(&redMat, sizeof(redMat));
										redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
										redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

										m_apObject[nCnt]->SetMat(1, redMat);
									}

									if (m_apObject[nCnt]->m_nCntEnemyBullet == 100)
									{
										m_apObject[nCnt]->ResetMat();

										//弾発射
										CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

										//ビーム生成
										CModelSet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, rot.y, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BEAM_ENE);

										m_apObject[nCnt]->m_nCntEnemyBullet = 0;  //リセット
									}

									m_apObject[nCnt]->m_nCntEnemyBullet++;  //敵の弾カウンター
								}
							}
						}
					}

					//=============================================
					//チュートリアル敵
					//=============================================
					if (typetex == TYPE_TUTORIAL_ENE)
					{
						//プレイヤーが範囲内に入った時
						if (pos.x - scale.x * USUALLY_COR_X - USUALLY_RANGE < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  pos.x + scale.x * USUALLY_COR_X + USUALLY_RANGE > posPlayer.x - scalePlayer.x * PLAYER_COL_X
							&&  pos.y - scale.y * USUALLY_COR_Y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
							&&  pos.z - scale.z * USUALLY_COR_Z - USUALLY_RANGE < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 130.0f
							&&  pos.z + scale.z * USUALLY_COR_Z + USUALLY_RANGE > posPlayer.z - scalePlayer.z * PLAYER_COL_Z + 130.0f)
						{
							float fAngleY = atan2f(posOldPlayer.z - pos.z, pos.x - posOldPlayer.x);

							D3DXVECTOR3 fAngle = D3DXVECTOR3(posOldPlayer.x - pos.x, (posOldPlayer.y + 50.0f) - pos.y, posOldPlayer.z - pos.z);
							D3DXVec3Normalize(&fAngle, &fAngle);

							rot.y = fAngleY + 1.57f;

							if (m_apObject[nCnt]->m_TutorialEne == TUTORIAL_ENESTATE_ATTACKMODE)
							{
								if (m_apObject[nCnt]->m_nCntEnemyBullet == 60)
								{
									D3DXMATERIAL redMat;
									ZeroMemory(&redMat, sizeof(redMat));
									redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
									redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

									m_apObject[nCnt]->SetMat(0, redMat);
								}

								if (m_apObject[nCnt]->m_nCntEnemyBullet == 100)
								{
									m_apObject[nCnt]->ResetMat();

									//弾発射
									CBullet3D::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(fAngle.x * BULLETSPEED, fAngle.y * BULLETSPEED, fAngle.z * BULLETSPEED), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.8f, 0.8f, 0.8f), CBullet3D::BULLETTYPE_ENEMY);

									m_apObject[nCnt]->m_nCntEnemyBullet = 0;  //リセット
								}

								m_apObject[nCnt]->m_nCntEnemyBullet++;  //敵の弾カウンター
							}
						}
					}
				}
			}

			//設定
			m_apObject[nCnt]->SetPosition(pos);  //位置の設定
			m_apObject[nCnt]->SetRotation(rot);  //向きの設定
		}
	}
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CEnemy3D::UpdateEnemyState(void)
{
	switch (m_state)
	{
	case ENEMYSTATE_NORMAL:

		for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
		{
			//m_apObject[nCnt]がNULLじゃなかった時
			if (m_apObject[nCnt] != NULL)
			{
				m_apObject[nCnt]->m_LifeGaugeSize = false;  //ライフゲージサイズが変更出来ない状態にする
			}
		}
		break;

	case ENEMYSTATE_DAMAGE:

		m_nCounterState--;

		if (m_nCounterState <= 0)
		{
			m_state = ENEMYSTATE_NORMAL;

			for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
			{
				//m_apObject[nCnt]がNULLじゃなかった時
				if (m_apObject[nCnt] != NULL)
				{
					m_apObject[nCnt]->ResetMat();
				}
			}

			break;
		}
	}
}
//-------------------------------------------------------
//敵の戦闘態勢ごとの処理
//-------------------------------------------------------
void CEnemy3D::EnemyBattelState(CModelSet *pModelSet)
{
	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
			D3DXVECTOR3 move = m_apObject[nCnt]->GetMove();  //移動量の取得
			D3DXVECTOR3 rot = m_apObject[nCnt]->GetRotation();  //向きの取得
			D3DXVECTOR3 scale = m_apObject[nCnt]->GetScale();  //スケールの取得
			BOSS_BATTEL BossBattel = m_apObject[nCnt]->GetBossBattel();  //ボスの戦闘態勢状態の取得
			int typetex = m_apObject[nCnt]->GetTypeTex();  //テクスチャタイプ取得
			int BossCoreState = pModelSet->GetBossCoreState();  //ボスコアの状態を取得

			//通常敵の処理
			if (typetex == TYPE_USUALLY)
			{

			}

			//ボスの処理
			if (typetex == TYPE_BOSS)
			{
				if (BossBattel == BOSS_BATTEL_1)
				{
					//コアがないとき
					if (BossCoreState == pModelSet->BOSSCORESTATE_NONE)
					{
						if (m_CreateCore == false)
						{
							//一個目のコアを出す (番号5)
							CModelSet::Create(D3DXVECTOR3(pos.x - 200.0f, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//二個目のコアを出す (番号6)
							CModelSet::Create(D3DXVECTOR3(pos.x + 200.0f, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//三個目のコアを出す (番号7)
							CModelSet::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//四個目のコアを出す (番号8)
							CModelSet::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							//五個目のコアを出す (番号9)
							CModelSet::Create(D3DXVECTOR3(pos.x, pos.y - 200.0f, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.5f, 1.5f, 1.5f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BOSSCORE);

							m_CreateCore = true;
							pModelSet->SetBossCoreState(pModelSet->BOSSCORESTATE_LIVE);
						}
					}

					//ボスの体力が1000以下になった時
					if (m_apObject[nCnt]->m_Life <= 0)
					{
						m_apObject[nCnt]->SetBossBattel(BOSS_BATTEL_2);  //二段階目にする
						m_apObject[nCnt]->m_BossDownState = false;  //ダウン状態から復帰する
						m_CreateCore = false;  //コアがない状態にする

						rot.x += 0.005f;  //ボスがダウンから戻る速度

						if (rot.x > -0.09f)
						{
							rot.x = -0.09f;  //元に戻す
							pModelSet->SetBreakCore(false);  //コアが壊れていない状態にする
						}
					}
				}

				//二段階目のとき
				if (BossBattel == BOSS_BATTEL_2)
				{
					//コアがないとき
					if (BossCoreState == pModelSet->BOSSCORESTATE_NONE)
					{
						if (m_CreateCore == false)
						{
							m_CreateCore = true;

							pModelSet->SetBossCoreState(pModelSet->BOSSCORESTATE_LIVE);  //コアがある状態にする
						}
					}
				}

				//コアが壊れたとき
				if (pModelSet->GetBossCoreState() == pModelSet->BOSSCORESTATE_BREAK && m_apObject[nCnt]->m_BossDownState == false)
				{
					m_apObject[nCnt]->m_nCntDownSpeed++;

					if (m_apObject[nCnt]->m_nCntDownSpeed > 60)
					{
						m_apObject[nCnt]->m_BossDownState = true;
						m_apObject[nCnt]->m_nCntDownSpeed = 0;
						pModelSet->SetBossCoreState(pModelSet->BOSSCORESTATE_NONE);  //コアがない状態にする
						m_apObject[nCnt]->ResetMat();  //色を戻す
					}
				}

				//ボスがダウン状態のとき
				if (m_apObject[nCnt]->m_BossDownState == true)
				{
					rot.x -= 0.004f;  //ボスがダウンする速度
					rot.y = 0.0f;

					if (rot.x < -1.2f)
					{
						rot.x = -1.2f;
					}
				}

				if (m_apObject[nCnt]->m_nCntDownSpeed > 100)
				{
					m_apObject[nCnt]->m_nCntDownSpeed = 100;
				}

				m_apObject[nCnt]->SetPosition(pos);  //位置の設定
				m_apObject[nCnt]->SetRotation(rot);  //向きの設定

				//-------------------------------------------------------
				//敵のデバック表示
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("ボスがダウンするスピード [%d]\n", m_apObject[nCnt]->m_nCntDownSpeed);
			}
		}
	}
}
//-------------------------------------------------------
//敵のヒット処理
//-------------------------------------------------------
void CEnemy3D::HitEnemy(int nDamage, int nCnt)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	if (m_apObject[nCnt] != NULL)
	{
		D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
		int typetex = m_apObject[nCnt]->GetTypeTex();

		m_apObject[nCnt]->m_Life -= nDamage;  //ライフを減少させる

		if (m_apObject[nCnt]->m_Life <= 0)
		{
			//通常敵の時
			if (typetex == TYPE_USUALLY)
			{
				//爆発の生成
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), D3DXVECTOR3(200.0f, 200.0f, 0.0f));

				//死亡状態
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//自分の終了処理
				m_apObject[nCnt]->Uninit();
			}

			//ボスの時
			else if (typetex == TYPE_BOSS)
			{
				//爆発の生成
				CExplosion::Create(D3DXVECTOR3(pos.x, pos.y + 50.0f, pos.z), D3DXVECTOR3(200.0f, 200.0f, 0.0f));

				//死亡状態
				m_apObject[nCnt]->SetState(CObject::STATE_DEATH, 0);

				//自分の終了処理
				m_apObject[nCnt]->Uninit();

				//ゲームの状態の設定
				CGame::SetGameState(CGame::GAMESTATE_END, 60);
			}

			//SEの再生
			pSound->PlaySound(SOUND_LABEL_SE_EXPLOSION);
		}

		else
		{
			//通常敵の時
			if (typetex == TYPE_USUALLY || typetex == TYPE_BOSS)
			{
				m_apObject[nCnt]->SetState(CObject::STATE_DAMAGE, 20);  //ダメージ状態
				m_apObject[nCnt]->SetEnemyState(ENEMYSTATE_DAMAGE, 20);  //ダメージ状態

				D3DXMATERIAL redMat;
				ZeroMemory(&redMat, sizeof(redMat));
				redMat.MatD3D.Diffuse = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
				redMat.MatD3D.Emissive = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

				 m_apObject[nCnt]->SetMat(0, redMat);
				m_apObject[nCnt]->m_LifeGaugeSize = true;  //ライフゲージサイズが変更出来る状態にする
			}

			//チュートリアル敵の時
			if (typetex == TYPE_TUTORIAL_ENE)
			{
				m_apObject[nCnt]->SetState(CObject::STATE_DAMAGE, 20);  //ダメージ状態
				m_apObject[nCnt]->SetEnemyState(ENEMYSTATE_DAMAGE, 60);  //ダメージ状態
			}

			//SEの再生
			pSound->PlaySound(SOUND_LABEL_SE_DAMAGE);
		}
	}
}
//-------------------------------------------------------
//弾との当たり判定
//-------------------------------------------------------
bool CEnemy3D::CollisionBullet(CBullet3D *pBullet)
{
	//種類を取得
	CObject::TYPE type = pBullet->GetType();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
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
				int typetex = m_apObject[nCnt]->GetTypeTex();

				//通常の時
				if (typetex == TYPE_USUALLY)
				{
					//敵と重なった時
					if (pos.x + scale.x * USUALLY_COR_X > posBullet.x - scaleBullet.x * BULLET_COL_XZ
						&&  pos.x - scale.x * USUALLY_COR_X < posBullet.x + scaleBullet.x * BULLET_COL_XZ
						&&  pos.y + scale.y * USUALLY_COR_Y > posBullet.y - scaleBullet.y * BULLET_COL_Y
						&&  pos.y - scale.y < posBullet.y + scaleBullet.y
						&&  pos.z + scale.z * USUALLY_COR_Z > posBullet.z - scaleBullet.z * BULLET_COL_XZ
						&&  pos.z - scale.z * USUALLY_COR_Z < posBullet.z + scaleBullet.z * BULLET_COL_XZ)
					{
						//敵のヒット処理
						CEnemy3D::HitEnemy(100, nCnt);

						pBullet->Uninit();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//ライフゲージ
//-------------------------------------------------------
void CEnemy3D::LifeGauge(CLife *pLife)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	for (int nCnt = 0; nCnt < MAX_ENEMY; nCnt++)
	{
		if (m_apObject[nCnt] != NULL)
		{
			CObject::TYPE type = pLife->GetType();  //種類

			//種類がライフの場合
			if (type == CObject::TYPE_LIFE)
			{
				//種類を取得
				int typetexEnemy = m_apObject[nCnt]->GetTypeTex();
				int lifeEnemy = m_apObject[nCnt]->m_Life;  //ボスのライフ取得
				D3DXVECTOR3 GaugeSize = pLife->GetSize();  //テクスチャサイズの取得
				
				if (typetexEnemy == TYPE_BOSS)
				{
					if (lifeEnemy > 1100)
					{
						pLife->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
					}

					else if (lifeEnemy < 1100 && lifeEnemy > 500)
					{
						pLife->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
					}

					else if (lifeEnemy <= 400)
					{
						pLife->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					}

					//ダメージを受けた時
					if (m_apObject[nCnt]->m_state == ENEMYSTATE_DAMAGE && m_apObject[nCnt]->m_LifeGaugeSize == true)
					{
						GaugeSize.x -= 100.0f;  //テクスチャを小さくしていく
					}
				}

				//-------------------------------------------------------
				//敵のデバック表示
				//-------------------------------------------------------
				//CManager::GetInstance()->GetDebugProc()->Print("ボスのライフゲージサイズ [%f]\n", GaugeSize.x);
				
				pLife->SetSize(GaugeSize);
			}
		}
	}
}
//-------------------------------------------------------
//体力の設定処理
//-------------------------------------------------------
void CEnemy3D::SetLife(int Life)
{
	m_Life = Life;
}
//-------------------------------------------------------
//ボスがダウンしてるかの設定
//-------------------------------------------------------
void CEnemy3D::SetBossDownState(bool BossDownState)
{
	m_BossDownState = BossDownState;
}
//-------------------------------------------------------
//状態管理設定
//-------------------------------------------------------
void CEnemy3D::SetEnemyState(ENEMYSTATE state, int nCounterState)
{
	m_state = state;
	m_nCounterState = nCounterState;
}
//-------------------------------------------------------
//ボスの戦闘態勢状態
//-------------------------------------------------------
void CEnemy3D::SetBossBattel(BOSS_BATTEL BossBattel)
{
	m_BossBattel = BossBattel;
}