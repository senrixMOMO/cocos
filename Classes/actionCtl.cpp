#include "actionCtl.h"
#include "OPRT_STATE.h"
#include "OPRT_KEY.h"

USING_NS_CC;

actionCtl::actionCtl()
{
	sy = 12.0f;
}


actionCtl::~actionCtl()
{
}

void actionCtl::MoveLR(int speed, Node * sp)
{
	sp->setPositionX(sp->getPositionX() + speed);
}

void actionCtl::Jump(Node * sp)
{
	sp->setPositionY(sp->getPositionY() + sy);

}

void actionCtl::Fall(int speed, Node * sp)
{
}
