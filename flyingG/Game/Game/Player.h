#pragma once
#define MAX_ANGLE 90
#define MIN_ANGLE -90

class Player :	public IGameObject
{
public:
	Player();
	~Player();

	//更新関数
	void Update();

	//プレイヤーの移動処理
	void Move();

	//視点の回転
	void Rotation();
	
	//描画処理
	void Render(CRenderContext&);

	CVector3 position;			//場所
	CQuaternion rotation;		//プレイヤーの向き
	CSkinModel model;			//モデル
	CSkinModelData modeldata;	//モデルデータ
	CLight light;				//ライト
	CVector3 move_direction_z;	//正面へのベクトル
	CVector3 move_direction_x;	//横方向へのベクトル
};

