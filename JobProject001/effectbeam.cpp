//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author 若木 一真
//
//=============================================================================
#include "effectbeam.h"
#include "manager.h"

//マクロ定義
#define EXPLOSIONAMIME (5)  //アニメーション速度
#define EXPLOSIONPATTERNAMIME (8)  //アニメーションパターン数
#define TEXSIZE_X	(20.0f)  //テクスチャのサイズX
#define TEXSIZE_Y	(20.0f)  //テクスチャのサイズY
#define TEXSIZE_Z	(20.0f)  //テクスチャのサイズZ
#define LIFE	 (3)  //寿命

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CEffectBeam::CEffectBeam()
{
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置の初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));      //サイズの初期化
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CEffectBeam::~CEffectBeam()
{

}
//-------------------------------------------------------
//初期化処理
//-------------------------------------------------------
HRESULT CEffectBeam::Init()
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//モデルを宣言
	m_nIdxTexture[EFFECTTYPE_BEAM] = pTexture->Regist("data\\texture\\Beam001.jpg");  //ビーム
	m_nIdxTexture[EFFECTTYPE_BLINKING] = pTexture->Regist("data\\texture\\blinking.png");  //点滅

	//サイズ初期化
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//オブジェクトビルボードの初期化処理
	CObject3D::Init();

	//種類の設定
	SetType(TYPE_EFFECT);

	return (S_OK);
}
//-------------------------------------------------------
//終了処理
//-------------------------------------------------------
void CEffectBeam::Uninit()
{
	//オブジェクトビルボードの終了処理
	CObject3D::Uninit();
}
//-------------------------------------------------------
//更新処理
//-------------------------------------------------------
void CEffectBeam::Update()
{
	D3DXVECTOR3 pos = GetPosition();  //位置取得
	D3DXVECTOR3 move = GetMove();  //移動量取得

	//位置の更新
	pos += move;

	//位置の設定
	SetPosition(pos);

	CObject3D::SetVtxEffect();

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
void CEffectBeam::Draw()
{
	//オブジェクトビルボードの描画処理
	CObject3D::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CEffectBeam *CEffectBeam::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex)
{
	CEffectBeam *pEffectBeam;

	//エフェクトの生成
	pEffectBeam = new CEffectBeam;

	//NULLじゃなかった時
	if (pEffectBeam != NULL)
	{
		//初期化処理
		pEffectBeam->Init();

		//位置の設定
		pEffectBeam->SetPosition(pos);

		//移動量の設定
		pEffectBeam->SetMove(move);

		//サイズ
		pEffectBeam->SetSize(size);

		//頂点情報の生成
		pEffectBeam->SetVtxEffect();

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pEffectBeam->BindTexture(pEffectBeam->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pEffectBeam;
}