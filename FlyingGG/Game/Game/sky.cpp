#include "stdafx.h"
#include "sky.h"
#include "GameCamera.h"

extern CLight darklight;
extern GameCamera *gamecamera;

//���f�����e�X�g�\��������N�\�N���X
sky::sky()
{
	light.SetAmbinetLight(CVector3::One);
	modeldata.LoadModelData("Assets/modelData/apple.X", NULL);
	model.Init(&modeldata);
	model.SetLight(&light);
	rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(0));
	//model.SetShadowReceiverFlag(true);
}

sky::~sky()
{
}

void sky::Update()
{
	model.Update({ 0.0f, 0.0f, 0.0f }, CQuaternion::Identity, CVector3::One);
}

void sky::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}