#include "pch.h"
#include "Collider.h"

#include "Object.h"
#include "Main.h"
#include "SelectGDI.h"

UINT Collider::g_iNextID = 0;

Collider::Collider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

Collider::Collider(const Collider* _origin)
	:m_pOwner(nullptr)
	, m_vOffsetPos(_origin->m_vOffsetPos)
	, m_vScale(_origin->m_vScale)
	, m_iID(g_iNextID++)
{
}
Collider::~Collider()
{
}



void Collider::finalupdate()
{
}

void Collider::render(HDC _dc)
{
}

