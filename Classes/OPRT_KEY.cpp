#include "OPRT_KEY.h"
#include "Player.h"

USING_NS_CC;

OPRT_KEY::OPRT_KEY(Node * sp)
{
	dir = Dir::NON;
	keyFlag = true;
	Init(sp);
}


OPRT_KEY::~OPRT_KEY()
{
}

void OPRT_KEY::Init(Node * sp)
{
	auto key = cocos2d::EventListenerKeyboard::create();
	key->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *KeyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			dir = Dir::LEFT;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			dir = Dir::RIGHT;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			dir = Dir::UP;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			dir = Dir::DOWN;
		}
		else
		{
		}
	};
	key->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *KeyEvent)
	{
		dir = Dir::NON;
		keyFlag = true;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(key, sp);

}

void OPRT_KEY::Update(Node * sp)
{
}
