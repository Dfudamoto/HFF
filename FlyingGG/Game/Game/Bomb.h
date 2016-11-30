#pragma once
class Bomb : public IGameObject
{
public:
	Bomb();
	~Bomb();

	void Init();

	void Init(CVector3);

	//�X�V�֐�
	void Update();

	//�`�揈��
	void Render(CRenderContext&);

	//�����ɓ������Ă��邩���肷�鏈��
	void CollCheck();

	//�����邩���肷�鏈��
	void Throw();

	CSkinModelDataResources	modelresource;
	CSkinModelDataHandle	modeldata;
	CSkinModel				model;				//���f��
	CLight					light;				//���C�g
	CVector3				position;			//�ꏊ
	CVector3				move_direction;		//��ԕ���
	CVector3				axisx;				//��]���鎲
	CQuaternion				rotation;			//���f���̌���
	float					fallspeed;			//������X�s�[�h
	CCharacterController	charactercontroller;
	CVector3				move_speed;			//�ړ����x
	int						angle;				//��]����p�x
	bool					throwflg;			//�����Ă邩
};

