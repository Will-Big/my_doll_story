#include "pch.h"
#include "Tape.h"

#include "Animator.h"

#include "ResManager.h"
#include "Texture.h"
#include "Item.h"

#include "TimeManager.h"
#include "SoundManager.h"



Tape::Tape()
	: m_bIsUse(false)
{
	SetScale(Vec2(110.f, 110.f));
	SetItemType(ITEM_TYPE::TAPE);

	m_pTex = ResManager::GetInst()->LoadTexture(L"TapeImage", L"texture\\��������\\����\\����Ʈ��.bmp");
	/*CreateAnimator();
	GetAnimator()->CreateAnimation(L"TapeImage", m_pTex, Vec2(0.f, 0.f), Vec2(168.f, 180.f), Vec2(0.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"TapeImage", true);*/
}

Tape::~Tape()
{

}

//void tape::toggleactivate()
//{
//	if (m_bactivated)
//	{
//		m_bactivated = false;
//	}
//	else
//	{
//		m_bactivated = true;
//	}
//
//}

void Tape::Use()
{
	static float fElapsedTime = 0.f;
	float _fDuration = 0.2f;


	if (!m_bIsUse)
	{
		SoundManager::GetInst()->PlaySound(SOUND::E_ITEM, CHANNEL::EFFECT);
		m_bIsUse = true;
	}

	if (fElapsedTime < _fDuration)
	{
		fElapsedTime += fDT;
	}
	else
	{
		fElapsedTime = 0.f;
		m_bIsUse = false;
		SetIsOn();
	}
}

void Tape::update()
{
	if (m_bIsUse)
	{
		Use();
	}
}

void Tape::render(HDC _dc)
{
Vec2 vPos = GetPos();

	if (!ItemOn())
	{
		return;
	}

	else
	{
		TransparentBlt(_dc							//���� float���� �۾��ϱ� ������ int���� ����ȯ�� �ʿ���
			, (int)(vPos.x - GetScale().x / 2.f)
			, (int)(vPos.y - GetScale().y / 2.f)
			, (int)GetScale().x 		//���α���
			, (int)GetScale().y		//���α���
			, m_pTex->GetDC()
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, m_pTex->Width()	//�ڸ� ������
			, m_pTex->Height()	//�ڸ� ������
			, RGB(255, 255, 255));					//����ȭ�� ����
	}
}