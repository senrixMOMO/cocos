#pragma once
#include "OPRT_STATE.h"
#include "cocos2d.h"

struct OPRT_KEY :public OPRT_STATE
{
public:
	OPRT_KEY(Node * sp);
	~OPRT_KEY();
	OPRT_TYPE GetType() { return OPRT_TYPE_KEY; }
	void Init(Node * sp);
	void Update(Node * sp);
private:
};

