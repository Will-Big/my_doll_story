#pragma once

class Object;

class Collider
{
	friend class Object;

private:
	static UINT g_iNextID;

	Object* m_pOwner;       // �ݶ��̴��� ������ �ִ� ������Ʈ�� �ּ�

	Vec2	m_vOffsetPos;	// ���� ��ġ�������� ������� �Ÿ���
	Vec2	m_vFinalPos;	// �浹ü�� ���� ��
	Vec2	m_vScale;       //�浹ü ũ��

	UINT m_iID;			    //�浹ü�� ���̵�

	
public:

	void setScale(Vec2 _vScale) { m_vScale = _vScale; }
	void setOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }

public:
	void finalupdate(); //�浹ü ���� ��ġ�� ���
	void render(HDC _dc);    //�浹ü ĭ�� �׸��� ����? //������Ʈ���� render

public:
	Collider& operator=(Collider& _origin) = delete;

public:
	Collider();
	Collider(const Collider* _origin);
	~Collider();
	
};
