#include "pch.h"
#include "Texture.h"
#include "Main.h"

Texture::Texture()
	:m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{

}

Texture::~Texture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void Texture::Load(const wstring& _strFilePath)
{
	// ���Ϸκ��� �ε��� �����͸� ��Ʈ������ ����
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0 , 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(m_hBit != nullptr);

	// ��Ʈ�ʰ� ������ DC
	m_dc = CreateCompatibleDC(Main::GetInst()->GetMainDC());

	//��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// ��Ʈ�� ����
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);
}