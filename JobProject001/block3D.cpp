//=============================================================================
//
// ブロック3D処理 [block3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "block3D.h"
#include "manager.h"
#include "player3D.h"
#include "enemy3D.h"
#include "bullet3D.h"
#include "explosion.h"

//マクロ定義
#define CORRECTION	(6.0f)  //横の当たり判定補正

//静的メンバ変数
CBlock3D *CBlock3D::m_apObject[MAX_BLOCK] = {};

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CBlock3D::CBlock3D()
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
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
CBlock3D::~CBlock3D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CBlock3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //モデルのポインタ

	m_nIdxModel[BLOCK_NEONFLOOR] = pModel->Regist("data\\MODEL\\neonfloor001.x");  //床ブロック
	m_nIdxModel[BLOCK_NEON] = pModel->Regist("data\\MODEL\\neonwall001.x");  //ネオンブロック
	m_nIdxModel[BLOCK_NEONWALL] = pModel->Regist("data\\MODEL\\runwall001.x");  //ネオンブロック

	//モデルの初期化処理
	CObjectX::Init();

	//種類の設定
	CObject::SetType(TYPE_BLOCK);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CBlock3D::Uninit()
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
void CBlock3D::Update()
{
	//弾との当たり判定
	//CBullet3D::CollisionBlock(this);
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CBlock3D::Draw()
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CBlock3D *CBlock3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int SetTypeTex)
{
	CBlock3D *pBlock3D = nullptr;

	//ブロックの生成
	pBlock3D = new CBlock3D;

	if (pBlock3D != nullptr)
	{
		//初期化処理
		pBlock3D->Init();

		//位置の設定
		pBlock3D->SetPosition(pos);

		//向きの設定
		pBlock3D->SetRotation(rot);

		//拡大率の設定
		pBlock3D->SetScale(scale);

		//テクスチャタイプ
		pBlock3D->SetTypeTex(SetTypeTex);

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//モデルの割り当て
				pBlock3D->BindModel(pBlock3D->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pBlock3D;
}
//-------------------------------------------------------
//プレイヤーとの当たり判定
//-------------------------------------------------------
bool CBlock3D::CollisionPlayer(CPlayer3D *pPlayer)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	//ゲームパッドの取得
	CInputPad *pInputPad;
	pInputPad = CManager::GetInstance()->GetInputPad();

	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //ブロックの位置の取得
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //移動量の取得
			D3DXVECTOR3 m_Scale = m_apObject[nCnt]->GetScale();  //ブロックの拡大率の取得
			CObject::TYPE type;  //種類
			int typetex = m_apObject[nCnt]->GetTypeTex();  //敵の種類取得

			//種類を取得
			type = pPlayer->GetType();

			//種類がプレイヤーの場合
			if (type == CObject::TYPE_PLAYER)
			{
				D3DXVECTOR3 posPlayer = pPlayer->GetPosition();  //プレイヤーの位置
				D3DXVECTOR3 posOldPlayer = pPlayer->GetPositionOld();  //プレイヤーの過去の位置
				D3DXVECTOR3 movePlayer = pPlayer->GetMove();  //プレイヤーの移動量
				D3DXVECTOR3 rotPlayer = pPlayer->GetRotation();  //プレイヤーの向き
				D3DXVECTOR3 scalePlayer = pPlayer->GetScale();  //プレイヤーの拡大率

				//ネオン床
				if (typetex == BLOCK_NEONFLOOR)
				{
					//プレイヤーと重なった時
					if (m_pos.z - m_Scale.z * NEONFLOOR_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
						&&  m_pos.z + m_Scale.z * NEONFLOOR_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
					{
						///////////////////////////////////
						//横の判定
						///////////////////////////////////
						if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
							&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posPlayer.y - scalePlayer.y)
						{
							if (m_pos.x - m_Scale.x * NEONFLOOR_COL > posOldPlayer.x + scalePlayer.x * PLAYER_COL_X
								&&  m_pos.x - m_Scale.x * NEONFLOOR_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X)
							{//ひだり。
								posPlayer.x = m_pos.x - m_Scale.x * NEONFLOOR_COL;  //ブロックの左から抜けない
								movePlayer.x = 0.0f;  //プレイヤーの移動量を0にする
							}

							if (m_pos.x + m_Scale.x * NEONFLOOR_COL < posOldPlayer.x - scalePlayer.x * PLAYER_COL_X
								&&  m_pos.x + m_Scale.x * NEONFLOOR_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X)
							{//ミギー。
								posPlayer.x = m_pos.x + m_Scale.x * NEONFLOOR_COL;  //ブロックの右から抜けない
								movePlayer.x = 0.0f;  //プレイヤーの移動量を0にする
							}
						}

						///////////////////////////////////
						//縦の判定
						///////////////////////////////////
						if ((m_pos.x - m_Scale.x * NEONFLOOR_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&& m_pos.x + m_Scale.x * NEONFLOOR_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X))
						{
							if (m_pos.y + m_Scale.y * NEONFLOOR_COL < posOldPlayer.y - scalePlayer.y + 2.0f
								&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posPlayer.y - scalePlayer.y + 2.0f)
							{//上だ。
								posPlayer.y = m_pos.y + m_Scale.y * NEONFLOOR_COL + 0.4f;  //ブロックの上に立たせる
								movePlayer.y = 0.0f;  //移動量を0にする
								pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_GROUND);  //プレイヤーを地上状態にする
								pPlayer->SetStepPossible(false);  //ステップ可能状態を有効にする
							}

							if (m_pos.y - m_Scale.y > posOldPlayer.y + scalePlayer.y * PLAYER_COL_X
								&&  m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_X)
							{//下だ。
								posPlayer.y = m_pos.y - m_Scale.y - 70.0f;  //ブロック抜けないようにする
								movePlayer.y = 0.0f;  //移動量を0にする
							}
						}
					}

					///////////////////////////////////
					//奥行きの判定
					///////////////////////////////////
					if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posPlayer.y - scalePlayer.y)
					{
						if (m_pos.x - m_Scale.x * NEONFLOOR_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  m_pos.x + m_Scale.x * NEONFLOOR_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X)
						{
							if (m_pos.z - m_Scale.z * NEONFLOOR_COL > posOldPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
								&&  m_pos.z - m_Scale.z * NEONFLOOR_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f)
							{//手前
								posPlayer.z = m_pos.z - m_Scale.z * NEONFLOOR_COL - 170.0f;  //ブロックの手前から抜けない
								movePlayer.z = 0.0f;  //プレイヤーの移動量を0にする
							}

							if (m_pos.z + m_Scale.z * NEONFLOOR_COL < posOldPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f
								&&  m_pos.z + m_Scale.z * NEONFLOOR_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
							{//奥
								posPlayer.z = m_pos.z + m_Scale.z * NEONFLOOR_COL + 170.0f;  //ブロックの奥から抜けない
								movePlayer.z = 0.0f;  //プレイヤーの移動量を0にする
							}
						}
					}
				}

				//ネオンブロック
				if (typetex == BLOCK_NEON)
				{
					if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  m_pos.y + m_Scale.y * NEON_COL > posPlayer.y - scalePlayer.y)
					{
						///////////////////////////////////
						//横の判定
						///////////////////////////////////
						if (m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
							&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
						{
							if (m_pos.x - m_Scale.x * NEON_COL > posOldPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f
								&&  m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f)
							{//左
								posPlayer.x = m_pos.x - m_Scale.x * NEON_COL - 180.0f;  //ブロックの左から抜けない
								movePlayer.x = 0.0f;  //プレイヤーの移動量を0にする
							}

							if (m_pos.x + m_Scale.x * NEON_COL < posOldPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f
								&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f)
							{//右
								posPlayer.x = m_pos.x + m_Scale.x * NEON_COL + 180.0f;  //ブロックの右から抜けない
								movePlayer.x = 0.0f;  //プレイヤーの移動量を0にする
							}
						}

						///////////////////////////////////
						//奥行きの判定
						///////////////////////////////////
						if (m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X
							&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X)
						{
							if (m_pos.z - m_Scale.z * NEON_COL > posOldPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
								&&  m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f)
							{//手前
								posPlayer.z = m_pos.z - m_Scale.z * NEON_COL - 170.0f;  //ブロックの手前から抜けない
								movePlayer.z = 0.0f;  //プレイヤーの移動量を0にする
							}

							if (m_pos.z + m_Scale.z * NEON_COL < posOldPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f
								&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
							{//奥
								posPlayer.z = m_pos.z + m_Scale.z * NEON_COL + 170.0f;  //ブロックの奥から抜けない
								movePlayer.z = 0.0f;  //プレイヤーの移動量を0にする
							}
						}
					}
				}

				//ネオン壁
				if (typetex == BLOCK_NEONWALL)
				{
					if (m_pos.y - m_Scale.y < posPlayer.y + scalePlayer.y * PLAYER_COL_Y
						&&  m_pos.y + m_Scale.y * NEON_COL > posPlayer.y - scalePlayer.y)
					{
						///////////////////////////////////
						//横の判定
						///////////////////////////////////
						if (m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
							&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
						{
							if (m_pos.x - m_Scale.x * NEON_COL > posOldPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f
								&&  m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f)
							{//左
								posPlayer.x = m_pos.x - m_Scale.x * NEON_COL - 179.0f;  //ブロックの左から抜けない

								//前に進む
								movePlayer.x += sinf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;
								movePlayer.z += cosf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;

								if (rotPlayer.y > 1.57f || rotPlayer.y < -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_R);  //プレイヤーを右からの壁走り状態にする
								}

								else if (rotPlayer.y < 1.57f || rotPlayer.y > -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_L);  //プレイヤーを左からの壁走り状態にする
								}
							}

							if (m_pos.x + m_Scale.x * NEON_COL < posOldPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f
								&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f)
							{//右
								posPlayer.x = m_pos.x + m_Scale.x * NEON_COL + 179.0f;  //ブロックの右から抜けない

								//前に進む
								movePlayer.x += sinf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;
								movePlayer.z += cosf(rotPlayer.y + D3DX_PI) * WALLRUNSPEED;

								if (rotPlayer.y > 1.57f || rotPlayer.y < -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_R);  //プレイヤーを右からの壁走り状態にする
								}

								else if (rotPlayer.y < 1.57f || rotPlayer.y > -1.57f)
								{
									pPlayer->SetPlayerJump(CPlayer3D::PLAYERJUMP_WALLRUN_L);  //プレイヤーを左からの壁走り状態にする
								}
							}
						}

						///////////////////////////////////
						//奥行きの判定
						///////////////////////////////////
						if (m_pos.x - m_Scale.x * NEON_COL < posPlayer.x + scalePlayer.x * PLAYER_COL_X + 150.0f
							&&  m_pos.x + m_Scale.x * NEON_COL > posPlayer.x - scalePlayer.x * PLAYER_COL_X - 150.0f)
						{
							if (m_pos.z - m_Scale.z * NEON_COL > posOldPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f
								&&  m_pos.z - m_Scale.z * NEON_COL < posPlayer.z + scalePlayer.z * PLAYER_COL_Z + 150.0f)
							{//手前
								posPlayer.z = m_pos.z - m_Scale.z * NEON_COL - 170.0f;  //ブロックの手前から抜けない
								movePlayer.z = 0.0f;  //プレイヤーの移動量を0にする
							}

							if (m_pos.z + m_Scale.z * NEON_COL < posOldPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f
								&&  m_pos.z + m_Scale.z * NEON_COL > posPlayer.z - scalePlayer.z * PLAYER_COL_Z - 150.0f)
							{//奥
								posPlayer.z = m_pos.z + m_Scale.z * NEON_COL + 170.0f;  //ブロックの奥から抜けない
								movePlayer.z = 0.0f;  //プレイヤーの移動量を0にする
							}
						}
					}
				}

				pPlayer->SetPosition(posPlayer);  //プレイヤーの位置の設定
				pPlayer->SetMove(movePlayer);  //プレイヤーの移動量の設定
			}
		}
	}
	
	return FALSE;
}
//-------------------------------------------------------
//敵との当たり判定
//-------------------------------------------------------
bool CBlock3D::CollisionEnemy(CEnemy3D *pEnemy)
{
	for (int nCnt = 0; nCnt < MAX_BLOCK; nCnt++)
	{
		//m_apObject[nCnt]がNULLじゃなかった時
		if (m_apObject[nCnt] != NULL)
		{
			D3DXVECTOR3 m_pos = m_apObject[nCnt]->GetPosition();  //ブロックの位置の取得
			D3DXVECTOR3 m_move = m_apObject[nCnt]->GetMove();  //移動量の取得
			D3DXVECTOR3 m_Scale = m_apObject[nCnt]->GetScale();  //ブロックのサイズの取得
			CObject::TYPE type;  //種類
			int typetex = m_apObject[nCnt]->GetTypeTex();  //敵の種類取得

			//種類を取得
			type = pEnemy->GetType();

			//種類が敵の場合
			if (type == CObject::TYPE_ENEMY)
			{
				D3DXVECTOR3 posEnemy = pEnemy->GetPosition();  //敵の位置の取得
				D3DXVECTOR3 posOldEnemy = pEnemy->GetPositionOld();  //敵の過去の位置の取得
				D3DXVECTOR3 moveEnemy = pEnemy->GetMove();  //敵の移動量の取得
				D3DXVECTOR3 scaleEnemy = pEnemy->GetScale();  //敵のサイズの取得

				if (typetex == BLOCK_NEONFLOOR)
				{
					///////////////////////////////////
					//横の判定
					///////////////////////////////////
					//プレイヤーと重なった時
					if (m_pos.z - m_Scale.z * NEONFLOOR_COL <= posEnemy.z + scaleEnemy.z * USUALLY_COR_Z
						&&  m_pos.z + m_Scale.z * NEONFLOOR_COL >= posEnemy.z - scaleEnemy.z * USUALLY_COR_Z)
					{
						if (m_pos.y - m_Scale.y < posEnemy.y + scaleEnemy.y * PLAYER_COL_Y
							&&  m_pos.y + m_Scale.y * NEONFLOOR_COL + 10.0f > posEnemy.y - scaleEnemy.y)
						{
							if (m_pos.x - m_Scale.x * NEONFLOOR_COL > posOldEnemy.x + scaleEnemy.x * USUALLY_COR_X
								&&  m_pos.x - m_Scale.x * NEONFLOOR_COL < posEnemy.x + scaleEnemy.x * USUALLY_COR_X)
							{//ひだり。
								posEnemy.x = m_pos.x - m_Scale.x * NEONFLOOR_COL;  //ブロックの左から抜けない
								moveEnemy.x = 0.0f;  //プレイヤーの移動量を0にする
							}

							if (m_pos.x + m_Scale.x * NEONFLOOR_COL < posOldEnemy.x - scaleEnemy.x * USUALLY_COR_X
								&&  m_pos.x + m_Scale.x * NEONFLOOR_COL > posEnemy.x - scaleEnemy.x * USUALLY_COR_X)
							{//ミギー。
								posEnemy.x = m_pos.x + m_Scale.x * NEONFLOOR_COL;  //ブロックの右から抜けない
								moveEnemy.x = 0.0f;  //プレイヤーの移動量を0にする
							}
						}
					}

					///////////////////////////////////
					//縦の判定
					///////////////////////////////////
					if (m_pos.z - m_Scale.z * NEONFLOOR_COL <= posEnemy.z + scaleEnemy.z * USUALLY_COR_Z
						&&  m_pos.z + m_Scale.z * NEONFLOOR_COL >= posEnemy.z - scaleEnemy.z * USUALLY_COR_Z)
					{
						if ((m_pos.x - m_Scale.x * NEONFLOOR_COL < posEnemy.x + scaleEnemy.x * USUALLY_COR_X
							&& m_pos.x + m_Scale.x * NEONFLOOR_COL > posEnemy.x - scaleEnemy.x * USUALLY_COR_X))
						{
							if (m_pos.y + m_Scale.y * NEONFLOOR_COL < posOldEnemy.y - scaleEnemy.y + 2.0f
								&&  m_pos.y + m_Scale.y * NEONFLOOR_COL > posEnemy.y - scaleEnemy.y + 2.0f)
							{//上だ。
								posEnemy.y = m_pos.y + m_Scale.y * NEONFLOOR_COL + 0.4f;  //ブロックの上に立たせる
								moveEnemy.y = 0.0f;  //移動量を0にする
							}

							if (m_pos.y - m_Scale.y > posOldEnemy.y + scaleEnemy.y * USUALLY_COR_Y
								&&  m_pos.y - m_Scale.y < posEnemy.y + scaleEnemy.y * USUALLY_COR_Y)
							{//下だ。
								posEnemy.y = m_pos.y - m_Scale.y - 70.0f;  //ブロック抜けないようにする
								moveEnemy.y = 0.0f;  //移動量を0にする
							}
						}
					}
				}

				pEnemy->SetPosition(posEnemy);  //敵の位置の設定
				pEnemy->SetMove(moveEnemy);  //敵の移動量の設定
			}
		}
	}

	return FALSE;
}