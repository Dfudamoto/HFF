#pragma once

#include "tkEngine/shape/tkSphereShape.h"

class smog : public IGameObject
{
public:
	smog();
	~smog();

	//�X�V�֐�
	void Update();

	//�`�揈��
	void Render(CRenderContext&);

private:
	CVector3 m_position;
	CVector3 position;			//�ꏊ
};

