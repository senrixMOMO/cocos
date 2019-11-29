#pragma once
#include "cocos2d.h"
#include "Cricket/ck/ck.h"
#include "Cricket/ck/config.h"
#include "Cricket/ck/bank.h"
#include "Cricket/ck/sound.h"

class SoundManager
{
public:

	static SoundManager* getInstance();

	/**
	 * @deprecated Use getInstance() instead.
	 * @js NA
	 */
	CC_DEPRECATED_ATTRIBUTE static SoundManager* sharedSoundManager() { return SoundManager::getInstance(); }

	SoundManager();
	~SoundManager();
	void init();
	void SetSE(const char* file, const char* ckbx);
	void PlaySE();
	void SetBGM(const char* file);
	void Destroy();
	void update();
private:
	CkSound* _music;
	CkBank* _bank;
	CkSound* _soundEffect;
};

