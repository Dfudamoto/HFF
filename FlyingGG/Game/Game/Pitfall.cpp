#include "stdafx.h"
#include "Pitfall.h"
#include "GameCamera.h"
#include "Player.h"

extern Player* player;
extern GameCamera* gamecamera;


Pitfall::Pitfall()
{
}


Pitfall::~Pitfall()
{
}

void Pitfall::Init(const char *modelname, CVector3 position, CQuaternion rotation)
{
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//���f���f�[�^�����[�h�B
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModel���������B
	model.Init(modeldata.GetBody());
	//�f�t�H���g���C�g��ݒ肵�āB
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	CVector3 movespeed = { 0.0f, 0.0f, 0.0 };
	model.Update(position, rotation, CVector3::One);
	//���b�V���R���C�_�[�̍쐬�B
	meshcollider.CreateFromSkinModel(&model, modeldata.GetBody()->GetRootBoneWorldMatrix());
	//���̂̍쐬�B
	RigidBodyInfo rbInfo;
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &meshcollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidbody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&rigidbody);
}

void Pitfall::Update()
{
	if (player->position.y - position.y > HEIGHT + 0.3f)
	{
		return;
	}
	CVector3 distance;
	distance.Subtract(position, player->position);
	distance.y = 0;
	if (distance.Length() < 5.0f)
	{
		
		;
	}
}

void Pitfall::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}

void Pitfall::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	PhysicsWorld().RemoveRigidBody(&rigidbody);
	rigidbody.Release();
	DeleteGO(this);
}