#pragma once
#include "cocos2d.h"
#include <list>
USING_NS_CC;

enum class ANIM_ST 
{
	IDLE,
	RUN,
	JUMP,
	FALL
};
//std::function<bool(Sprite & sp)> func;

struct actModule
{
	ANIM_ST animID;
	EventKeyboard::KeyCode keyCode;
	//std::list<> blackList,

};

class actionCtl
{
public:
	actionCtl();
	~actionCtl();

	void MoveLR(int speed, Node * sp);
	void Jump(Node * sp);
	void Fall(Node * sp);

	float sy;		//ƒWƒƒƒ“ƒv—Í
	//float 
};

