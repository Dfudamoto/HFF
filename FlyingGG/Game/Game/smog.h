#pragma once

#include "tkEngine/shape/tkSphereShape.h"

class smog : public IGameObject
{
public:
	smog();
	~smog();

	//更新関数
	void Update();

	//描画処理
	void Render(CRenderContext&);

private:
	CVector3						m_position;
	CVector3 position;			//場所
};

