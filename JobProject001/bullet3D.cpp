//=============================================================================
//
// 弾の処理(3D) [bullet3D.cpp]
// Author 若木 一真
//
//=============================================================================
#include "bullet3D.h"
#include "manager.h"
#include "explosion.h"
#include "block3D.h"
#include "effectbeam.h"
#include "modelset.h"

//マクロ定義
#define LIFE_ENEMY (150)  //敵の弾寿命
#define LIFE_PLAYER (150)  //プレイヤーの弾寿命
#define LIFE_PLAYERBOSS (50)  //プレイヤーボス戦の弾寿命
#define PLAYER_SPEED (5.0f)  //プレイヤーの弾の速度
#define ENEMY_SPEED (5.0f)  //敵の弾の速度

//静的メンバ変数
CBullet3D *CBullet3D::m_apObject[MAX_BULLET] = {};
bool CBullet3D::m_Beam = false;
//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CBullet3D::CBullet3D()
{
	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
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
CBullet3D::~CBullet3D()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CBullet3D::Init(void)
{
	//デバイスの取得
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	CModel *pModel = CManager::GetInstance()->GetModel();  //モデルのポインタ

	//モデルを宣言
	m_nIdxModel[BULLETTYPE_PLAYER] = pModel->Regist("data\\MODEL\\bullet001.x");  //プレイヤーの弾
	m_nIdxModel[BULLETTYPE_ENEMY] = pModel->Regist("data\\MODEL\\bullet001.x");  //敵の弾
	m_nIdxModel[BULLETTYPE_TUTORIAL] = pModel->Regist("data\\MODEL\\bullet001.x");  //敵のチュートリアル弾

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//値のクリア
	m_nLife = 0;
	m_nCntHit = 0;
	m_Beam = false;

	//種類の設定
	CObject::SetType(TYPE_BULLET);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CBullet3D::Uninit(void)
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
void CBullet3D::Update(void)
{
	D3DXVECTOR3 pos = GetPosition();  //位置の取得
	D3DXVECTOR3 move = GetMove();  //移動量の取得

	int nID = m_nID;

	//位置の更新
	pos += move;

	//位置の設定
	SetPosition(pos);

	m_nLife++;
	m_nCntHit++;

	if (m_Beam == false)
	{
		////ビーム生成
		//CModelSet::Create(D3DXVECTOR3(pos.x, pos.y, pos.z), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CModelSet::TYPE_BEAM);

		m_Beam = true;
	}



	//タイプがプレイヤーの時
	if (m_type == BULLETTYPE_PLAYER)
	{
		//弾が消えるまでのカウント
		if (m_nLife >= LIFE_PLAYER)
		{
			//削除処理
			Uninit();

			m_nLife = 0;  //0に戻す

			return;
		}

		//敵との当たり判定
		if (CEnemy3D::CollisionBullet(this))
		{
			return;
		}

		//モデルとの当たり判定
		if (CModelSet::CollisionBullet(this)) {
			return;
		}
	}

	//タイプが敵の時
	if (m_type == BULLETTYPE_ENEMY || m_type == BULLETTYPE_TUTORIAL)
	{
		if (m_nCntHit >= 10)
		{
			//プレイヤーとの当たり判定
			if (CPlayer3D::CollisionBullet(this) == true)
			{
				//自分の終了処理
				Uninit();

				m_nCntHit = 0;  //カウントを0にリセットする
			}
		}

		//弾が消えるまでのカウント
		if (m_nLife >= LIFE_ENEMY)
		{
			//削除処理
			Uninit();

			m_nLife = 0;  //0に戻す
		}
	}
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CBullet3D::Draw(void)
{
	//オブジェクトの描画処理
	CObjectX::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CBullet3D *CBullet3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int type)
{
	CBullet3D *pBullet = NULL;;

	//弾の生成
	pBullet = new CBullet3D;

	if (pBullet != NULL)
	{
		//初期化処理
		pBullet->Init();

		//位置の設定
		pBullet->SetPosition(pos);

		//移動量の設定
		pBullet->SetMove(move);

		//向きの設定
		pBullet->SetRotation(rot);

		//拡大率の設定
		pBullet->SetScale(scale);

		//種類の設定
		pBullet->SetTypeBullet(type);

		//ビームがない状態にする
		m_Beam = false;

		//弾の移動量設定
		pBullet->SetMove(move * ENEMY_SPEED);

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == type)
			{
				//モデルの割り当て
				pBullet->BindModel(pBullet->m_nIdxModel[nCount]);
			}
		}
	}

	else
	{
		//生成に失敗した場合
		return NULL;
	}

	return pBullet;
}
//-------------------------------------------------------
//ブロックとの当たり判定
//-------------------------------------------------------
bool CBullet3D::CollisionBlock(CBlock3D *pBlock)
{
	//サウンドの取得
	CSound *pSound;
	pSound = CManager::GetInstance()->GetSound();

	for (int nCnt = 0; nCnt < MAX_BULLET; nCnt++)
	{
		//NULLじゃないとき
		if (m_apObject[nCnt] != NULL)
		{
			CObject::TYPE type = pBlock->GetType();  //種類を取得

			//種類が弾の場合
			if (type == CObject::TYPE_BLOCK)
			{
				D3DXVECTOR3 pos = m_apObject[nCnt]->GetPosition();  //位置の取得
				D3DXVECTOR3 m_scale = m_apObject[nCnt]->GetScale();  //サイズの取得
				D3DXVECTOR3 posBlock = pBlock->GetPosition();  //ブロックの位置の取得
				D3DXVECTOR3 scaleBlock = pBlock->GetScale();  //ブロックのサイズの取得
				int typetex = pBlock->GetTypeTex();  //種類取得

				if (typetex == CBlock3D::BLOCK_NEONFLOOR)
				{
					//弾と重なった時
					if (pos.x + m_scale.x > posBlock.x - scaleBlock.x * NEONFLOOR_COL
						&&  pos.x - m_scale.x < posBlock.x + scaleBlock.x * NEONFLOOR_COL
						&&  pos.y + m_scale.y > posBlock.y - scaleBlock.y
						&&  pos.y - m_scale.y < posBlock.y + scaleBlock.y * NEONFLOOR_COL
						&&  pos.z + m_scale.z > posBlock.z - scaleBlock.z
						&&  pos.z - m_scale.z < posBlock.z + scaleBlock.z) 
					{
						//弾の終了処理
						m_apObject[nCnt]->Uninit();

						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
//-------------------------------------------------------
//弾の種類タイプの設定
//-------------------------------------------------------
void CBullet3D::SetTypeBullet(int Type)
{
	m_type = Type;
}