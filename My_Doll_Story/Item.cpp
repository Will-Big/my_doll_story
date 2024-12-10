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
	// ��������Ʈ ��� ���� �ڵ�� ������ �Ȱ��� ���� �ȵ˴ϴ� !
	// �� ������ Ŭ���� �����ڿ��� �̷������� �϶�� ���̿���
	// �ڱ� Ŭ���� �����Ҷ��� �̺κ� �����Ͻñ� ��������Ʈ �ִ°ſ���
	m_pTexture = ResManager::GetInst()->LoadTexture(L"PlayerImage", L"texture\\link_resize24.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"IDLE_UP", m_pTexture, Vec2(0.f, 220.f), Vec2(110.f, 110.f), Vec2(110.f, 0.f), 0.5f, 1);
	GetAnimator()->Play(L"IDLE_UP", true);

	// =================================================

}

Item::~Item()
{
}
