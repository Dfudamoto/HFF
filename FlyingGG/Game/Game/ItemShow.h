#pragma once

class ItemShow : public IGameObject
{
public:
	enum
	{
		APPLE,
		DEBUFFITEM,
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
	CTexture debuffitemt;
	CSprite num1sprite;
	CSprite num2sprite;
	CTexture _0;
	CTexture _1;
	CTexture _2;
	CTexture _3;
	CTexture _4;
	CTexture _5;
	CTexture _6;
	CTexture _7;
	CTexture _8;
	CTexture _9;

};

