#pragma once
#include "cocos2d.h"
USING_NS_CC;

class OPRT_STATE;

class actionCtl
{
public:
	actionCtl();
	~actionCtl();

	void MoveLR(int speed, Node * sp);
	void Jump(float speed, Node * sp);
	void Fall(int speed, Node * sp);

	OPRT_STATE *oprt_state;
	bool jumpFlag;
	float sy;		//ƒWƒƒƒ“ƒv—Í
	//float 
};

