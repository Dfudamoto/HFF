#pragma once
class Pitfall : public IGameObject
{
public:
	Pitfall();
	~Pitfall();

	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);
	void Delete();

	CSkinModel				model;
	CSkinModelDataResources modelresource;
	CSkinModelDataHandle	modeldata;
	CLight					light;					//���f���̌�
	CVector3				position;				//HealingApple�̍��W
	CQuaternion				rotation;				//���f���̉�]�p�x
	CRigidBody				rigidbody;
	CMeshCollider			meshcollider;
};

