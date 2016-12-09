#pragma once

class ItemShow : public IGameObject
{
public:
	enum
	{
		APPLE,
		BOMB,
		KNIFE,
		ITEMNUM
	};

	ItemShow();
	~ItemShow();

	void Update();

	void Render(CRenderContext&);

	CSprite sprite;
	CTexture applet;
	CTexture bombt;
	CTexture knifet;
};

