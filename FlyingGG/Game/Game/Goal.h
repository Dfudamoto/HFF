#pragma once
class Goal : public IGameObject
{
public:
	Goal();

	~Goal();

	void Init(const char *, CVector3, CQuaternion);

	void Update();

	void Render(CRenderContext&);

	void Delete();

	int hp;
	CVector3 position;
	CQuaternion rotation;
	CSkinModelDataResources modelresource;
	CSkinModelDataHandle modeldata;
	CSkinModel model;
	CLight light;
	CRigidBody rigidbody;
	CMeshCollider meshcollider;


};

