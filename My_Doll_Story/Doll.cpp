#include "pch.h"
#include "Doll.h"

#include "Texture.h"
#include <algorithm>

#include "ResManager.h"

#include "SceneManager.h"
#include "SoundManager.h"

// static 멤버 변수 초기화
int Doll::m_iStartID = 0;

Doll::Doll(SCENE_TYPE _eType)
	: m_iUniqID(m_iStartID)
	, m_pTex(nullptr)
	, m_iXSize(0)
	, m_iYSize(0)
	, m_iMaxPart(0)
{
	static const wstring link = L"texture\\스테이지\\인형파츠\\";

	switch (_eType)
	{
	case SCENE_TYPE::STAGE_01:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_01_DOLL", link + L"꺼먼오리.bmp"), 3);
		m_SceneType = SCENE_TYPE::STAGE_01;
		break;
	case SCENE_TYPE::STAGE_02:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_02_DOLL", link + L"코끼리.bmp"), 3);
		m_SceneType = SCENE_TYPE::STAGE_02;
		break;
	case SCENE_TYPE::STAGE_03:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_03_DOLL", link + L"상어.bmp"), 2);
		m_SceneType = SCENE_TYPE::STAGE_03;
		break;
	case SCENE_TYPE::STAGE_04: 
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_04_DOLL", link + L"오리.bmp"), 3);
		m_SceneType = SCENE_TYPE::STAGE_04;
		break;
	case SCENE_TYPE::STAGE_05:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_05_DOLL", link + L"퍼런코끼리.bmp"), 3);
		m_SceneType = SCENE_TYPE::STAGE_05;
		break;
	case SCENE_TYPE::STAGE_06:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_06_DOLL", link + L"곰.bmp"), 4);
		m_SceneType = SCENE_TYPE::STAGE_06;
		break;
	case SCENE_TYPE::STAGE_07:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_07_DOLL", link + L"병아리.bmp"), 2);
		m_SceneType = SCENE_TYPE::STAGE_07;
		break;
	case SCENE_TYPE::STAGE_08:
		SetTexture(ResManager::GetInst()->LoadTexture(L"STAGE_08_DOLL", link + L"토끼.bmp"), 4);
		m_SceneType = SCENE_TYPE::STAGE_08;
		break;
	default:
		assert(false);
		break;
	}



	SetScale(Vec2(110.f, 110.f));
	SetItemType(ITEM_TYPE::DOLL);
	m_iStartID++;
	m_vMerged.push_back(m_iUniqID);
}

Doll::Doll(const Doll& _doll)
{
}

Doll::~Doll()
{
	m_iStartID = 0;
}

void Doll::update()
{
}

void Doll::render(HDC _dc)
{
	if (!ItemOn())
		return;

	int xIndex = 0;
	int yIndex = 0;
	
	if (m_vMerged.size() == 1) // 단일 파트라면
	{
		xIndex = m_vMerged[0];
		yIndex += 1;

		TransparentBlt(_dc,
			m_vPos.x - m_vScale.x / 2.f,
			m_vPos.y - m_vScale.y / 2.f,
			m_vScale.x,
			m_vScale.y,
			m_pTex->GetDC(),
			m_iXSize * xIndex,
			m_iYSize * yIndex,
			m_iXSize,
			m_iYSize,
			RGB(255, 255, 255)
		);

	}
	else if (m_vMerged.size() == m_iMaxPart) // 완성본이라면
	{
		yIndex += 2;

		TransparentBlt(_dc,
			m_vPos.x - m_vScale.x / 2.f,
			m_vPos.y - m_vScale.y / 2.f,
			m_vScale.x,
			m_vScale.y,
			m_pTex->GetDC(),
			m_iXSize * xIndex,
			m_iYSize * yIndex,
			m_iXSize,
			m_iYSize,
			RGB(255, 255, 255)
			);
	}
	else if(m_vMerged.size() <= m_iMaxPart) // 둘 이상 합쳐져있다면
	{
		yIndex += 0;

		for (auto& i : m_vMerged)
		{
			TransparentBlt(_dc,
				m_vPos.x - m_vScale.x / 2.f,
				m_vPos.y - m_vScale.y / 2.f,
				m_vScale.x,
				m_vScale.y,
				m_pTex->GetDC(),
				m_iXSize * i,
				m_iYSize * yIndex,
				m_iXSize,
				m_iYSize,
				RGB(255, 255, 255)
			);
		}
	}
}

void Doll::SetTexture(Texture* _pTex, int _iPartNum)
{
	m_pTex = _pTex;
	
	m_iMaxPart = _iPartNum;
	m_iXSize = _pTex->Width() / 5;
	m_iYSize = _pTex->Height() / 3;
}

void Doll::MergeParts(vector<int>& _vecPart)
{
	if(!_vecPart.empty())
	{
		SoundManager::GetInst()->PlaySound(SOUND::E_ITEM, CHANNEL::EFFECT);
		for (int i : _vecPart)
		{
			m_vMerged.push_back(i);
		}

		_vecPart.clear();

		sort(m_vMerged.begin(), m_vMerged.end(), std::greater<int>());

		if (CheckComplete())
		{			
			SoundManager::GetInst()->PlaySound(SOUND::E_CLEAR, CHANNEL::EFFECT);
			SceneManager::GetInst()->SetClear(m_SceneType, true);
		}
	}
}

