#pragma once
#include "OPRT_STATE.h"
#include "cocos2d.h"

struct OPRT_TOUCH :public OPRT_STATE
{
public:
	OPRT_TOUCH();
	~OPRT_TOUCH();
	OPRT_TYPE GetType() { return OPRT_TYPE_TOUCH; }
	void Update(Node * sp);
private:

	Vec2 oldPos;	//タッチした時の座標
	Vec2 nowPos;	//動いてる時の座標
};

