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

	void ReInit();

	CSkinModel				model;				//モデル
	CLight					light;				//モデルの光
	CVector3				position;			//DebuffItemの座標
	CQuaternion				rotation;			//モデルの回転
	CCharacterController	charactercontroller;
	bool					harves;				//木に生ってるか
	CSkinModelDataHandle	modeldata;
	CSkinModelDataResources modelresource;
	bool					deleteflg;
	CVector3				initpos;
};

