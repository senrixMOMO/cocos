#include "OPRT_KEY.h"
#include "Player.h"

USING_NS_CC;

OPRT_KEY::OPRT_KEY(Node * sp)
{
	input_key = Input::NON;
	trigger_key = KeyTrigger::OFF;
	trigger_key_old = Input_info::NOW;
	trigger = 1;
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
		trigger_key = KeyTrigger::ON;
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			input_key = Input::LEFT;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			input_key = Input::RIGHT;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			input_key = Input::UP;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			input_key = Input::DOWN;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_Z)
		{
			input_key = Input::Z;
		}
		else
		{
		}
	};
	key->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *KeyEvent)
	{
		trigger_key = KeyTrigger::OFF;
		input_key = Input::NON;
		keyFlag = true;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(key, sp);
}

void OPRT_KEY::Update(Node * sp)
{
	trigger = static_cast<int>(trigger_key);
	cocos2d::log("%d", trigger);
}
