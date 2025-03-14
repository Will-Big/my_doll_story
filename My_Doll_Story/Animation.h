#pragma once

class Animator;
class Texture;

struct tAnimFrm
{
	Vec2 vLT;
	Vec2 vSlice;
	Vec2 vOffset;
	float fDuration;
};

class Animation
{
private:
	wstring				m_strName;
	Animator*			m_pAnimator;
	Texture*			m_pTex;			// Animation 이 사용하는 텍스처
	vector<tAnimFrm>	m_vecFrm;		// 각 애니메이션 프레임 정보
	int					m_iCurFrm;		// 현재 프레임
	float				m_fAccTime;		// 시간 누적
	bool				m_bFinish;		// 재생 끝에 도달 여부

private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}

	tAnimFrm& GetFrame(int _idx) { return m_vecFrm[_idx]; } // 받아 간 쪽에서 수정할 수 있도록 레퍼런스로
	int GetMaxFrame() { return (int)m_vecFrm.size(); }

public:
	void update();
	void render(HDC _dc);
	void Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);

public:
	Animation();
	~Animation();

	friend class Animator;
};

