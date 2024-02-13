//=============================================================================
//
// [effect.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _EFFECT_H_  //このマクロ定義がされてなかったら
#define _EFFECT_H_  //2重インクルード防止のマクロを定義する

#include "billboard.h"

//マクロ定義
#define EFFECTSPEED (60.0f)   //スピード

//エフェクトクラス
class CEffect : public CBillboard
{
public:
	//エフェクトの種類
	typedef enum
	{
		EFFECTTYPE_BEAM = 0,  //ビーム
		EFFECTTYPE_BLINKING,  //点滅
		EFFECTTYPE_MAX
	}EFFECTTYPE;

	CEffect();   //コンストラクタ
	~CEffect();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);	 //終了処理
	void Update(void);	 //更新処理
	void Draw(void);	 //描画処理
	static CEffect *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, int SetTypeTex);  //エフェクト生成

private:
	D3DXCOLOR m_col;    //色
	int m_nLife;		//寿命
	int m_nIdxTexture[EFFECTTYPE_MAX];  //テクスチャ
};

#endif