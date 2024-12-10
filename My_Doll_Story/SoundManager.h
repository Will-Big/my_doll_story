#pragma once

#include "Singleton.h"

#include <fmod.hpp>

// B - BACKGROUND MUSIC
// E - EFFECT

enum class SOUND
{
	BGM,
	E_WALK,
	E_PUSH,
	E_BUTTON,
	E_ITEM,
	E_RESET,
	E_CLEAR,
	END,
};

enum class CHANNEL
{
	BACKGROUND,
	EFFECT,
	WALK,
	END,
};

class SoundManager : public Singleton<SoundManager> {
	friend class Singleton<SoundManager>;

private:
	FMOD::System*		m_pSystem;
	FMOD::Sound*		m_arrSound[(UINT)SOUND::END];
	FMOD::Channel*		m_arrChannel[(UINT)CHANNEL::END];
	FMOD::Sound*		m_pCurSound;
	FMOD_RESULT			m_eResult;
	UINT				m_iVersion;


public:
	void init();
	void update();

public:
	void SetVolume(CHANNEL _eChannel, float _fVolume);
	void PlaySound(SOUND _eSound, CHANNEL _eChannel);
	void PauseReplaySound(CHANNEL _eChannel);
	void PlayWalkSound();

private:
	SoundManager();
	~SoundManager();
};

