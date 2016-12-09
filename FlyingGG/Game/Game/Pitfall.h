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
	CLight					light;					//���f���̌�
	CVector3				position;				//HealingApple�̍��W
	CQuaternion				rotation;				//���f���̉�]�p�x
	CCharacterController	charactercontroller;
};

