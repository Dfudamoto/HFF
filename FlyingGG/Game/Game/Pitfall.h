#pragma once
class Pitfall : public IGameObject
{
public:
	Pitfall();
	~Pitfall();

	void Init(const char* modelName, CVector3 position, CQuaternion rotation);
	void Update();
	void Render(CRenderContext& renderContext);

	CSkinModelData modeldata;
	CSkinModel model;
	CLight					light;					//モデルの光
	CVector3				position;				//HealingAppleの座標
	CQuaternion				rotation;				//モデルの回転角度
	CCharacterController	charactercontroller;
};

