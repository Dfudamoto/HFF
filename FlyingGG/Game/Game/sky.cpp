#include "stdafx.h"
#include "sky.h"
#include "GameCamera.h"

extern CLight darklight;
extern GameCamera *gamecamera;

//モデルをテスト表示させるクソクラス
sky::sky()
{
	modeldata.LoadModelData("Assets/modelData/apple.X", NULL);
	model.Init(&modeldata);
	model.SetLight(&darklight);
	darklight.SetAmbinetLight({ 1.0f, 1.0f, 1.0f });
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