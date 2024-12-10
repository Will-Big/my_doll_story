#include "pch.h"
#include "ResManager.h"

#include "PathManager.h"
#include "Texture.h"

ResManager::ResManager()
{

}

ResManager::~ResManager()
{
	map<wstring, Texture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
}

Texture* ResManager::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 텍스쳐가 이미 로드되어 있는지 확인
	Texture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	wstring strFilePath = PathManager::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pTex = new Texture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

Texture* ResManager::FindTexture(const wstring& _strKey)
{
	map<wstring, Texture*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}
