#pragma once

#include "Singleton.h"

class PathManager : public Singleton<PathManager> {
	friend class Singleton<PathManager>;

private:
	wchar_t	m_szContentPath[255]; //������ ��� �ִ���ڼ� ������ 255

public:
	void init();
	wchar_t* GetContentPath() { return m_szContentPath; }

private:
	PathManager();
	~PathManager();
};