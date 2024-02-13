//=============================================================================
//
// [life.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _LIFE_H_  //このマクロ定義がされなかったら
#define _LIFE_H_  //2重インクルード防止のマクロ定義

#include "object2D.h"

class CPlayer3D;
class CEnemy3D;

//ライフクラス
class CLife : public CObject2D
{
public:
	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_LIFEGAUGE = 0,  //ライフゲージ
		TYPE_LIFEFRAME,  //ライフ枠
		TYPE_BOSSLIFEGAUGE,  //ボスのライフゲージ
		TYPE_MAX
	}TYPE;

	//ゲージの段階分け
	typedef enum
	{
		LIFE_500 = 0,  //体力500
		LIFE_400,  //体力400
		LIFE_300,  //体力300
		LIFE_200,  //体力200
		LIFE_100,  //体力100
		LIFE_MAX
	}LIFETYPE;

	CLife();   //コンストラクタ
	~CLife();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);  //終了処理
	void Update(void);  //更新処理
	void Draw(void);  //描画処理
	static CLife *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 scale, int SetTypeTex);  //ライフ生成

	//取得
	int GetLife(void) { return m_nLife; };  //ライフの段階取得

	//設定
	void SetLife(int nLife);

private:
	int m_nID;  //番号
	int m_nLife;  //寿命
	int m_nIdxTexture[TYPE_MAX];  //テクスチャ
	static CLife *m_apObject;  //オブジェクトクラスのポインタ
};

#endif