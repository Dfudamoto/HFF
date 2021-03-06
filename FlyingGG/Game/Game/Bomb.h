#pragma once
class Bomb : public IGameObject
{
public:
	Bomb();
	~Bomb();

	void Init();

	void Init(CVector3);

	//更新関数
	void Update();

	//描画処理
	void Render(CRenderContext&);

	//何かに当たっているか判定する処理
	void CollCheck();

	//投げるか判定する処理
	void Throw();

	void Delete();

	CSkinModelDataResources	modelresource;
	CSkinModelDataHandle	modeldata;
	CSkinModel				model;				//モデル
	CLight					light;				//ライト
	CVector3				position;			//場所
	CVector3				move_direction;		//飛ぶ方向
	CVector3				axisx;				//回転する軸
	CQuaternion				rotation;			//モデルの向き
	float					fallspeed;			//落ちるスピード
	CCharacterController	charactercontroller;
	CVector3				move_speed;			//移動速度
	int						angle;				//回転する角度
	bool					throwflg;			//投げてるか
	bool					deleteflg;
};

