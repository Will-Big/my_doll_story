#pragma once

class Object;
class Animation;
class Texture;

class Animator
{
private:
	map<wstring, Animation*>	m_mapAnim;	// ��� Animation
	Animation*					m_pCurAnim;	// ���� ������� Animation
	Object*						m_pOwner;	// Animator ���� ������Ʈ
	bool						m_bRepeat;	// �ִϸ��̼� ���� ����

public:
	Object* GetObj() { return m_pOwner; }

public:
	void CreateAnimation(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount);
	// Vec2 _vLT: �ִϸ��̼��� ù ��° �������� �»�� ��ǥ
	// Vec2 _vSliceSize: �»�� ��ǥ�κ��� ���μ��θ� �󸶳� �߶� �� ������
	// Vec2 _vStep: ������ ���� (ex. Vec2(60.f, 0.f) �Է½� ���ʺ��� ���������� ����)
	// float fDuration
	// UINT _iFrameCount: ������ ����
	Animation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _bRepeat);
	void SetOffset(const wstring& _strName, Vec2 _vOffset); // �ִϸ��̼� �̸��� �̵���ų ���͸� �־��ָ� �ش� �ִϸ��̼��� ���� _vOffSet��ŭ ����

public:
	void update();
	void render(HDC _dc);

public:
	Animator();
	~Animator();

	friend class Object;
};