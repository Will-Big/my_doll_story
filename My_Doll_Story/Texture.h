#pragma once

#include "Res.h"

class Texture :
	public Res
{
private:
	HDC m_dc;
	HBITMAP m_hBit;
	BITMAP m_bitInfo;

public:
	void Load(const wstring& _strFilePath);

	UINT Width() { return m_bitInfo.bmWidth; }
	UINT Height() { return m_bitInfo.bmHeight; }

	HDC GetDC() { return m_dc; }

private:
	Texture();
	~Texture();

	friend class ResManager;
};