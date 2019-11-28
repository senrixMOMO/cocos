#pragma once
#include "cocos2d.h"
#include "Effekseer/Effekseer.h"

USING_NS_CC;

class EffectControl
{
public:
	static EffectControl* getInstance();

	/**
	 * @deprecated Use getInstance() instead.
	 * @js NA
	 */
	CC_DEPRECATED_ATTRIBUTE static EffectControl* sharedEffectControl() { return EffectControl::getInstance(); }

	EffectControl();
	~EffectControl();

	void init();
	void PlayEffect(std::string str, float frame, Vec2 pos, Sprite* sp);
	void CountClear();

private:
	efk::EffectManager* manager;
	int _count;

};