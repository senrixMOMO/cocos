#include "actionCtl.h"


USING_NS_CC;

actionCtl::actionCtl()
{
}


actionCtl::~actionCtl()
{
}

void actionCtl::MoveLR(int speed, Node * sp)
{
	sp->setPositionX(sp->getPositionX() + speed);
}
