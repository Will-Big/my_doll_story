#include "pch.h"
#include "Object.h"

#include "Collider.h"
#include "Animator.h"

Object::Object()
	: m_strName()
	, m_vPos{}
	, m_vScale{}
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
{

}
Object::Object(const Object& _origin)
	: m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_bAlive(true)
{
	if (_origin.m_pCollider)
	{
		m_pCollider = new Collider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;

	}

	if (_origin.m_pAnimator)
	{
		m_pAnimator = new Animator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}

	/*CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 0.f), Vec2(500.f, 500.f), Vec2(500.f, 0.f), 0.1f, 8);
	GetAnimator()->Play(L"WALK_RIGHT", true);*/
}


Object::~Object()
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}

	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
}


void Object::finalupdate()
{
	if (m_pCollider)
	{
		m_pCollider->finalupdate();
	}


}

void Object::component_render(HDC _dc)
{
	if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
	}

	if (m_pAnimator != nullptr)
	{
		m_pAnimator->render(_dc);
	}
}


void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::init()
{
}
