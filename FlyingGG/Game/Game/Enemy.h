#pragma once
class Enemy : public IGameObject
{
public:
	Enemy();
	~Enemy();

	void Init(const char *, CVector3, CQuaternion);
	
	void Update();

	void Move();

	void Delete();

	void Render(CRenderContext&);

	void NockBack();

	void NockBack2();

	void ReInit();

	CVector3				position;
	CQuaternion				rotation;
	CSkinModel				model;
	CSkinModelDataHandle	modeldata;
	CSkinModelDataResources	modelresource;
	CLight					light;
	CCharacterController	charactercontroller;
	float					timer;
	bool					discovery;
	bool					rotswitch;
	float					saverad;
	bool					reuse;
	int						reusecount;
	bool					nockbackflg;
	float					nockbacktimer;
	bool					revisionflg;
	float					revisionrad;
	int						sticknum;
	CVector3				move_angle;
	int						hp;
	bool					deleteflg;
	CQuaternion				initrot;
	CVector3				initpos;

};

