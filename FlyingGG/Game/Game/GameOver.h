#pragma once

class GameOver : public IGameObject
{
public:
	GameOver();
	
	~GameOver();

	void Update() {}

	void Render(CRenderContext&);

	CTexture back;
	CSprite back_sp;
};

