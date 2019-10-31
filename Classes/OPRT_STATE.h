#pragma once
#include "2d/CCScene.h"

USING_NS_CC;

enum OPRT_TYPE
{
	OPRT_TYPE_KEY,
	OPRT_TYPE_TOUCH,
	OPRT_TYPE_MAX
};
enum class Dir
{
	NON,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	MAX
};
struct OPRT_STATE : public cocos2d::Node
{
public:
	OPRT_STATE();
	~OPRT_STATE();
	virtual OPRT_TYPE GetType() = 0;
	virtual void Update(Node * sp) = 0;
	Dir dir;
	bool keyFlag;
};

