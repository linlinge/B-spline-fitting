#pragma once
#include <math.h>
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Vec3f
{
public:
	union {
		struct {
			float r, g, b;
		};
		struct {
			float x, y, z;
		};
	};
	Vec3f() :r(0.0f), g(0.0f), b(0.0f) {};
	Vec3f(float r1, float g1, float b1)
	{
		r = r1;
		g = g1;
		b = b1;
	};
	Vec3f & operator=(const Vec3f & obj)
	{
		r = obj.r;
		g = obj.g;
		b = obj.b;
		return (*this);
	}

	float DistanceXY(Vec3f & dat)
	{
		return sqrt(pow(x - dat.x, 2.0f) + pow(y - dat.y, 2.0f));
	}
	float Distance(Vec3f & dat)
	{
		return sqrt(pow(x - dat.x, 2.0f) + pow(y - dat.y, 2.0f) + pow(z - dat.z, 2.0f));
	}

	Vec3f& operator *(float scale)
	{
		x = x * scale;
		y = y * scale;
		z = z * scale;
		return *this;
	}
	Vec3f& operator /(float scale)
	{
		x = x / scale;
		y = y / scale;
		z = z / scale;
		return *this;
	}
	Vec3f& operator +(Vec3f & dat)
	{
		x = x + dat.x;
		y = y + dat.y;
		z = z + dat.z;
		return *this;
	}

	float GetArc(Vec3f& dat)
	{
		float arc = x * dat.x + y * dat.y + z * dat.z;
		return arc / sqrt(x*x + y * y + z * z) / sqrt(dat.x*dat.x + dat.y*dat.y + dat.z*dat.z);
	}

	static Vec3f GetNorm(Vec3f& dat)
	{
		Vec3f norm = dat;
		float a = sqrt(dat.x*dat.x + dat.y * dat.y + dat.z * dat.z);
		return norm / a;
	}

	static Vec3f Dot(Vec3f& dat1, Vec3f& dat2)
	{
		Vec3f rst;
		rst.x = dat1.y * dat2.z - dat2.y * dat1.z;
		rst.y = dat2.x * dat1.z - dat1.x * dat2.z;
		rst.z = dat1.x * dat2.y - dat2.x * dat1.y;
	}

};