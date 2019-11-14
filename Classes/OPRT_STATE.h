#pragma once
#include "2d/CCScene.h"

USING_NS_CC;

enum OPRT_TYPE
{
	OPRT_TYPE_KEY,
	OPRT_TYPE_TOUCH,
	OPRT_TYPE_MAX
};
enum class Input
{
	NON,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Z,
	MAX
};

enum class KeyTrigger
{
	ON,
	OFF,
	MAX
};

enum class Input_info
{
	NOW,
	OLD,
	MAX
};

struct OPRT_STATE : public cocos2d::Node
{
public:
	OPRT_STATE();
	~OPRT_STATE();
	virtual OPRT_TYPE GetType() = 0;
	virtual void Update(Node * sp) = 0;
	Input input_key;
	KeyTrigger trigger_key;
	Input_info trigger_key_old;
	int trigger;
	bool keyFlag;
};

