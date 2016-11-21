#pragma once

#include "tkEngine/shape/tkSphereShape.h"

class smog : public IGameObject
{
public:
	smog();
	~smog();

	//XVŠÖ”
	void Update();

	//•`‰æˆ—
	void Render(CRenderContext&);

private:
	CVector3						m_position;
	CVector3 position;			//êŠ
};

