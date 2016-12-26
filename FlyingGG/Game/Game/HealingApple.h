#pragma once
class HealingApple : public IGameObject
{
public:
	HealingApple();
	~HealingApple();
	
	void Update();
	
	void Render(CRenderContext& renderContext);
	
	void Init(const char *, CVector3, CQuaternion);

	void Move();
	
	void Delete();

	void PickUp();

	CSkinModel				model;					//モデル
	CLight					light;					//モデルの光
	CVector3				position;				//HealingAppleの座標
	CQuaternion				rotation;				//モデルの回転角度
	CCharacterController	charactercontroller;	
	bool					harves;					//木に生ってるか
	CSkinModelDataHandle	modeldata;
	CSkinModelDataResources modelresource;
	bool					deleteflg;
};

