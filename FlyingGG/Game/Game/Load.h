#pragma once

class Load : public IGameObject
{
public:
	Load();
	~Load();
	void Start();
	void Update();
	void Render(CRenderContext&);

	CTexture back;
	CSprite back_sp;
	int deletewindow;
	bool initflg;

};

