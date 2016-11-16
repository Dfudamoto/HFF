#include "stdafx.h"
#include "HelmetLight.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern Player *player;
CLight darklight;		//�Â��Ƃ���ɂ���I�u�W�F�N�g�p�̃��C�g

HelmetLight::HelmetLight()
{
	modeldata.LoadModelData("Assets/modelData/car.X", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = CVector3::Zero;
	rotation = CQuaternion::Identity;
	darklight.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	darklight.SetDiffuseLightColor(0, { 0.9f, 0.9f, 0.9f, 1.0f });
	getflg = true;
	lightswitch = true;
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionDirection);
}


HelmetLight::~HelmetLight()
{
}

void HelmetLight::Update()
{

	//�v���C���[���E�������
	if (getflg)
	{
		position = player->position;
		rotation = player->rotation;
	}
	CMatrix matrix = player->model.GetWorldMatrix();
	CVector3 lightdirection;
	lightdirection.x = matrix.m[2][0];
	lightdirection.y = matrix.m[2][1];
	lightdirection.z = matrix.m[2][2];
	//lightdirection.Normalize();
	CVector3 shadowdirection = lightdirection;
	lightdirection.Scale(-1.0f);

	if (lightswitch)
	{
		darklight.SetDiffuseLightDirection(0, CVector3(0.0f, 0.0f, 1.0f));
	}
	else
	{
		darklight.SetDiffuseLightDirection(0, CVector3::Zero);
	}
	//�V���h�E�}�b�v�̃��C�g�̐ݒ�
	CVector3 lightposition = player->position;
	ShadowMap().SetLightPosition(lightposition);
	ShadowMap().SetLightDirection(shadowdirection);

	Equip();

	model.Update(position, rotation, CVector3::One);

}

void HelmetLight::Equip()
{
	//�������E�����̋�������
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < 2.0f && KeyInput().IsTrgger(CKeyInput::enKeyB))
	{
		getflg = true;
	}
	//���C�g��ON/OFF�̐؂�ւ�
	if (Pad(0).IsTrigger(enButtonX))
	{
		//lightswitch = !lightswitch;
	}
}

void HelmetLight::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}


