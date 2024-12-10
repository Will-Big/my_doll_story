#pragma once

#include "Singleton.h"

class Texture;

class ResManager : public Singleton<ResManager> {
	friend class Singleton<ResManager>;

private:
	map<wstring, Texture*> m_mapTex;

public:
	Texture* LoadTexture(const wstring& _strKey, const wstring& _strRelativePath);

public:
	Texture* FindTexture(const wstring& _strKey);

public:
	ResManager();
	~ResManager();

};

