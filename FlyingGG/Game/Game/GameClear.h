#pragma once

class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();

	void Update() {}
	void Render(CRenderContext&);

	CTexture back;
	CSprite back_sp;
};

