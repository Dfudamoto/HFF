#pragma once


#define MAX_ANGLE 75
#define MIN_ANGLE -75

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

	CSkinModelData				bombdata;			//ボムのモデルデータ
	CVector3					position;			//場所
	CQuaternion					rotation;			//プレイヤーの向き
	CSkinModel					model;				//モデル
	CSkinModelData				modeldata;			//モデルデータ
	CLight						light;				//ライト
	CCharacterController		characterController;
	float						radius;				//アイテムのあたり判定取るときの半径
};

