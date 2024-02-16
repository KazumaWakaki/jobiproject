//=============================================================================
//
// [player3D.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _PLAYER3D_H_  //このマクロ定義がされてなかったら
#define _PLAYER3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"
#include "enemy3D.h"
#include "life.h"
#include "gauge.h"

class CBullet3D;
class CLife;
class CGauge;

//マクロ定義
#define PLAYERSPEED (5.5f)  //移動時のスピード
#define PLAYERSPEEDUP (0.2f)  //移動量更新時のスピード
#define STEPSPEED (100.0f)  //ステップ時のスピード
#define WALLRUNSPEED (8.0f)  //壁走りのスピード
#define WALLJAMPSPEED (250.0f)  //壁走りジャンプのスピード
#define PLAYER_COL_X (95.0f)  //プレイヤーの拡大率分補正X
#define PLAYER_COL_Y (400.0f)  //プレイヤーの拡大率分補正Y
#define PLAYER_COL_Z (66.0f)  //プレイヤーの拡大率分補正Z
#define PLALIFE (500)  //体力
#define PLASTAMINA_MAX (150)  //スタミナ上限
#define PLASTAMINA_HEAL (80)  //スタミナが回復するまでの時間
#define SLOW (80)  //スロー用

#if _DEBUG

//#define PLAYERSPEED (5.0f)  //移動時のスピード

#endif

//プレイヤー3Dクラス
class CPlayer3D : public CObjectX
{
public:
	//ジャンプ状態
	typedef enum
	{
		PLAYERJUMP_GROUND = 0,  //地面
		PLAYERJUMP_SKY,  //ジャンプ状態
		PLAYERJUMP_GETOFF,  //降下状態
		PLAYERJUMP_WALLRUN_R,  //壁走り状態右から
		PLAYERJUMP_WALLRUN_L,  //壁走り状態左から
		PLAYERJUMP_MAX
	}PLAYERJAMP;

	//日本刀の攻撃3段階
	typedef enum
	{
		SWORDATTACK_0 = 0,  //攻撃していない
		SWORDATTACK_1,  //一段階目
		SWORDATTACK_2,  //二段階目
		SWORDATTACK_3,  //三段階目
		SWORDATTACK_MAX
	}SWORDATTACK;

	//リスポーン状態
	typedef enum
	{
		STATERES_NONE = 0,  //通常
		STATERES_RESPAWN,  //リスポーン待機
		STATERES_MAX
	}STATERES;

	//ステップ状態
	typedef enum
	{
		STEPSTATE_NONE = 0,  //通常
		STEPSTATE_STEP,  //ステップ状態
		STEPSTATE_OUTSTAMINA,  //スタミナ切れ状態
		STEPSTATE_MAX
	}STEPSTATE;

	CPlayer3D();   //コンストラクタ
	~CPlayer3D();  //デストラクタ

	//メンバ関数
	virtual HRESULT Init(void);  //初期化処理
	virtual void Uninit(void);	 //終了処理
	virtual void Update(void);  //更新処理
	virtual void Draw(void);	 //描画処理
	static CPlayer3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size);  //生成処理
	void StepMode(void);  //ステップ状態

	//取得
	int GetLife(void) { return m_Life; };  //体力の取得
	bool GetStepPossible(void) { return m_StepPossible; };  //ステップ可能状態切り替え取得
	bool GetRestart(void) { return m_Restart; };  //リスタート状態切り替え取得
	PLAYERJAMP GetJamp(void) { return m_jump; }  //ジャンプしてるかの取得
	SWORDATTACK GetSwordAttack(void) { return m_SwordAttack; };  //日本刀の攻撃段階の取得
	STATERES GetStateRes(void) { return m_StateRes; };  //リスポーン状態の取得
	D3DXVECTOR3 GetStartPos(void) { return m_StartPos; };  //保存されているスタート位置の取得
	D3DXVECTOR3 GetKeepPos(void) { return m_KeepPos; };  //保存されている位置の取得

	//設定
	void SetLife(int Life);  //体力の設定
	void SetStepPossible(bool StepPossible);  //ステップ可能状態切り替えの設定
	void SetRestart(bool Restart);  //リスタート状態切り替え設定
	void SetPlayerJump(PLAYERJAMP Jamp);  //ジャンプ状態の設定
	void SetSwordAttack(SWORDATTACK SwordAttack);  //日本刀の攻撃段階の設定
	void SetStateRes(STATERES StateRes);  //リスポーン状態の設定
	void SetKeepPos(D3DXVECTOR3 KeepPos);  //保存されている位置の設定

	//当たり判定
	static void HitPlayer(int nDamage);  //プレイヤーのヒット処理
	static bool CollisionEnemy(CEnemy3D *pEnemy);  //敵との当たり判定
	static bool CollisionBullet(CBullet3D *pBullet);  //弾との当たり判定
	static void LifeMove(CLife *pLife);  //ライフ設定処理
	static void StepGaugeMove(CGauge *pGauge);  //ステップゲージ設定処理

private:
	int m_nIdxTexture;  //テクスチャ保存
	int m_nIdxMode;  //モデル割り当て
	int m_nCntDown;  //ジャンプのカウント
	int m_nCntAttack;  //アタックカウント
	int m_nCntStep;  //ステップのカウント
	int m_Life;  //体力
	int m_StepGauge;  //ステップゲージ
	int m_StepGaugeCnt;  //ステップカウントゲージ
	bool m_Step;  //ステップ状態切り替え
	bool m_StepPossible;  //ステップ可能状態切り替え
	bool m_Restart;  //リスタート状態切り替え
	static bool m_BossState;  //ボスが生成管理
	PLAYERJAMP m_jump;  //プレイヤーのジャンプ
	SWORDATTACK m_SwordAttack;  //日本刀の攻撃3段階
	STATERES m_StateRes;  //リスポーン状態
	STEPSTATE m_StepState;  //ステップ状態
	D3DXVECTOR3 m_StartPos;  //スタート位置
	D3DXVECTOR3 m_KeepPos;  //位置保存
	static CPlayer3D *m_apObject;  //オブジェクトクラスのポインタ
};

#endif