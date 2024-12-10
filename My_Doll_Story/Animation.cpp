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
	if (m_bFinish)		//finish ���¶�� ������Ʈ�� �� �� ��
		return;

	// �ð� ����
	m_fAccTime += fDT;

	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		m_iCurFrm++;

		// ������ ������ŭ ������ �� �� ��� 1�� ���������� �����ֱ�
		if (m_iCurFrm >= m_vecFrm.size())
		{
			m_iCurFrm = -1;			//0�� �ƴ� -1�� ������ ���� '������'�� �ǹ� ����
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}

		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration; //0�� �ƴԿ� ���� //���� �ɷ��� ������ ���ڴ�
	}
}

void Animation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	Object* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos = vPos + m_vecFrm[m_iCurFrm].vOffset; // Object Position �� Offset ��ŭ �߰� �̵� ��ġ

	TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
		, (int)(vPos.x - pObj->GetScale().x / 2.f)
		, (int)(vPos.y - pObj->GetScale().y / 2.f)
		, (int)(pObj->GetScale().x)				//���α���
		, (int)(pObj->GetScale().y)				//���α���
		, m_pTex->GetDC()
		, (int)(m_vecFrm[m_iCurFrm].vLT.x)		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
		, (int)(m_vecFrm[m_iCurFrm].vLT.y)		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
		, (int)(m_vecFrm[m_iCurFrm].vSlice.x)	//�ڸ� ������
		, (int)(m_vecFrm[m_iCurFrm].vSlice.y)	//�ڸ� ������
		, RGB(255, 255, 255));					//����ȭ�� ����
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