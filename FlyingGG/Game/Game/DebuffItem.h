#pragma once

class DebuffItem : public IGameObject
{
public:
	DebuffItem();
	
	~DebuffItem();

	void Update();
	
	void Render(CRenderContext& renderContext);
	
	void Init(const char *, CVector3, CQuaternion);

	CSkinModelData			modeldata;			//���f���̃f�[�^
	CSkinModel				model;				//���f��
	CLight					light;				//���f���̌�
	CVector3				position;			//DebuffItem�̍��W
	CQuaternion				rotation;			//���f���̉�]
	CCharacterController	charactercontroller;
	bool					harves;				//�؂ɐ����Ă邩
};

