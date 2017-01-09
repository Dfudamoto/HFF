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

	CSkinModel			model;		//���f��
	CSkinModelData		modeldata;	//���f���̃f�[�^
	CLight				light;		//���f���̌�
	CVector3			position;	//�ꏊ
	CQuaternion			rotation;	//���f���̉�]
	CRigidBody			rigidbody;	//����
	CMeshCollider		meshcollider;
	CCharacterController charactercontroller;
};

