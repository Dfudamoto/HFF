#include "stdafx.h"
#include "sky.h"
#include "GameCamera.h"

extern CLight darklight;
extern GameCamera *gamecamera;

sky::sky()
{
	modeldata.LoadModelData("Assets/modelData/sky.x", NULL);
	model.Init(&modeldata);
	model.SetLight(&darklight);
	rotation.SetRotation(CVector3::AxisX, CMath::DegToRad(270));
	model.SetShadowReceiverFlag(true);
}


sky::~sky()
{
}

void sky::Update()
{
	model.Update({ 0.0f, 0.0f, 190.0f }, rotation, CVector3::One);
}

void sky::Render(CRenderContext& rendercontext)
{
	model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}