#include "pch.h"
#include "Stage.h"

#include "Map.h"
#include "Block.h"

#include "Player.h"
#include "Doll.h"
#include "Scissors.h"
#include "Cotton.h"
#include "Tape.h"

#include "ClearPanel.h"
#include "MenuPanel.h"

#include "Texture.h"
#include "ResManager.h"

#include "GameManager.h"
#include "Main.h"

#include "SceneManager.h"
#include "InputManager.h"

#include "SoundManager.h"

Stage::Stage()
	: m_pPlayer(nullptr)
	, m_pMap(nullptr)
{
}

Stage::~Stage()
{

}

void Stage::update()
{
}

void Stage::finalupdate()
{
}

void Stage::render(HDC _dc)
{
}

void Stage::Enter()
{
}

void Stage::Exit()
{
}


void Stage::MakeItem(ITEM_TYPE _eType, int _x, int _y)
{
	Item* pItem = nullptr;

	switch (_eType)
	{
	case ITEM_TYPE::DOLL:		// 예시입니다.
		pItem = new Doll(m_SceneType);
		break;
	case ITEM_TYPE::SCISSORS:
		pItem = new Scissors(_x, _y);
		break;
	case ITEM_TYPE::COTTON:
		pItem = new Cotton(_x, _y);
		break;
	case ITEM_TYPE::TAPE:
		pItem = new Tape();
		break;
	case ITEM_TYPE::BUTTON:
		break;
	default:
		pItem = new Item();
		break;
	}

	m_pMap->SetItem(pItem, _x, _y);
}

void Stage::SetClear(bool _b)
{
	m_pClearPanel->SetOn(_b);
}

void Stage::StageKeyInput()
{
	if (InputManager::GetInst()->GetKeyState(KEY::Z) == KEY_STATE::TAP)
	{
		bool bPanelOn = m_pClearPanel->GetOn();
		m_pClearPanel->SetOn(!bPanelOn);
	}
	if (InputManager::GetInst()->GetKeyState(KEY::ESC) == KEY_STATE::TAP)
	{
		SoundManager::GetInst()->PlaySound(SOUND::E_BUTTON, CHANNEL::EFFECT);

		if (m_pMenuPanel->GetOn())
			m_pMenuPanel->SetOn(false);
		else if (m_pClearPanel->GetOn())
			m_pClearPanel->SetOn(false);
		else if(!m_pMenuPanel->GetOn())
			m_pMenuPanel->SetOn(true);
	}
#ifdef DEV_MODE
	if (InputManager::GetInst()->GetKeyState(KEY::F3) == KEY_STATE::TAP)
	{
		SetClear(true);
		m_pClearPanel->SetOn(true);
	}
#endif DEV_MODE
}
