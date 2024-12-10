#include "pch.h"
#include "func.h"

#include "EventManager.h"
#include "MenuPanel.h"
#include "ClearPanel.h"

void CreateObject(Object* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	EventManager::GetInst()->AddEvent(evn);
}

void DeleteObject(Object* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	EventManager::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	EventManager::GetInst()->AddEvent(evn);
}


void MakeMenuPanel(MenuPanel* _menuPanel)
{
	_menuPanel->SetName(L"MenuPanel");
	_menuPanel->SetScale(Vec2(1000.f, 700.f));
	_menuPanel->SetPos(Vec2(800.f, 450.f));
}

void MakeClearPanel(ClearPanel* _clearPanel)
{
	_clearPanel->SetName(L"ClearPanel");
	_clearPanel->SetScale(Vec2(1000.f, 700.f));
	_clearPanel->SetPos(Vec2(800.f, 450.f));
}

void Menu(DWORD_PTR _panel, DWORD_PTR)
{
	((MenuPanel*)_panel)->SetOn(true);
}

void ToMenu(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::MENU);
}

void ToSelect(DWORD_PTR _panel, DWORD_PTR)
{
	((ClearPanel*)_panel)->SetOn(false);
	ChangeScene(SCENE_TYPE::SELECT_STAGE);
}


void ToSelect2(DWORD_PTR _panel, DWORD_PTR)
{
	((ClearPanel*)_panel)->SetOn(false);
	ChangeScene(SCENE_TYPE::SELECT_STAGE2);
}

Vec2 IndexToVec(MapIndex _sMapIndex)
{
	Vec2 vStartPos = { 560.f, 120.f };

	if (_sMapIndex.x != 0)
	{
		vStartPos.x = vStartPos.x + (110.f * _sMapIndex.x);
	}
	if (_sMapIndex.y != 0)
	{
		vStartPos.y = vStartPos.y + (110.f * _sMapIndex.y);
	}

	return vStartPos;
}

MapIndex VecToIndex(Vec2 _vPos)
{
	Vec2 vStartPos = { 560.f, 120.f };
	MapIndex _mapIndex = { 0,0 };

	_vPos.x -= vStartPos.x;
	_vPos.y -= vStartPos.y;

	_mapIndex.x = (int)_vPos.x / 110;
	_mapIndex.y = (int)_vPos.y / 110;

	return _mapIndex;

}

