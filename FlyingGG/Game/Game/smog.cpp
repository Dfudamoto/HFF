#include "stdafx.h"
#include "smog.h"
#include"Player.h"

extern Player *player;

smog::smog()
{
	position = CVector3::Zero;
	position = { 20.0f, 23.0f, 10.0f };
}


smog::~smog()
{
}

void smog::Update() {
	CVector3 diff;
	diff.x = player->position.x - position.x;
	diff.y = player->position.y - position.y;
	diff.z = player->position.z - position.z;
	float length;
	length = diff.Length();
	if (length < 0.05) {
		MessageBox(NULL, NULL, "ƒ_ƒ[ƒW", MB_OK);
	}
	
	
}

void smog::Render(CRenderContext& rendercontext)
{
	//model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}