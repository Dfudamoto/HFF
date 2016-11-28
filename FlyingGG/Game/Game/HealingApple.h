#pragma once
class HealingApple : public IGameObject
{
public:
	HealingApple();
	~HealingApple();
	void Update();
	void Render(CRenderContext& renderContext);
	void Init(const char *, CVector3, CQuaternion);

	CSkinModelData			modeldata;				//���f���̃f�[�^
	CSkinModel				model;					//���f��
	CLight					light;					//���f���̌�
	CVector3				position;				//HealingApple�̍��W
	CQuaternion				rotation;				//���f���̉�]�p�x
	CCharacterController	charactercontroller;	
	bool					harves;					//�؂ɐ����Ă邩
};

