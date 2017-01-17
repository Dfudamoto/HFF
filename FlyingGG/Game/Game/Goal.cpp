#include "stdafx.h"
#include "Goal.h"
#include "Scene.h"
#include "GameCamera.h"
#include "Player.h"

extern Scene *scene;
extern GameCamera *gamecamera;
extern Player *player;

Goal::Goal()
{
	hp = 3;
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
}


Goal::~Goal()
{
}

void Goal::Init(const char *modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	this->rotation = rotation;
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�B
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModel���������B
	model.Init(modeldata.GetBody());
	model.SetLight(&light);

	//���[���h�s����X�V����B
	//���̃I�u�W�F�N�g�͓����Ȃ��̂ŁA�������ň�񂾂����[���h�s����쐬����΂����B
	model.Update(position, rotation, CVector3::One);
	//skinModel.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
	model.SetShadowCasterFlag(true);
	model.SetShadowReceiverFlag(true);
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

void Goal::Update()
{
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	distance.Scale(0.2f);
	float light_scale = 1.0f / distance.Length();
	direction.Normalize();
	float light_limit = 1.0f;
	if (light_scale > light_limit)
	{
		light_scale = light_limit;
	}
	direction.Scale(light_scale);
	light.SetDiffuseLightDirection(0, direction);

	if (player->attackflg)
	{
		CVector3 distance;
		distance.Subtract(player->hitbox_position, position);
		if (distance.Length() < 4.0f)
		{
			hp--;
		}
	}
	model.Update(position, rotation, CVector3::One);
}

void Goal::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void Goal::Delete()
{
	model.SetShadowCasterFlag(false);
	PhysicsWorld().RemoveRigidBody(&rigidbody);
	rigidbody.Release();
	DeleteGO(this);
}
