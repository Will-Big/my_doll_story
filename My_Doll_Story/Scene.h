#pragma once

// ���� ����
class Object;

class Scene
{
private:
	vector<Object*>	 m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring			 m_strName;							// Scene �̸�

public: 
	void SetName(const wstring& _strName) { m_strName = _strName; }   // Scene �̸� ����
	const wstring& GetName()			  { return m_strName; }       // Scene �̸� ��ȯ

	virtual void update();			// ���� �� ������Ʈ�� ������Ʈ �Լ� ����
	virtual void finalupdate();     // ��� ������Ʈ�� Ȯ����Ű�� �Լ� 
	virtual void render(HDC _dc);	// ���� �� ������Ʈ�� ���� �Լ� ����

	virtual void Enter() = 0;		// �� ���Խ� ȣ��(������Ʈ ��ġ)
	virtual void Exit() = 0;		// �� ����� ȣ��(������Ʈ ����)
	
public:
	void AddObject(Object* _pObj, GROUP_TYPE _eType)  // Ÿ�Կ� �ش��ϴ� ���Ϳ� ������Ʈ �߰�
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	const vector<Object*>& GetgroupObject(GROUP_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	vector<Object*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

public:
	Scene();
	virtual ~Scene();
};

