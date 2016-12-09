#pragma once
class HealingApple : public IGameObject
{
public:
	HealingApple();
	~HealingApple();
	void Update();
	void Render(CRenderContext& renderContext);
	void Init(const char *, CVector3, CQuaternion);

	CSkinModelData			modeldata;				//モデルのデータ
	CSkinModel				model;					//モデル
	CLight					light;					//モデルの光
	CVector3				position;				//HealingAppleの座標
	CQuaternion				rotation;				//モデルの回転角度
	CCharacterController	charactercontroller;	
	bool					harves;					//木に生ってるか
};

