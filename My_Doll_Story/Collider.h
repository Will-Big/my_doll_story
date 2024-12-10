#pragma once

class Object;

class Collider
{
	friend class Object;

private:
	static UINT g_iNextID;

	Object* m_pOwner;       // 콜라이더를 가지고 있는 오브젝트의 주소

	Vec2	m_vOffsetPos;	// 기준 위치에서부터 상대적인 거리값
	Vec2	m_vFinalPos;	// 충돌체의 최종 위
	Vec2	m_vScale;       //충돌체 크기

	UINT m_iID;			    //충돌체의 아이디

	
public:

	void setScale(Vec2 _vScale) { m_vScale = _vScale; }
	void setOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void finalupdate(); //충돌체 최종 위치를 계산
	void render(HDC _dc);    //충돌체 칸을 그리기 위한? //오브젝트에서 render

public:
	Collider& operator=(Collider& _origin) = delete;

public:
	Collider();
	Collider(const Collider* _origin);
	~Collider();
	
};
