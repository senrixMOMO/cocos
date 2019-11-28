#include "EffectControl.h"


static EffectControl *s_SharedEffectControl = nullptr;
EffectControl * EffectControl::getInstance()
{
	if (!s_SharedEffectControl)
	{
		s_SharedEffectControl = new (std::nothrow) EffectControl;
		CCASSERT(s_SharedEffectControl, "FATAL: Not enough memory");
		s_SharedEffectControl->init();
	}
	return s_SharedEffectControl;
}

EffectControl::EffectControl()
{
	manager = nullptr;
	_count = 0;
}


EffectControl::~EffectControl()
{
	manager->release();
}

void EffectControl::init()
{
	auto rsize = Director::getInstance()->getOpenGLView()->getDesignResolutionSize();

	manager = efk::EffectManager::create(rsize);
}

void EffectControl::PlayEffect(std::string str, float frame, Vec2 pos, Sprite * sp)
{
	auto effect = efk::Effect::create(str, frame);
	if (effect != nullptr)
	{
		auto emitter = efk::EffectEmitter::create(manager);
		emitter->setEffect(effect);
		if (_count == 0)
		{
			emitter->setPlayOnEnter(true);
		}

		emitter->setRotation3D(cocos2d::Vec3(90, 0, 0));
		emitter->setPosition(pos);

		// emitter->setScale(13);
		sp->addChild(emitter, 0);
		_count++;
	}
}

void EffectControl::CountClear()
{
	_count = 0;
}
