#pragma once
class Vec2f
{
public:
	Vec2f()
	{

	}

	Vec2f(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2f(const Vec2f& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	~Vec2f()
	{

	}

	Vec2f operator+(Vec2f c)
	{
		return Vec2f(x + c.x, y + c.y);
	}

	Vec2f operator-(Vec2f c)
	{
		return Vec2f(x - c.x, y - c.y);
	}

	Vec2f operator*(double num)
	{
		return Vec2f(x*num, y*num);
	}

	Vec2f operator/(double num)
	{
		return Vec2f(x / num, y / num);
	}

	void operator+=(Vec2f c)
	{
		x += c.x;
		y += c.y;
	}

	void operator-=(Vec2f c)
	{
		x -= c.x;
		y -= c.y;
	}

	void operator*=(double num)
	{
		x *= num;
		y *= num;
	}

	void operator/=(double num)
	{
		x /= num;
		y /= num;
	}

	double x = 0;
	double y = 0;
private:
	
};

