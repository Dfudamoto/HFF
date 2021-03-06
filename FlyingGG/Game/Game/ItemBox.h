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

	void Delete();

	CSkinModel				model;		//モデル
	CLight					light;		//モデルの光
	CVector3				position;	//場所
	CQuaternion				rotation;	//モデルの回転
	CRigidBody				rigidbody;	//剛体
	CMeshCollider			meshcollider;
	CSkinModelDataHandle	modeldata;
	CSkinModelDataResources modelresource;
	bool					deleteflg;
};

