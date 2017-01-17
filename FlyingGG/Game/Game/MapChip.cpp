#include "stdafx.h"
#include "MapChip.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern CLight defaultlight;
extern Player *player;

MapChip::MapChip()
{
	light.SetAmbinetLight(CVector3::Zero);
	light.SetDiffuseLightColor(0, { 1.0f, 1.0f, 1.0f, 1.0f });
	maplight.SetAmbinetLight(CVector3::One);
	maplight.SetDiffuseLightColor(0, {0.05f, 0.05f, 0.05f, 1.0f});
	maplight.SetDiffuseLightDirection(0, { 0.0f, -1.0f, 0.0f });
	walllight.SetAmbinetLight(CVector3::Zero);
	signpostlight.SetAmbinetLight({1.0f, 1.0f, 1.0f});
}


MapChip::~MapChip()
{
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
{
	this->position = position;
	this->rotation = rotation;
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.x", modelName);
	//���f���f�[�^�����[�h�B
	modelresource.Load(modeldata, filePath, NULL);
	//CSkinModel���������B
	skinModel.Init(modeldata.GetBody());

	//�f�t�H���g���C�g��ݒ肵�āB
	if (strcmp(modelName, "map") == 0 || strcmp(modelName, "ground") == 0)
	{
		skinModel.SetLight(&maplight);
	}
	else if (strcmp(modelName, "signpost") == 0)
	{
		skinModel.SetLight(&signpostlight);
	}
	else
	{
		skinModel.SetLight(&light);
	}
	//���[���h�s����X�V����B
	//���̃I�u�W�F�N�g�͓����Ȃ��̂ŁA�������ň�񂾂����[���h�s����쐬����΂����B
	skinModel.Update(position, rotation, CVector3::One);
	//skinModel.SetFogParam(enFogFuncDist, 0.0f, 30.0f);
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
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
	modelname = modelName;
}
void MapChip::Update()
{
	if (strcmp(modelname, "ground") == 0)
	{
		float pointlightcolor = 4.0f;
		maplight.SetPointLightPosition(player->position);
		maplight.SetPointLightColor({ pointlightcolor, pointlightcolor, pointlightcolor, 1.0f });

	}
	else if (strcmp(modelname, "tree") == 0)
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

	}
	else if (strcmp(modelname, "wall") == 0)
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


	skinModel.Update(position, rotation, CVector3::One);
}
void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void MapChip::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	skinModel.SetShadowCasterFlag(false);
	PhysicsWorld().RemoveRigidBody(&rigidBody);
	rigidBody.Release();
	DeleteGO(this);

}