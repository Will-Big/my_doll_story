class SelectGDI
{
private:
	HDC m_hDC;
	HBRUSH m_hDefaultBrush;
	HPEN m_hDefaultPen;

public:
	SelectGDI(HDC _dc, PEN_TYPE _ePenType);
	SelectGDI(HDC _dc, BRUSH_TYPE _eBrushType);
	~SelectGDI();



};

