#include "actionCtl.h"
#include "OPRT_STATE.h"
#include "OPRT_KEY.h"

USING_NS_CC;

actionCtl::actionCtl()
{
	jumpFlag = false;
	sy = 12.0f;
}


actionCtl::~actionCtl()
{
}

void actionCtl::MoveLR(int speed, Node * sp)
{
	sp->setPositionX(sp->getPositionX() + speed);
}

void actionCtl::Jump(float speed, Node * sp)
{
	sp->setPositionY(sp->getPositionY() + sy);

}

void actionCtl::Fall(int speed, Node * sp)
{
}
