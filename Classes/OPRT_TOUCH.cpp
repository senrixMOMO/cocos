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

	//�^�b�`������
	touch->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		oldPos = touch->getLocation();
		return true;
	};

	//�����Ă��鎞
	touch->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		nowPos = touch->getLocation();
		return true;
	};

	//��������
	touch->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		oldPos = nowPos = Vec2(0, 0);
		return true;
	};

	//���W��r
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

	//�C�x���g�ǉ�
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch, sp);
}
