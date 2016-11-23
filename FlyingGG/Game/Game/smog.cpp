#include "stdafx.h"
#include "smog.h"


smog::smog()
{
	position = CVector3::Zero;
	position = { 20.0f, 23.0f, 10.0f };
}


smog::~smog()
{
}

void smog::Update() {
	/*CVector3 diff;
	diff.x = pos.x - m_position.x;
	diff.y = pos.y - m_position.y;
	diff.z = pos.z - m_position.z;
	float length;
	length = diff.Length();
	if (length < 0.05) {
		CGameObjectManager::Instance().DeleteGameObject(this);
	}
	*/
}

void smog::Render(CRenderContext& rendercontext)
{
	//model.Draw(rendercontext, gamecamera->camera.GetViewMatrix(), gamecamera->camera.GetProjectionMatrix());
}