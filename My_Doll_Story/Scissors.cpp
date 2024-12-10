#include "pch.h"
#include "Scissors.h"

#include "ResManager.h"
#include "Animator.h"
#include "Texture.h"

#include "TimeManager.h"
#include "SoundManager.h"


Scissors::Scissors()
	: m_bIsUse(false)
{
}

Scissors::Scissors(int _x, int _y)
{
	SetItemType(ITEM_TYPE::SCISSORS);
	m_sCurIndex = { _y,_x };

	SetScale(Vec2(110.f, 110.f));
	SetPos(IndexToVec(m_sCurIndex));
	m_pTexture = ResManager::GetInst()->LoadTexture(L"ScissorsImage", L"texture\\��������\\����\\����.bmp");

}


Scissors::~Scissors()
{
}

void Scissors::Use()
{
	static float fElapsedTime = 0.f;
	float _fDuration = 0.17f;


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

void Scissors::update()
{
	if (m_bIsUse)
	{
		Use();
	}
}

void Scissors::render(HDC _dc)
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
			, (int)GetScale().x		//���α���
			, (int)GetScale().y		//���α���
			, m_pTexture->GetDC()
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, 0		//�ؽ��� ������ �ڸ� ��ġ�� �»��(LT)
			, m_pTexture->Width()	//�ڸ� ������
			, m_pTexture->Height()	//�ڸ� ������
			, RGB(255, 255, 255));					//����ȭ�� ����
	}
}
