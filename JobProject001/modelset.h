//=============================================================================
//
// [modelset.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _MODELSET_H_  //このマクロ定義がされてなかったら
#define _MODELSET_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"
#include "model.h"

class CPlayer3D;
class CEnemy3D;
class CBullet3D;

//マクロ定義
#define CHECKPOINT_COR (30.0f)  //チェックポイントの拡大率分補正
#define BOSSCORE_COR_X (41.0f)  //ボスコアの拡大率分補正X
#define BOSSCORE_COR_Y (100.0f)  //ボスコアの拡大率分補正Y
#define BOSSCORE_COR_Z (50.0f)  //ボスコアの拡大率分補正Z

//モデル設定クラス
class CModelSet : public CObjectX
{
public:
	//モデルタイプ種類
	typedef enum
	{
		TYPE_SWORD = 0,  //日本刀
		TYPE_CHECKPOINT,  //チェックポイント
		TYPE_BOSSCORE,  //ボスコア
		TYPE_BEAM_PLA,  //ビームプレイヤー
		TYPE_BEAM_ENE,  //ビーム敵
		TYPE_MAX
	}TYPE;

	//日本刀の攻撃3段階
	typedef enum
	{
		SWORDROT_0 = 0,  //攻撃していない
		SWORDROT_1,  //一段階目
		SWORDROT_2,  //二段階目
		SWORDROT_3,  //三段階目
		SWORDROT_MAX
	}SWORDROT;

	//ボスコアの状態
	typedef enum
	{
		BOSSCORESTATE_NONE = 0,  //ない
		BOSSCORESTATE_BREAK,  //壊された
		BOSSCORESTATE_LIVE,  //生きてる
		BOSSCORESTATE_MAX
	}BOSSCORESTATE;

	CModelSet();   //コンストラクタ
	~CModelSet();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);	 //終了処理
	virtual void Update(void);  //更新処理
	virtual void Draw(void);  //描画処理
	static CModelSet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex);  //生成処理
	void SwordRotMove(void);  //日本刀向き移動処理

	//当たり判定処理
	static bool ModelCollision(CPlayer3D *pPlayer);  //プレイヤーとの当たり判定処理
	static bool CollisionBullet(CBullet3D *pBullet);  //弾との当たり判定

	//移動処理
	static void SwordMove(CPlayer3D *pPlayer);  //日本刀攻撃移動量処理
	static void CoreMove(CEnemy3D *pEnemy);  //ボスのコア移動量処理

	//取得
	int GetnCntBreakCore(void) { return m_nCntBreakCore; };  //コアの破壊された数カウンターの取得
	SWORDROT GetSwordRot(void) { return m_SwordRot; }  //日本刀の攻撃3段階
	BOSSCORESTATE GetBossCoreState(void) { return m_BossCoreState; }  //コアが壊れたかの取得

	//設定
	void SetnCntBreakCore(int nCntBreakCore);  //コアの破壊された数カウンターの設定
	void SetBreakCore(bool BreakCore);  //コアが壊れたかの確認の設定
	void SetSwordRot(SWORDROT SwordRot);  //日本刀の攻撃3段階
	void SetBossCoreState(BOSSCORESTATE BossCoreState);  //コアが壊れたかの設定

private:
	int m_AttackSwordCnt;  //剣の攻撃カウント
	int m_nCntDown;  //ジャンプのカウント
	int m_nID;  //番号
	int m_nIdxTexture[TYPE_MAX];   //テクスチャ保存
	int m_nIdxModel[TYPE_MAX];     //モデル割り当て
	int m_nCntSword;  //日本刀の動きカウント
	int m_nCntSwordAttack;  //日本刀の向きカウント
	int m_nCntSwordRot;  //日本刀の向きカウント
	int m_nCntBeamScale;  //ビームのスケールカウント
	static int m_nCntBreakCore;  //コアの破壊された数カウンター
	bool m_BreakCore;  //コアが壊れたかの確認用
	BOSSCORESTATE m_BossCoreState;  //コアが壊れたかの管理
	D3DXVECTOR3 m_SwordTag;  //日本刀のターゲット
	D3DXVECTOR3 m_SwordRotTag;  //日本刀の向きターゲット
	SWORDROT m_SwordRot;  //日本刀の攻撃3段階
	static CModelSet *m_apObject[MAX_MODEL];  //オブジェクトクラスのポインタ
};

#endif