#pragma once

class GameCamera : public IGameObject
{
public:
	GameCamera();

	~GameCamera();

	void Update();

	void render(CRenderContext&);

	CCamera camera;

};