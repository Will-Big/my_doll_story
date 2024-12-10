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
	Texture*			m_pTex;			// Animation �� ����ϴ� �ؽ�ó
	vector<tAnimFrm>	m_vecFrm;		// �� �ִϸ��̼� ������ ����
	int					m_iCurFrm;		// ���� ������
	float				m_fAccTime;		// �ð� ����
	bool				m_bFinish;		// ��� ���� ���� ����

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

	tAnimFrm& GetFrame(int _idx) { return m_vecFrm[_idx]; } // �޾� �� �ʿ��� ������ �� �ֵ��� ���۷�����
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

