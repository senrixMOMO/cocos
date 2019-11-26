#include "actionCtl.h"
#include "OPRT_STATE.h"
#include "OPRT_KEY.h"

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

void actionCtl::Fall(Node * sp)
{
	sp->setPositionY(sp->getPositionY() - 5);
}
