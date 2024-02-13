//=============================================================================
//
// [gauge.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _GAUGE_H_  //このマクロ定義がされなかったら
#define _GAUGE_H_  //2重インクルード防止のマクロ定義

#include "object2D.h"
#include "player3D.h"

class CGauge;

//ゲージクラス
class CGauge : public CObject2D
{
public:
	//ゲージタイプ種類
	typedef enum
	{
		GAUGETYPE_STEP = 0,  //ステップゲージ
		GAUGETYPE_S,  //ステップゲージ枠
		GAUGETYPE_MAX
	}GAUGETYPE;

	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_STEPFRAME = 0,  //ステップゲージ枠
		TYPE_STEPGAUGE_GREEN,  //ステップゲージ緑
		TYPE_STEPGAUGE_ORANGE,  //ステップゲージオレンジ
		TYPE_STEPGAUGE_RED,  //ステップゲージ赤
		TYPE_MAX
	}TEXTYPE;

	CGauge();   //コンストラクタ
	~CGauge();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理
	void Draw(void);  //描画処理
	static CGauge *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //ゲージ生成

	//取得
	D3DXVECTOR3 GetStepGauge(void) { return m_nStepGauge; };  //ステップゲージの段階取得

	//設定
	void SetStepGauge(D3DXVECTOR3 StepGauge);

private:
	int m_nID;  //番号
	D3DXVECTOR3 m_nStepGauge;  //ステップゲージ
	int m_nIdxTexture[TYPE_MAX];  //テクスチャ
	static CGauge *m_apObject;  //オブジェクトクラスのポインタ
};

#endif