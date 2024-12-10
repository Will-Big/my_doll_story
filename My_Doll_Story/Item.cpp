#include "pch.h"
#include "Item.h"

#include "Animator.h"

#include "ResManager.h"

#include "Doll.h"

void Item::Use()
{

}

void Item::update()
{
}

void Item::finalupdate()
{
}

void Item::render(HDC _dc)
{
	//Ellipse(_dc
	//	, int(m_vPos.x - m_vScale.x / 2.f)
	//	, int(m_vPos.y - m_vScale.y / 2.f)
	//	, int(m_vPos.x + m_vScale.x / 2.f)
	//	, int(m_vPos.y + m_vScale.y / 2.f));

	//component_render(_dc);
}


Item::Item(Item* _pItem)
	: m_bMoving(_pItem->m_bMoving)
	, m_bIsDoll(_pItem->m_bIsDoll)
	, m_bIsOn(_pItem->m_bIsOn)
	, m_eItemType(_pItem->m_eItemType)
{
	SetScale(Vec2(110.f, 110.f));


	m_pTexture = ResManager::GetInst()->LoadTexture(L"PlayerImage", L"texture\\link_resize24.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_UP", m_pTexture, Vec2(0.f, 220.f), Vec2(110.f, 110.f), Vec2(110.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"IDLE_UP", true);

}

Item::Item(ITEM_TYPE _eType)
	: m_bMoving(false)
	, m_bIsDoll(false)
	//, m_bIsCotton(false)
	, m_bIsOn(true)
	, m_eItemType(_eType)
{
	SetScale(Vec2(110.f, 110.f));

}

Item::Item()
	: m_bMoving(false)
	, m_bIsDoll(false)
	//, m_bIsCotton(false)
	, m_bIsOn(true)
	, m_eItemType(ITEM_TYPE::DEFAULT)
{
	//SetScale(Vec2(150.f, 150.f));

	// =================================================
	// 스프라이트 출력 예시 코드고 실제로 똑같이 쓰면 안됩니다 !
	// 각 아이템 클래스 생성자에서 이런식으로 하라는 뜻이에요
	// 자기 클래스 구현할때는 이부분 삭제하시구 스프라이트 넣는거에요
	m_pTexture = ResManager::GetInst()->LoadTexture(L"PlayerImage", L"texture\\link_resize24.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_UP", m_pTexture, Vec2(0.f, 220.f), Vec2(110.f, 110.f), Vec2(110.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"IDLE_UP", true);

	// =================================================

}

Item::~Item()
{
}
