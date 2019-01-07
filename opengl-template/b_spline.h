#pragma once
#include "main.h"
#include <fstream>
#define ORDER 4
enum KnotType
{
	UniformlySpacedMethod,
	ChordLengthMethod,
	CentripetalMethod
};

class B_spline
{
public:
	vector<float> knot_;
	vector<vector<Vec3f>> surface_;

	void fitting_curve( vector<float>& datx, vector<float>& daty, vector<float>& Pval);
	float BaseFunction(int k, int m, float t);	
	void fitting_surface(vector<vector<Vec3f>>& dat, vector<vector<Vec3f>>& out);
};

void tranpose(vector<vector<float>>& dat);