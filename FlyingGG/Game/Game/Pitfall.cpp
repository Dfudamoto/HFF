#include "stdafx.h"
#include "Pitfall.h"
#include "GameCamera.h"
#include "Player.h"

extern Player* player;
extern GameCamera* gamecamera;


Pitfall::Pitfall()
{
}


Pitfall::~Pitfall()
{
}

void Pitfall::Update(){

}

void Pitfall::Render(CRenderContext& renderContext) {
	model.Draw(renderContext,
		gamecamera->camera.GetViewMatrix(),
		gamecamera->camera.GetProjectionMatrix()
	);
}