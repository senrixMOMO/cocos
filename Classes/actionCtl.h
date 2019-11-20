#pragma once
#include "cocos2d.h"
#include <list>
USING_NS_CC;

class actionCtl
{
public:
	actionCtl();
	~actionCtl();

	void MoveLR(int speed, Node * sp);
	void Jump(Node * sp);
	void Fall(int speed, Node * sp);
	float sy;		//ƒWƒƒƒ“ƒv—Í
	//float 
};

