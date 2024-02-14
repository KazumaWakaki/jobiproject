//=============================================================================
//
// [enemy3D.h]
// Author 若木 一真
//
//=============================================================================
#ifndef _ENEMY3D_H_  //このマクロ定義がされてなかったら
#define _ENEMY3D_H_  //2重インクルード防止のマクロを定義する

#include "objectX.h"

//マクロ定義
#define ENEMYSPEED (3.0f)  //移動時のスピード
#define ENEMYSPEEDUP (0.15f)  //移動量更新時のスピード
#define ENEMY_COLLISION (50)  //当たり判定
#define MAX_ENEMY (30)  //最大数
#define USUALLY_COR_X (75.0f)  //通常敵の拡大率分補正X
#define USUALLY_COR_Y (168.0f)  //通常敵の拡大率分補正Y
#define USUALLY_COR_Z (66.0f)  //通常敵の拡大率分補正Z
#define BOSS_COR_X (1255.0f)  //ボスの拡大率分補正X
#define BOSS_COR_Y (1600.0f)  //ボスの拡大率分補正Y
#define BOSS_COR_Z (920.0f)  //ボスの拡大率分補正Z

class CBullet3D;
class CPlayer3D;
class CModelSet;
class CLife;

//敵クラス
class CEnemy3D : public CObjectX
{
public:
	//テクスチャタイプ種類
	typedef enum
	{
		TYPE_USUALLY = 0,  //通常敵
		TYPE_BOSS,  //ボス
		TYPE_TUTORIAL_ENE,  //チュートリアル敵
		TYPE_MAX
	}TYPE;

	//状態管理
	typedef enum
	{
		ENEMYSTATE_NORMAL = 0,  //通常状態
		ENEMYSTATE_DAMAGE,  //ダメージ状態
		ENEMYSTATE_MAX
	}ENEMYSTATE;

	//ボスの戦闘態勢状態
	typedef enum
	{
		BOSS_BATTEL_0 = 0,  //初期段階
		BOSS_BATTEL_1,  //段階1
		BOSS_BATTEL_2,  //段階2
		BOSS_BATTEL_3,  //段階3
		BOSS_BATTEL_MAX
	}BOSS_BATTEL;

	//チュートリアル敵状態管理
	typedef enum
	{
		TUTORIAL_ENESTATE_NORMAL = 0,  //ノーマルモード
		TUTORIAL_ENESTATE_ATTACKMODE,  //アタックモード
		TUTORIAL_ENESTATE_MAX
	}TUTORIAL_ENESTATE;

	CEnemy3D();   //コンストラクタ
	~CEnemy3D();  //デストラクタ

	//メンバ関数
	HRESULT Init(void);  //初期化処理
	void Uninit(void);   //終了処理
	void Update(void);   //更新処理
	void Draw(void);	 //描画処理
	static CEnemy3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXVECTOR3 size, int SetTypeTex, int Life);  //生成処理
	static void PlayerAttack(CPlayer3D *pPlayer);  //プレイヤー近接攻撃判定
	static void ShootBullet(CPlayer3D *pPlayer);  //弾を撃つ処理
	static void EnemyBattelState(CModelSet *pModelSet);  //敵別の戦闘態勢状態ごとの処理
	void UpdateEnemyState(void);  //状態
	static void LifeGauge(CLife *pLife);  //ライフゲージ

	//取得
	int GetLife(void) { return m_Life; };  //体力の取得
	BOSS_BATTEL GetBossBattel(void) { return m_BossBattel; };  //ボスの戦闘態勢状態の取得

	//設定
	void SetLife(int Life);  //体力の設定
	void SetBossDownState(bool BossDownState);  //ボスがダウンしてるかの設定
	void SetEnemyState(ENEMYSTATE state, int nCounterState);  //状態の設定
	void SetBossBattel(BOSS_BATTEL BossBattel);  //ボスの戦闘態勢状態の設定

	//当たり判定処理
	static void HitEnemy(int nDamage, int nCnt);  //ヒット処理
	static bool CollisionBullet(CBullet3D *pBullet);  //弾との当たり判定

private:
	int m_nIdxModel[TYPE_MAX];  //モデル割り当て
	int m_Life;  //体力
	int m_nID;  //番号
	int m_nCntHit;  //ダメージ状態のカウント
	int m_nCounterState;  //状態管理カウンター
	int m_nCounterMove;  //移動カウンター
	int m_nCntAttack;  //プレイヤーの近接攻撃カウンター
	int m_nCntEnemyBullet;  //弾カウンター
	int m_nCntDownSpeed;  //ボスがダウンするスピードカウンター
	bool m_BossDownState;  //ボスのダウン管理
	bool m_LifeGaugeSize;  //ライフゲージサイズの管理
	ENEMYSTATE m_state;  //状態管理
	BOSS_BATTEL m_BossBattel;  //ボスの戦闘態勢状態
	TUTORIAL_ENESTATE m_TutorialEne;  //チュートリアル敵状態管理
	static bool m_CreateCore;  //途中からコアを出す用
	static bool m_LifeState;  //ライフゲージ管理
	static CEnemy3D *m_apObject[MAX_ENEMY];  //オブジェクトクラスのポインタ
};

#endif