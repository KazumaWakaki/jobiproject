//=============================================================================
//
// ゲージ処理 [gauge.cpp]
// Author：若木一真
//
//=============================================================================
#include "manager.h"
#include "gauge.h"

//静的メンバ変数
CGauge *CGauge::m_apObject = NULL;

//-------------------------------------------------------
//コンストラクタ
//-------------------------------------------------------
CGauge::CGauge()
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apObject == NULL)
		{
			m_apObject = this;

			m_nID = nCnt;

			break;
		}
	}
}
//-------------------------------------------------------
//デストラクタ
//-------------------------------------------------------
CGauge::~CGauge()
{

}
//-------------------------------------------------------
//ゲージの初期化処理
//-------------------------------------------------------
HRESULT CGauge::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	m_nIdxTexture[TYPE_STEPFRAME] = pTexture->Regist("data\\texture\\attackgagecover001.png");
	m_nIdxTexture[TYPE_STEPGAUGE_GREEN] = pTexture->Regist("data\\texture\\attackgage001.png");
	m_nIdxTexture[TYPE_STEPGAUGE_ORANGE] = pTexture->Regist("data\\texture\\attackgage001.png");
	m_nIdxTexture[TYPE_STEPGAUGE_RED] = pTexture->Regist("data\\texture\\attackgage001.png");

	//オブジェクト2Dの初期化処理
	CObject2D::Init();

	//種類の設定
	CObject::SetType(TYPE_GAUGE);

	//初期化
	SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //位置
	SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //サイズ
	SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));  //スケール

	return (S_OK);
}
//-------------------------------------------------------
//ゲージの終了処理
//-------------------------------------------------------
void CGauge::Uninit(void)
{
	//オブジェクト2Dの終了処理
	CObject2D::Uninit();
}
//-------------------------------------------------------
//ゲージの更新処理
//-------------------------------------------------------
void CGauge::Update(void)
{
	//頂点情報の生成
	SetVtxUI();

	CPlayer3D::StepGaugeMove(this);
}
//-------------------------------------------------------
//ゲージの描画処理
//-------------------------------------------------------
void CGauge::Draw(void)
{
	//オブジェクト2Dの描画処理
	CObject2D::Draw();
}
//-------------------------------------------------------
//生成処理
//-------------------------------------------------------
CGauge *CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex)
{
	CGauge *pGauge = NULL;

	//ゲージの生成
	pGauge = new CGauge;

	//NULLじゃなかった時
	if (pGauge != NULL)
	{
		//初期化処理
		pGauge->Init();

		//位置設定
		pGauge->SetPosition(pos);

		//サイズ設定
		pGauge->SetSize(size);

		//スケール設定
		pGauge->SetScale(scale);

		//テクスチャタイプ設定
		pGauge->SetTypeTex(SetTypeTex);

		//頂点情報の生成
		pGauge->SetVtxUI();

		//nCount分回す
		for (int nCount = 0; nCount < TYPE_MAX; nCount++)
		{
			//nCountと選択されたモデルタイプが一致した時
			if (nCount == SetTypeTex)
			{
				//テクスチャの割り当て
				pGauge->BindTexture(pGauge->m_nIdxTexture[nCount]);
			}
		}
	}

	else
	{//生成に失敗した場合
		return NULL;
	}

	return pGauge;
}
//-------------------------------------------------------
//ステップゲージの設定処理
//-------------------------------------------------------
void CGauge::SetStepGauge(D3DXVECTOR3 StepGauge)
{
	m_nStepGauge = StepGauge;
}