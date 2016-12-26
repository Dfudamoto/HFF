#include "stdafx.h"
#include "MapChip.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern CLight defaultlight;
extern Player *player;

MapChip::MapChip()
{
	light.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	maplight.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	maplight.SetAmbinetLight(CVector3::One);
}


MapChip::~MapChip()
{
}

void MapChip::Init(const char* modelName, CVector3 position, CQuaternion rotation)
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
	if (strcmp(modelName, "map") == 0)
	{
		skinModel.SetLight(&maplight);
	}
	else
	{
		skinModel.SetLight(&light);
	}
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
	skinModel.SetShadowCasterFlag(true);
	skinModel.SetShadowReceiverFlag(true);
}
void MapChip::Update()
{
	CVector3 direction;
	direction.Subtract(position, player->position);
	CVector3 distance = direction;
	//distance.Scale(0.05f);

	direction.Normalize();
	//direction.Scale(20.0f);
	float light_scale = 1.0f / distance.Length();
	//float light_limit = 3.0f;
	////if (light_scale > light_limit)
	//{
	//	light_scale = light_limit;
	//}
	direction.Scale(light_scale);
	light.SetDiffuseLightDirection(0, direction);
	maplight.SetPointLightColor({ 4.0f, 4.0f, 4.0f, 1.0f });
	maplight.SetPointLightPosition(player->position);
}
void MapChip::Render(CRenderContext& renderContext)
{
	skinModel.Draw(renderContext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}