#include "pch.h"
#include "Main.h"
#include "PathManager.h"

PathManager::PathManager()
	:m_szContentPath{}
{
}

PathManager::~PathManager()
{
}

void PathManager::init()
{
	GetCurrentDirectory(255, m_szContentPath);

	int iLen = wcslen(m_szContentPath);

	//경로 한 칸 밖으로 나오기
	for (int i = iLen - 1; 0 <= i; --i) {
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	wcscat_s(m_szContentPath, 255, L"\\resource\\");

	//SetWindowText(Main::GetInst()->GetMainHwnd(), m_szContentPath);
}
