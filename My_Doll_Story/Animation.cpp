#include "pch.h"
#include "Animation.h"
#include "Object.h"
#include "Animator.h"
#include "Texture.h"
#include "TimeManager.h"

Animation::Animation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

Animation::~Animation()
{
}

void Animation::update()
{
	if (m_bFinish)		//finish 상태라면 업데이트를 안 돌 것
		return;

	// 시간 누적
	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		m_iCurFrm++;

		// 프레임 개수만큼 끝까지 다 쓴 경우 1번 프레임으로 돌려주기
		if (m_iCurFrm >= m_vecFrm.size())
		{
			m_iCurFrm = -1;			//0이 아닌 -1로 설정한 것은 '끝났다'는 의미 전달
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration; //0이 아님에 주의 //렉이 걸려도 문제는 없겠다
	}
}

void Animation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	Object* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos = vPos + m_vecFrm[m_iCurFrm].vOffset; // Object Position 에 Offset 만큼 추가 이동 위치

	TransparentBlt(_dc							//전부 float으로 작업하기 때문에 int로의 형변환이 필요함
		, (int)(vPos.x - pObj->GetScale().x / 2.f)
		, (int)(vPos.y - pObj->GetScale().y / 2.f)
		, (int)(pObj->GetScale().x)				//가로길이
		, (int)(pObj->GetScale().y)				//세로길이
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)		//텍스쳐 내에서 자를 위치의 좌상단(LT)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)		//텍스쳐 내에서 자를 위치의 좌상단(LT)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)	//자를 사이즈
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)	//자를 사이즈
		, RGB(255, 255, 255));					//투명화할 색깔
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrm frm = {};

	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = _fDuration;
		frm.vSlice = _vSliceSize;
		frm.vLT = _vLT + _vStep * i;

		m_vecFrm.push_back(frm);
	}
}