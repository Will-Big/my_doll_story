#pragma once

class Object;
class MenuPanel;
class ClearPanel;

void CreateObject(Object* _pObj, GROUP_TYPE _eGroup);
void DeleteObject(Object* _pObj);
void ChangeScene(SCENE_TYPE _eNext);

Vec2 IndexToVec(MapIndex _sMapIndex);
MapIndex VecToIndex(Vec2 _vPos);
void MakeMenuPanel(MenuPanel* _menuPanel);
void MakeClearPanel(ClearPanel* _clearPanel);
void Menu(DWORD_PTR _panel, DWORD_PTR);
void ToMenu(DWORD_PTR, DWORD_PTR);
void ToSelect(DWORD_PTR _panel, DWORD_PTR);
void ToSelect2(DWORD_PTR _panel, DWORD_PTR);


template<typename T>

void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		if (nullptr != _vec[i])
			delete _vec[i];
	}

	_vec.clear();
}
