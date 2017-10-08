#pragma once

class Point
{
public:
	Point(double x = 0.0, double y = 0.0) : mX(x), mY(y) {};
	~Point();

public:
	double mX;
	double mY;
};

