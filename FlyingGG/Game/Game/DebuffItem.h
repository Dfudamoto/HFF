#pragma once

class DebuffItem : public IGameObject
{
public:
	DebuffItem();
	
	~DebuffItem();

	void Update();
	
	void Render(CRenderContext& renderContext);
	
	void Init(const char *, CVector3, CQuaternion);

	void Move();

	void PickUp();
	
	void Delete();

	void Eatable();

	CSkinModel				model;				//���f��
	CLight					light;				//���f���̌�
	CVector3				position;			//DebuffItem�̍��W
	CQuaternion				rotation;			//���f���̉�]
	CCharacterController	charactercontroller;
	bool					harves;				//�؂ɐ����Ă邩
	CSkinModelDataHandle	modeldata;
	CSkinModelDataResources modelresource;
	bool					deleteflg;
};

