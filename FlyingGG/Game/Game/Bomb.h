#pragma once
class Bomb : public IGameObject
{
public:
	Bomb();
	~Bomb();

	void Init(CSkinModelData*);

	void Init(CVector3);

	//更新関数
	void Update();

	//描画処理
	void Render(CRenderContext&);

	//何かに当たっているか判定する処理
	void CollCheck();

	CSkinModel model;			//モデル
	CSkinModelData modeldata;	//モデルデータ
	CLight light;				//ライト
	CVector3 position;			//場所
	CVector3 move_direction;	//飛ぶ方向
	CVector3 axisx;				//回転する軸
	CQuaternion rotation;		//モデルの向き
	float fallspeed;			//爆弾の落ちるスピード
	CCharacterController charactercontroller;
	bool start;
	CVector3 move_speed;		//爆弾の移動速度
	int angle;
};

