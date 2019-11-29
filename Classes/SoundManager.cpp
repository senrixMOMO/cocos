#include "SoundManager.h"



static SoundManager *s_SharedSoundManager = nullptr;
SoundManager * SoundManager::getInstance()
{
	if (!s_SharedSoundManager)
	{
		s_SharedSoundManager = new (std::nothrow) SoundManager;
		CCASSERT(s_SharedSoundManager, "FATAL: Not enough memory");
		s_SharedSoundManager->init();
	}

	return s_SharedSoundManager;
}

SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
}

void SoundManager::init()
{
	CkConfig config;
	CkInit(&config);
}

void SoundManager::SetSE(const char* file, const char* ckbx)
{
	_bank = CkBank::newBank(file, kCkPathType_FileSystem);
	_soundEffect = CkSound::newBankSound(_bank, ckbx);
}

void SoundManager::PlaySE()
{
	_soundEffect->play();
}

void SoundManager::SetBGM(const char* file)
{
	_music = CkSound::newStreamSound(file, kCkPathType_FileSystem);
	_music->setLoopCount(-1);
	_music->play();
}

void SoundManager::Destroy()
{
	_music->destroy();
	_bank->destroy();
	_soundEffect->destroy();

	CkShutdown();
}

void SoundManager::update()
{
	CkUpdate();
}
