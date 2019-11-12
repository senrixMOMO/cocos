#include "OPRT_TOUCH.h"

USING_NS_CC;

OPRT_TOUCH::OPRT_TOUCH()
{
	nowPos = Vec2(0, 0);
	oldPos = Vec2(0, 0);
}


OPRT_TOUCH::~OPRT_TOUCH()
{
}

void OPRT_TOUCH::Update(Node * sp)
{
	//create
	auto touch = cocos2d::EventListenerTouchOneByOne::create();

	//タッチした時
	touch->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		oldPos = touch->getLocation();
		return true;
	};

	//動いている時
	touch->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		nowPos = touch->getLocation();
		return true;
	};

	//離した時
	touch->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		oldPos = nowPos = Vec2(0, 0);
		return true;
	};

	//座標比較
	if (oldPos.x > nowPos.x)
	{
		sp->setPositionX(sp->getPositionX() - 1);
		input_key = Input::LEFT;
	}
	if (oldPos.x < nowPos.x)
	{
		sp->setPositionX(sp->getPositionX() + 1);
		input_key = Input::RIGHT;
	}
	if (oldPos.y < nowPos.y)
	{
		sp->setPositionY(sp->getPositionY() + 1);
	}
	if (oldPos.y > nowPos.y)
	{
		sp->setPositionY(sp->getPositionY() - 1);
	}

	//イベント追加
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, sp);
}
