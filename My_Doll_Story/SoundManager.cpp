#include "pch.h"
#include "SoundManager.h"


SoundManager::SoundManager()
	: m_pSystem(nullptr)
	, m_arrSound{}
	, m_arrChannel{}
	, m_pCurSound(nullptr)
	, m_eResult()
	, m_iVersion(0)
{
}

SoundManager::~SoundManager()
{
	for (UINT i = 0; i < (UINT)SOUND::END; i++)
	{
		m_arrSound[i]->release();
	}

	m_pSystem->release();
}

void SoundManager::init()
{
	m_eResult = FMOD::System_Create(&m_pSystem);
	assert(m_eResult == FMOD_OK);

	m_eResult = m_pSystem->getVersion(&m_iVersion);
	assert(m_eResult == FMOD_OK);

	m_eResult = m_pSystem->init((UINT)CHANNEL::END, FMOD_INIT_NORMAL, nullptr);
	assert(m_eResult == FMOD_OK);

	// Create Sound
	// BGM
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\BGM1.wav", FMOD_LOOP_NORMAL, 0, &m_arrSound[(UINT)SOUND::BGM]);
	assert(m_eResult == FMOD_OK);

	// Sound Effects
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\E_WALK.wav", FMOD_LOOP_OFF, 0, &m_arrSound[(UINT)SOUND::E_WALK]);
	assert(m_eResult == FMOD_OK);
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\E_PUSH.wav", FMOD_LOOP_OFF, 0, &m_arrSound[(UINT)SOUND::E_PUSH]);
	assert(m_eResult == FMOD_OK);
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\E_BUTTON.wav", FMOD_LOOP_OFF, 0, &m_arrSound[(UINT)SOUND::E_BUTTON]);
	assert(m_eResult == FMOD_OK);
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\E_ITEM.wav", FMOD_LOOP_OFF, 0, &m_arrSound[(UINT)SOUND::E_ITEM]);
	assert(m_eResult == FMOD_OK);
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\E_RESET.wav", FMOD_LOOP_OFF, 0, &m_arrSound[(UINT)SOUND::E_RESET]);
	assert(m_eResult == FMOD_OK);
	m_eResult = m_pSystem->createSound("..\\resource\\sound\\E_CLEAR.wav", FMOD_LOOP_OFF, 0, &m_arrSound[(UINT)SOUND::E_CLEAR]);
	assert(m_eResult == FMOD_OK);

}

void SoundManager::update()
{
	m_eResult = m_pSystem->update();
	assert(m_eResult == FMOD_OK);
}

void SoundManager::SetVolume(CHANNEL _eChannel, float _fVolume)
{
	m_arrChannel[(UINT)_eChannel]->setVolume(_fVolume);
}

void SoundManager::PlaySound(SOUND _eSound, CHANNEL _eChannel)
{
	m_arrChannel[(UINT)_eChannel]->stop();
	FMOD::Sound* sound = m_arrSound[(UINT)_eSound];
	m_pSystem->playSound(sound, 0, false, &m_arrChannel[(UINT)_eChannel]);
	m_arrChannel[(UINT)CHANNEL::EFFECT]->setVolume(0.6f);
}

void SoundManager::PlayWalkSound()
{
	m_arrChannel[(UINT)CHANNEL::WALK]->stop();
	
	FMOD::Sound* sound = m_arrSound[(UINT)SOUND::E_WALK];
	m_pSystem->playSound(sound, 0, false, &m_arrChannel[(UINT)CHANNEL::WALK]);
	m_arrChannel[(UINT)CHANNEL::WALK]->setVolume(0.25f);
}

void SoundManager::PauseReplaySound(CHANNEL _eChannel)
{
	bool isPlaying;

	m_arrChannel[(UINT)_eChannel]->getPaused(&isPlaying);
	m_arrChannel[(UINT)_eChannel]->setPaused(!isPlaying);
}


