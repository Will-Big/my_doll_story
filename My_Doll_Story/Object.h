#pragma once



class Collider;
class Animator;

class Object
{
public:
	wstring m_strName;

	Vec2 m_vPos;
	Vec2 m_vScale;

	Collider* m_pCollider;
	Animator* m_pAnimator;

	bool		m_bAlive;

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetName(const wstring& _strName) { m_strName = _strName; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }
	const wstring& GetName() { return m_strName; }

	Collider* GetCollider() { return m_pCollider; }
	Animator* GetAnimator() { return m_pAnimator; }

	void CreateCollider();
	void CreateAnimator();

	bool IsDead() { return !m_bAlive; }
	void SetDead() { m_bAlive = false; }

public:
	virtual void init();
	virtual void update() = 0;
	virtual void render(HDC _dc) = 0;
	virtual void finalupdate();

	void component_render(HDC _dc);


public:
	Object();
	Object(const Object& _origin);
	virtual ~Object();
};

