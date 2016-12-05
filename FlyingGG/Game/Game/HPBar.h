#pragma once

class HPBar : public IGameObject
{
public:
	HPBar();
	~HPBar();

	void Update();

	void Render(CRenderContext&);

	CTexture hp;
	CSprite hpspr;
	CTexture hpb;
	CSprite hpbspr;

};

