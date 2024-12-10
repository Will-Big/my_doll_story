#pragma once
#include "Singleton.h"

class Collider;

class CollisonManager : public Singleton<CollisonManager>
{
	friend class Singleton<CollisonManager>;

private:
	UINT m_arrCheck[(UINT)GROUP_TYPE::END];



public:
	void init();
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // 그룹들끼리 충돌검사
	void Reset()
	{
		memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);
	}

private:
	void CollisionUpdateGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight); // 그룹간의 충돌 갱신
	bool IsCollision(Collider* pLeftCol, Collider* pRightCol);

private:
	CollisonManager();
	~CollisonManager();
};

