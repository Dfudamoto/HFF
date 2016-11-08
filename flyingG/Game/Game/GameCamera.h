#pragma once

class GameCamera :	public IGameObject
{
public:
	GameCamera();
	~GameCamera();

	void Update();

	CCamera camera;
};

