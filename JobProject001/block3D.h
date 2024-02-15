//=============================================================================
//
//[block3D.h]
//Author 若木 一真
//
//=============================================================================
#ifndef _BLOCK3D_H_  //このマクロ定義がされてなかったら
#define _BLOCK3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"

//マクロ定義
#define MAX_BLOCK (128)   //ブロックの最大数
#define NEONFLOOR_COL (30.0f)  //床の拡大率分補正
#define NEON_COL (300.0f)  //ネオンブロックの拡大率分補正

class CPlayer3D;
class CEnemy3D;

//ブロック3Dクラス
class CBlock3D : public CObjectX
{
public:
	//ブロックの種類
	typedef enum
	{
		BLOCK_NEONFLOOR = 0,  //ネオン床
		BLOCK_NEON,  //ネオンブロック
		BLOCK_NEONWALL,  //ネオン壁
		BLOCK_MAX
	}BLOCK;

	CBlock3D();   //コンストラクタ
	~CBlock3D();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);  //終了処理
	virtual void Update(void);  //更新処理
	virtual void Draw(void);  //描画処理
	static CBlock3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, int SetTypeTex);  //生成処理

	//当たり判定
	static bool CollisionPlayer(CPlayer3D *pPlayer);  //プレイヤーとの当たり判定
	static bool CollisionEnemy(CEnemy3D *pEnemy);   //敵との当たり判定

private:
	int m_nID;  //番号
	int m_nIdxTexture;   //テクスチャ保存
	int m_nIdxModel[BLOCK_MAX];  //モデル割り当て
	static CBlock3D *m_apObject[MAX_BLOCK];  //オブジェクトクラスのポインタ
};

#endif