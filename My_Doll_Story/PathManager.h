#pragma once

#include "Singleton.h"

class PathManager : public Singleton<PathManager> {
	friend class Singleton<PathManager>;

private:
	wchar_t	m_szContentPath[255]; //윈도우 경로 최대글자수 제한이 255

public:
	void init();
	wchar_t* GetContentPath() { return m_szContentPath; }

private:
	PathManager();
	~PathManager();
};