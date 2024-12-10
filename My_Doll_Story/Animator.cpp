#include "pch.h"
#include "Animator.h"
#include "Animation.h"

Animator::Animator()
	: m_pOwner(nullptr)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

Animator::~Animator()
{
	// 이 형식 나중에 Safe_Delete_Map으로 묶어 주기
	typename map<wstring, Animation*>::iterator iter = m_mapAnim.begin();

	for (; iter != m_mapAnim.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	m_mapAnim.clear();
}


void Animator::CreateAnimation(const wstring& _strName, Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	Animation* pAnim = FindAnimation(_strName);
	assert(pAnim == nullptr);

	pAnim = new Animation;

	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;
	pAnim->Create(_pTex, _vLT, _vSliceSize, _vStep, _fDuration, _iFrameCount);

	m_mapAnim.insert(make_pair(_strName, pAnim));

}

Animation* Animator::FindAnimation(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void Animator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_bRepeat = _bRepeat;
}

void Animator::SetOffset(const wstring& _strName, Vec2 _vOffset)
{
	map<wstring, Animation*>::iterator iter = m_mapAnim.find(_strName);

	if (iter == m_mapAnim.end())
		return;

	for (int i = 0; i < iter->second->GetMaxFrame(); i++)
	{
		iter->second->GetFrame(i).vOffset = _vOffset;
	}
}

void Animator::update()
{
	if (m_pCurAnim != nullptr)
	{
		m_pCurAnim->update();

		if (m_bRepeat && m_pCurAnim->IsFinish()) //루프 옵션 체크 + 한 번의 루프가 끝남
		{
			m_pCurAnim->SetFrame(0);
		}
	}
}

void Animator::render(HDC _dc)
{
	if (m_pCurAnim != nullptr)
		m_pCurAnim->render(_dc);
}