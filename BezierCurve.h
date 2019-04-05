#pragma once
#include <vector>
#include "Vec2f.h"

class BezierCurve
{
public:
	BezierCurve();
	~BezierCurve();
	BezierCurve(const BezierCurve& c);

	void addPoint(Vec2f p);
	Vec2f getPoint(int index);

	int getSize();

	Vec2f evaluate(double t);

private:
	std::vector<Vec2f> points = std::vector<Vec2f>();
};

