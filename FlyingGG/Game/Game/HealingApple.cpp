#include "stdafx.h"
#include "HealingApple.h"
#include "GameCamera.h"
#include "Player.h"

extern Player* player;
extern GameCamera* gamecamera;


HealingApple::HealingApple()
{	
	//modeldata.LoadModelData("Assets/modelData/P47_0.X", NULL);
	//model.Init(&modeldata);
	light.SetAmbinetLight({ 0.01f,0.01f,0.01f });
	light.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	//model.SetLight(&light);
	harves = false;
	light.SetAmbinetLight(CVector3::One);
}


HealingApple::~HealingApple()
{

}

void HealingApple::Init(const char *modelname, CVector3 position, CQuaternion rotation)
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
	CVector3 movespeed = { 0.0f, 0.0f, 0.0 };
	charactercontroller.SetMoveSpeed(movespeed);
	charactercontroller.Init(0.3f, 0.3f, position);
	model.Update(position, rotation, CVector3::One);
}

void HealingApple::Update() 
{
	//�v���C���[�Ƃ̋������v�Z
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
	//�ړ��i�����j����
	charactercontroller.Execute();
	CVector3 movespeed = charactercontroller.GetMoveSpeed();
	charactercontroller.SetMoveSpeed(movespeed);
	position = charactercontroller.GetPosition();

	model.Update(position, rotation, CVector3::One);
}

void HealingApple::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}
