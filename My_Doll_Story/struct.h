#pragma once



struct Vec2
{
	float x;
	float y;

public:
	Vec2()
		:x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(int _x, int _y)
		:x((float)_x)
		, y((float)_y)
	{}

	Vec2(POINT _pt)
		: x((float)_pt.x)
		, y((float)_pt.y)
	{}

	// ���� ������ �����ε�
	Vec2 operator+(const Vec2& _other) const
	{
		return Vec2(x + _other.x, y + _other.y);
	}

	// ���� ������ �����ε� (��Į�� ��)
	Vec2 operator+(float _scalar) const
	{
		return Vec2(x + _scalar, y + _scalar);
	}

	// ���� ������ �����ε�
	Vec2 operator-(const Vec2& _other) const
	{
		return Vec2(x - _other.x, y - _other.y);
	}

	// ���� ������ �����ε� 
	Vec2 operator*(const Vec2& _other)
	{
		return Vec2(x * _other.x, y * _other.y);
	}

	// ���� ������ �����ε� (��Į�� ��)
	Vec2 operator*(float _scalar) const
	{
		return Vec2(x * _scalar, y * _scalar);
	}

	// �� ������ �����ε�
	bool operator<(const Vec2& _other) const
	{
		return x < _other.x;
	}
};

struct MapIndex
{
	int y;
	int x;
};