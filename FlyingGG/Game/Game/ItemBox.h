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

	CSkinModel				model;		//ƒ‚ƒfƒ‹
	CLight					light;		//ƒ‚ƒfƒ‹‚ÌŒõ
	CVector3				position;	//êŠ
	CQuaternion				rotation;	//ƒ‚ƒfƒ‹‚Ì‰ñ“]
	CRigidBody				rigidbody;	//„‘Ì
	CMeshCollider			meshcollider;
	CSkinModelDataHandle	modeldata;
	CSkinModelDataResources modelresource;
};

