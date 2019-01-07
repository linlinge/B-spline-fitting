#pragma once
#include "main.h"
#include <sstream>
class DataManager
{
public:
	float x_min_, x_max_, y_min_, y_max_;	
	float delta_x_, delta_y_;
	int nx_, ny_;
	vector<vector<Vec3f>> samples_;
	void load_data(string path);
	void string_2_vec3f(string& in, Vec3f& out);
};

extern DataManager samples;