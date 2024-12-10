#include "pch.h"
#include "CollisonManager.h"

#include "Scene.h"
#include "SceneManager.h"
#include "Object.h"


CollisonManager::CollisonManager()
	:m_arrCheck{}
{
}

CollisonManager::~CollisonManager()
{
}


void CollisonManager::init()
{
}

void CollisonManager::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; iRow++)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; iCol++)
		{
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CollisonManager::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행, 큰 값을 열
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;

	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}

	if (m_arrCheck[iRow] & (1 << iCol))
	{
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

void CollisonManager::CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	Scene* pCurScene = SceneManager::GetInst()->GetCurScene();

	const vector<Object*>& vecLeft = pCurScene->GetgroupObject(_eLeft);
	const vector<Object*>& vecRight = pCurScene->GetgroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); i++)
	{
		if(nullptr==vecLeft[i]->GetCollider())
			continue;
		for (size_t j = 0; j < vecRight.size(); j++)
		{
			if (nullptr == vecRight[i]->GetCollider() || vecLeft[i] == vecRight[j]) //자신과의 충돌 방지
				continue;

			IsCollision(vecLeft[i]->GetCollider(), vecRight[i]->GetCollider());
		}
	}
}

bool CollisonManager::IsCollision(Collider* pLeftCol, Collider* pRightCol)
{
	return true;
}

