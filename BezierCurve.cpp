#include "BezierCurve.h"



BezierCurve::BezierCurve()
{
}


BezierCurve::~BezierCurve()
{
}

BezierCurve::BezierCurve(const BezierCurve & c)
{
	for (int i = 0; i < c.points.size(); i++)
	{
		points.push_back(c.points[i]);
	}
}

void BezierCurve::addPoint(Vec2f p)
{
	points.push_back(p);
}

Vec2f BezierCurve::getPoint(int index)
{
	return points[index];
}

int BezierCurve::getSize()
{
	return points.size();
}

Vec2f BezierCurve::evaluate(double t)
{
	Vec2f result;
	Vec2f other;
	if (points.size() > 0)
	{
		if (points.size() == 1)
		{
			result = points[0];
		}
		else
		{
			result = (points[0] * (1.0 - t)) + (points[1] * t);

			for (int i = 1; i < points.size()-1; i++)
			{
				other = (points[i] * (1.0 - t)) + (points[i + 1] * t);
				result = (result * (1.0 - t)) + (other * t);
			}
		}
	}
	
	return result;
}
