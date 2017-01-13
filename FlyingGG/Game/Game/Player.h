#pragma once


#define MAX_ANGLE 75
#define MIN_ANGLE -75

class Player :	public IGameObject
{
public:
	Player();
	~Player();

	enum
	{
		WAIT,
		WALK,
		RUN,
		KNIFE,
		BOMBTHROW,
		ANIMATIONNUM
	};

	void Init(CVector3, CQuaternion);
	 
	//更新関数
	void Update();

	//プレイヤーの移動処理
	void Move();

	//視点の回転
	void Rotation();
	
	//描画処理
	void Render(CRenderContext&);

	//ボムが近くで爆発したらダメージをくらう処理。
	void BombDam(CVector3& bombpos);

	void NockBack();

	void Delete();

	int							bombcount;
	int							applecount;
	int							debuffcount;
	CVector3					position;			//場所
	CQuaternion					rotation;			//プレイヤーの向き
	CSkinModel					player_model;		//モデル
	CSkinModel					knife_model;
	CLight						light;				//ライト
	CCharacterController		characterController;
	float						radius;				//アイテムのあたり判定取るときの半径
	CSkinModelDataHandle		player_data;			//モデルデータ
	CSkinModelDataResources		player_modelresource;		//モデルデータハンドルを入れる媒体
	CSkinModelDataResources		knife_modelresource;		//モデルデータハンドルを入れる媒体
	CSkinModelDataHandle		knife_data;			//モデルデータ
	int							hp;					//プレイヤーの体力
	CAnimation					player_animation;
	CAnimation					knife_animation;
	int							animenum;		
	CVector3					hitbox_position;	//ナイフのポジション
	bool						nockbackflg;
	bool						speedup_flg;
	float						speedup_count;
	bool						attackflg;
};

