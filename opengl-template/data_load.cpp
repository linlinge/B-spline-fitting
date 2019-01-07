#include "data_load.h"
#include <fstream>

DataManager samples;

void DataManager::load_data(string path)
{
	ifstream f;
	string line;
	Vec3f temp3f;
	f.open(path);
	// load x range
	getline(f, line);
	string_2_vec3f(line, temp3f);
	x_min_ = temp3f.x;
	delta_x_ = temp3f.y;
	x_max_ = temp3f.z;
	nx_ = (x_max_ - x_min_) / delta_x_ + 1;
	// load y range
	getline(f, line);
	string_2_vec3f(line, temp3f);
	y_min_ = temp3f.x;
	delta_y_ = temp3f.y;
	y_max_ = temp3f.z;
	ny_ = (y_max_ - y_min_) / delta_y_ + 1;

	// load samples
	for (int i = 0; i < nx_; i++)
	{
		vector<Vec3f> temp_row_data;
		for (int j = 0; j < ny_; j++)
		{
			getline(f, line);
			string_2_vec3f(line, temp3f);			
			temp_row_data.push_back(temp3f);
		}
		samples_.push_back(temp_row_data);
	}
}

void DataManager::string_2_vec3f(string& in, Vec3f& out)
{	
	stringstream ss(in);
	string buf;
	vector<string> temp;
	while (ss >> buf)
	{
		temp.push_back(buf);
	}
	out.x = atof(temp[0].c_str());
	out.y = atof(temp[1].c_str());
	out.z = atof(temp[2].c_str());
}