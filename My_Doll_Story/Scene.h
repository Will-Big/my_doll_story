#pragma once

// 전방 선언
class Object;

class Scene
{
private:
	vector<Object*>	 m_arrObj[(UINT)GROUP_TYPE::END];	// 오브젝트를 저장 및 관리할 벡터를 그룹 개수만큼 선언
	wstring			 m_strName;							// Scene 이름

public: 
	void SetName(const wstring& _strName) { m_strName = _strName; }   // Scene 이름 설정
	const wstring& GetName()			  { return m_strName; }       // Scene 이름 반환

	virtual void update();			// 현재 씬 오브젝트의 업데이트 함수 실행
	virtual void finalupdate();     // 모든 업데이트를 확정시키는 함수 
	virtual void render(HDC _dc);	// 현재 씬 오브젝트의 렌더 함수 실행

	virtual void Enter() = 0;		// 씬 진입시 호출(오브젝트 배치)
	virtual void Exit() = 0;		// 씬 퇴장시 호출(오브젝트 삭제)
	
public:
	void AddObject(Object* _pObj, GROUP_TYPE _eType)  // 타입에 해당하는 벡터에 오브젝트 추가
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

