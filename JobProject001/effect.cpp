//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author 若木 一真
//
//=============================================================================
#include "effect.h"
#include "manager.h"

//マクロ定義
#define EXPLOSIONAMIME (5)         //アニメーション速度
#define EXPLOSIONPATTERNAMIME (8)  //アニメーションパターン数
#define TEXSIZE_X	(20.0f)        //テクスチャのサイズX
#define TEXSIZE_Y	(20.0f)        //テクスチャのサイズY
#define TEXSIZE_Z	(20.0f)        //テクスチャのサイズZ
#define LIFE	    (3)           //寿命

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CEffect::CEffect()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置の初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //サイズの初期化
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CEffect::~CEffect()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CEffect::Init()
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//モデルを宣言
	m_nIdxTexture[EFFECTTYPE_BEAM] = pTexture->Regist("data\\texture\\Beam001.jpg");  //ビーム
	m_nIdxTexture[EFFECTTYPE_BLINKING] = pTexture->Regist("data\\texture\\Beam001.png");  //点滅

	//サイズ初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オブジェクトビルボードの初期化処理
	CBillboard::Init();

	//種類の設定
	SetType(TYPE_EFFECT);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CEffect::Uninit()
{
	//オブジェクトビルボードの終了処理
	CBillboard::Uninit();
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CEffect::Update()
{
	D3DXVECTOR3 pos = GetPosition();  //位置取得
	D3DXVECTOR3 move = GetMove();  //移動量取得

	//位置の更新
	pos += move;

	//位置の設定
	SetPosition(pos);

	CBillboard::SetVtxBullet();

	m_nLife++;

	//エフェクトが消えるまでのカウント
	if (m_nLife >= LIFE)
	{
		//削除処理
		Uninit();

		m_nLife = 0;  //0に戻す
	}
}
//-------------------------------------------------------
//描画処理
//-------------------------------------------------------
void CEffect::Draw()
{
	//オブジェクトビルボードの描画処理
	CBillboard::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex)
{
	CEffect *pEffect;

	//エフェクトの生成
	pEffect = new CEffect;

	//NULLじゃなかった時
	if (pEffect != NULL)
	{
		//初期化処理
		pEffect->Init();

		//位置の設定
		pEffect->SetPosition(pos);

		//移動量の設定
		pEffect->SetMove(move);

		//サイズ
		pEffect->SetSize(size);

		//頂点情報の生成
		pEffect->SetVtxBullet();

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pEffect->BindTexture(pEffect->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pEffect;
}