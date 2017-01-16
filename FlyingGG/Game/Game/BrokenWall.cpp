#include "stdafx.h"
#include "BrokenWall.h"
#include "Player.h"
#include "GameCamera.h"

extern Player *player;
extern GameCamera *gamecamera;


BrokenWall::BrokenWall()
{
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
}

BrokenWall::~BrokenWall()
{
}


void BrokenWall::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�B
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModel���������B
	skinModel.Init(modeldata.GetBody());
	//�f�t�H���g���C�g��ݒ肵�āB
	skinModel.SetLight(&light);
	//���[���h�s����X�V����B
	//���̃I�u�W�F�N�g�͓����Ȃ��̂ŁA�������ň�񂾂����[���h�s����쐬����΂����B
	skinModel.Update(position, rotation, CVector3::One);
	//skinModel.SetFogParam(enFogFuncDist, 0.0f, 30.0f);

	//���b�V���R���C�_�[�̍쐬�B
	meshCollider.CreateFromSkinModel(&skinModel, modeldata.GetBody()->GetRootBoneWorldMatrix());
	//���̂̍쐬�B
	RigidBodyInfo rbInfo;
	//���̂̃R���C�_�[��n���B
	rbInfo.collider = &meshCollider;
	//���̂̎��ʁB0.0���Ɠ����Ȃ��I�u�W�F�N�g�B�w�i�Ȃǂ�0.0�ɂ��悤�B
	rbInfo.mass = 0.0f;
	rbInfo.pos = position;
	rbInfo.rot = rotation;
	rigidBody.Create(rbInfo);
	//�쐬�������̂𕨗����[���h�ɒǉ�����B
	PhysicsWorld().AddRigidBody(&rigidBody);
}

void BrokenWall::Update()
{
	float pointlightcolor = 0.0f;
	CVector3 distance;
	distance.Subtract(player->position, position);
	pointlightcolor = distance.Length();
	if (distance.Length() > 4.0f)
	{
		pointlightcolor *= 4.0f;
	}
	else
	{
		pointlightcolor *= distance.Length();
	}
	light.SetPointLightPosition(player->position);
	light.SetPointLightColor({ pointlightcolor, pointlightcolor, pointlightcolor, 1.0f });
}

void BrokenWall::Break(CVector3& position)
{
	CVector3 distance;
	distance.Subtract(this->position, position);
	if (distance.Length() < 5.0f)
	{
		Delete();
	}
}

void BrokenWall::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void BrokenWall::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	DeleteGO(this);
}