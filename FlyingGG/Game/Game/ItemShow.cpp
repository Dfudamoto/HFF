#include "stdafx.h"
#include "ItemShow.h"
#include "Player.h"

extern Player *player;
int itemnum;

ItemShow::ItemShow()
{
	applet.ExLoad("Assets/sprite/apple.png");
	bombt.ExLoad("Assets/sprite/bomb.png");
	knifet.ExLoad("Assets/sprite/knife.png");
	debuffitemt.Load("Assets/sprite/Load.jpg");

	_0.ExLoad("Assets/sprite/0.png");
	_1.ExLoad("Assets/sprite/1.png");
	_2.ExLoad("Assets/sprite/2.png");
	_3.ExLoad("Assets/sprite/3.png");
	_4.ExLoad("Assets/sprite/4.png");
	_5.ExLoad("Assets/sprite/5.png");
	_6.ExLoad("Assets/sprite/6.png");
	_7.ExLoad("Assets/sprite/7.png");
	_8.ExLoad("Assets/sprite/8.png");
	_9.ExLoad("Assets/sprite/9.png");
	num1sprite.Init(&_0);
	num1sprite.SetPivot({ 0.5f, 0.5f });
	num1sprite.SetSize({ 50.0f, 100.0f });
	num1sprite.SetPosition({ -505.0f, -300.0f });
	num2sprite.Init(&_0);
	num2sprite.SetPivot({ 0.5f, 0.5f });
	num2sprite.SetSize({ 50.0f, 100.0f });
	num2sprite.SetPosition({ -480.0f, -300.0f });

	sprite.Init(&applet);
	sprite.SetPivot({ 0.5f, 0.5f });
	sprite.SetSize({100.0f, 100.0f});
	sprite.SetPosition({ -580.0f, -300.0f });
	itemnum = 0;

	sprite.SetTexture(&applet);

	
}


ItemShow::~ItemShow()
{
}


void ItemShow::Update()
{
	int num1 = 0;
	int num2 = 0;
	if (Pad(0).IsTrigger(enButtonLB1) && itemnum > 0)
	{
		itemnum--;
	}
	if (Pad(0).IsTrigger(enButtonRB1) && itemnum < ITEMNUM - 1)
	{
		itemnum++;

	}
	int i = 90;
	switch (itemnum)
	{
	case APPLE:
		sprite.SetTexture(&applet);
		num1 = player->applecount / 10;
		num2 = player->applecount % 10;
		break;
	case BOMB:
		sprite.SetTexture(&bombt);
		num1 = player->bombcount / 10;
		num2 = player->bombcount % 10;
		break;
	case KNIFE:
		sprite.SetTexture(&knifet);
		break;
	case DEBUFFITEM:
		sprite.SetTexture(&debuffitemt);
		num1 = player->debuffcount / 10;
		num2 = player->debuffcount % 10;
		break;

	}
	switch (num1)
	{
	case 0:
		num1sprite.SetTexture(&_0);
		break;
	case 1:
		num1sprite.SetTexture(&_1);
		break;
	case 2:
		num1sprite.SetTexture(&_2);
		break;
	case 3:
		num1sprite.SetTexture(&_3);
		break;
	case 4:
		num1sprite.SetTexture(&_4);
		break;
	case 5:
		num1sprite.SetTexture(&_5);
		break;
	case 6:
		num1sprite.SetTexture(&_6);
		break;
	case 7:
		num1sprite.SetTexture(&_7);
		break;
	case 8:
		num1sprite.SetTexture(&_8);
		break;
	case 9:
		num1sprite.SetTexture(&_9);
		break;
	}
	switch (num2)
	{
	case 0:
		num2sprite.SetTexture(&_0);
		break;
	case 1:
		num2sprite.SetTexture(&_1);
		break;
	case 2:
		num2sprite.SetTexture(&_2);
		break;
	case 3:
		num2sprite.SetTexture(&_3);
		break;
	case 4:
		num2sprite.SetTexture(&_4);
		break;
	case 5:
		num2sprite.SetTexture(&_5);
		break;
	case 6:
		num2sprite.SetTexture(&_6);
		break;
	case 7:
		num2sprite.SetTexture(&_7);
		break;
	case 8:
		num2sprite.SetTexture(&_8);
		break;
	case 9:
		num2sprite.SetTexture(&_9);
		break;
	}

}


void ItemShow::Render(CRenderContext& rendercontext)
{
	sprite.Draw(rendercontext);
	if (itemnum == BOMB || itemnum == APPLE || itemnum == DEBUFFITEM)
	{
		num1sprite.Draw(rendercontext);
		num2sprite.Draw(rendercontext);
	}
}