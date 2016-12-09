#pragma once
class ItemBox : public IGameObject
{
public:
	ItemBox();
	~ItemBox();

	void Update();

	void Init(const char*, CVector3&, CQuaternion&);

	void BombCreate();

	void Render(CRenderContext&);

	CSkinModel			model;		//モデル
	CSkinModelData		modeldata;	//モデルのデータ
	CLight				light;		//モデルの光
	CVector3			position;	//場所
	CQuaternion			rotation;	//モデルの回転
};

