#pragma once

class Object;
class Animation;
class Texture;

class Animator
{
private:
	map<wstring, Animation*>	m_mapAnim;	// 모든 Animation
	Animation*					m_pCurAnim;	// 현재 재생중인 Animation
	Object*						m_pOwner;	// Animator 소유 오브젝트
	bool						m_bRepeat;	// 애니메이션 루프 여부

public:
	Object* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	// Vec2 _vLT: 애니메이션의 첫 번째 프레임의 좌상단 좌표
	// Vec2 _vSliceSize: 좌상단 좌표로부터 가로세로를 얼마나 잘라서 쓸 것인지
	// Vec2 _vStep: 접근할 간격 (ex. Vec2(60.f, 0.f) 입력시 왼쪽부터 오른쪽으로 접근)
	// float fDuration
	// UINT _iFrameCount: 프레임 개수
	Animation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);
	void SetOffset(const wstring& _strName, Vec2 _vOffset); // 애니메이션 이름과 이동시킬 벡터를 넣어주면 해당 애니메이션을 전부 _vOffSet만큼 변경

public:
	void update();
	void render(HDC _dc);

public:
	Animator();
	~Animator();

	friend class Object;
};