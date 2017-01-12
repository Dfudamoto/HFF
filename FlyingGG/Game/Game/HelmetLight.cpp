#include "stdafx.h"
#include "HelmetLight.h"
#include "GameCamera.h"
#include "Player.h"

extern GameCamera *gamecamera;
extern Player *player;
CLight darklight;		//暗いところにあるオブジェクト用のライト

HelmetLight::HelmetLight()
{
	modeldata.LoadModelData("Assets/modelData/bodyg.X", NULL);
	model.Init(&modeldata);
	light.SetAmbinetLight(CVector3::One);
	model.SetLight(&light);
	position = CVector3::Zero;
	rotation = CQuaternion::Identity;
	darklight.SetAmbinetLight({ 0.01f, 0.01f, 0.01f });
	darklight.SetDiffuseLightColor(2, { 0.9f, 0.9f, 0.9f, 1.0f });
	pickup = true;
	lightswitch = true;
	ShadowMap().SetCalcLightViewFunc(CShadowMap::enCalcLightViewFunc_PositionTarget);
}


HelmetLight::~HelmetLight()
{
}

void HelmetLight::Update()
{

	//プレイヤーが拾った状態
	if (pickup)
	{
		position = player->position;
		rotation = player->rotation;
	}
	CMatrix matrix = player->knife_model.GetWorldMatrix();
	CVector3 lightdirection;
	lightdirection.x = matrix.m[2][0];
	lightdirection.y = matrix.m[2][1];
	lightdirection.z = matrix.m[2][2];
	lightdirection.Normalize();


	//シャドウマップのライトの設定
	CVector3 lightposition = player->position;
	lightdirection.Add(lightposition);
	lightposition.y -= 0.4;
	lightdirection.y -= 1.0f;
	ShadowMap().SetLightPosition(lightposition);
	ShadowMap().SetLightTarget(lightdirection);
	ShadowMap().Update();
	Equip();
	model.Update(position, rotation, CVector3::One);
}

void HelmetLight::Equip()
{
	//装備を拾う時の距離判定
	CVector3 distance;
	distance.Subtract(position, player->position);
	if (distance.Length() < 2.0f && KeyInput().IsTrgger(CKeyInput::enKeyB))
	{
		pickup = true;
	}
	//ライトのON/OFFの切り替え
	if (Pad(0).IsTrigger(enButtonX))
	{
		//lightswitch = !lightswitch;
	}
}

void HelmetLight::Render(CRenderContext& rendercontext)
{
	if (pickup)
	{
		return;
	}
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}

void HelmetLight::Delete()
{
	if (this == nullptr)
	{
		return;
	}
	DeleteGO(this);
}

