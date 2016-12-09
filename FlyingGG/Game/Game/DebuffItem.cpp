#include "stdafx.h"
#include "DebuffItem.h"
#include "GameCamera.h"
#include "Player.h"

extern Player *player;
extern GameCamera *gamecamera;

DebuffItem::DebuffItem()
{
	light.SetAmbinetLight({0.01f, 0.01f, 0.01f});
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	harves = false;
}

DebuffItem::~DebuffItem()
{
}

void DebuffItem::Init(const char *modelname, CVector3 position, CQuaternion rotation)
{
	//�t�@�C���p�X���쐬����B
	char filePath[256];
	sprintf(filePath, "Assets/modelData/%s.X", modelname);
	//���f���f�[�^�����[�h�B
	modeldata.LoadModelData(filePath, NULL);
	//CSkinModel���������B
	model.Init(&modeldata);
	//�f�t�H���g���C�g��ݒ肵�āB
	model.SetLight(&light);
	this->position = position;
	this->rotation = rotation;
	charactercontroller.SetMoveSpeed(CVector3::Zero);
	charactercontroller.Init(0.3f, 0.3f, position);
	model.Update(position, rotation, CVector3::One);
}

void DebuffItem::Update()
{
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (Pad(0).IsTrigger(enButtonX) && distance.Length() < player->radius)
	{
		harves = true;
	}
	if (!harves)
	{
		return;
	}
	distance.Normalize();
	light.SetDiffuseLightDirection(0, distance);
	charactercontroller.Execute();
	CVector3 movespeed = charactercontroller.GetMoveSpeed();
	charactercontroller.SetMoveSpeed(movespeed);
	position = charactercontroller.GetPosition();
	model.Update(position, rotation, CVector3::One);
}

void DebuffItem::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}
