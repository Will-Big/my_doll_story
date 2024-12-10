#include "pch.h"
#include "Background.h"

#include "ResManager.h"
#include "Texture.h"

#include "Animator.h"

#include "Main.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::SetCenterPos()
{
	Vec2 vResolution = Main::GetInst()->GetResolution();

	SetPos(Vec2(vResolution.x / 2.f, vResolution.y / 2.f));
}

void Background::update()
{
}

void Background::render(HDC _dc)
{
	// �ؽ�ó ũ�� ����
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	// //���÷��� �߾ӿ� �ؽ�ó �׸���
	//BitBlt(_dc,
	//	(int)vPos.x - iWidth / 2,
	//	(int)vPos.y - iHeight / 2,
	//	iWidth, iHeight,
	//	m_pTex->GetDC(),
	//	0, 0,
	//	SRCCOPY);

	//TransparentBlt(_dc,
	//	int(m_vPos.x - m_vScale.x / 2.f),
	//	int(m_vPos.y - m_vScale.y / 2.f),
	//	int(m_vPos.x + m_vScale.x / 10.f),
	//	int(m_vPos.y + m_vScale.y / 10.f),
	//	m_pTex->GetDC(),
	//	0,
	//	0,
	//	m_pTex->Width(),
	//	m_pTex->Height(),
	//	RGB(255, 255, 255)
	//);

	BitBlt(_dc,
		int(m_vPos.x - m_vScale.x / 2.f),
		int(m_vPos.y - m_vScale.y / 2.f),
		int(m_vPos.x + m_vScale.x / 2.f),
		int(m_vPos.y + m_vScale.y / 2.f),
		m_pTex->GetDC(),
		0,
		0,
		SRCCOPY
	);
}

void Background::finalupdate()
{
}

