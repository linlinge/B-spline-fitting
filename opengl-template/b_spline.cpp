#include "b_spline.h"

float B_spline::BaseFunction(int k, int m, float t)
{	
	if (m==1)
	{
		if (knot_[k] < t && t < knot_[k + 1])
			return  1.0f;
		else
			return 0.0f;
	}
	else
	{
		if (knot_[k + m - 1] == knot_[k] || knot_[k + m] == knot_[k + 1])
			return 0.0f;
		else
			return ((t - knot_[k]) / (knot_[k+m-1]-knot_[k])*BaseFunction(k,m-1,t) + (knot_[k+m]-t) / (knot_[k+m]-knot_[k+1])*BaseFunction(k+1,m-1,t));
	}	
}

void B_spline::fitting_curve(vector<float>& datx, vector<float>& daty,vector<float>& Pval)
{
	// init Pval
	Pval.clear();

	// generate knot
	int n = datx.size();
	int m = ORDER;
	knot_.clear();
	float start = datx[0];
	float end = datx[datx.size() - 1];
	float delta = (end - start) / (datx.size()-1);
	float temp=start;
	for (int i = 0; i <= n + m; i++)
	{
		if(i<=m-3)
			knot_.push_back(0);
		else if(i<= n+m-2)
		{
			knot_.push_back(temp);
			temp += delta;
		}
		else
			knot_.push_back(end);
	}

	// caculate N
	MatrixXf N(n,n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			N(i, j) = BaseFunction(i+1,ORDER,datx[j]);
		}
	}

	// caculate Q
	MatrixXf Q(n, 1);
	for (int i = 0; i < n; i++)
	{
		float sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += BaseFunction(i,ORDER,datx[j]);
		}
		sum = sum * daty[i];
		Q(i, 0) = sum;
	}
	MatrixXf P(n, 1);

	MatrixXf temp_N = N.transpose()*N;
	//ofstream f("../data/debug.txt");	

	P = temp_N.inverse()*N.transpose()*Q;

	/*f << P;
	f.close();*/
	for (int i = 0; i < n; i++)
	{
		Pval.push_back(P(i, 0));
	}
	Pval[0] = daty[0];
	Pval[1] = daty[1];
}


void B_spline::fitting_surface(vector<vector<Vec3f>>& dat, vector<vector<Vec3f>>& out)
{
	// init out
	out.resize(dat.size());
	for (auto& line : out)
	{
		line.resize(dat[0].size());
	}

	// init control points
	int rows = dat.size();
	int cols = dat[0].size();
	vector<vector<float>> ControlPoints;
	vector<vector<float>> out_float;
	
	ControlPoints.resize(rows);
	out_float.resize(cols);
	for (auto& temp : ControlPoints)  temp.resize(cols);
	for (auto& temp : out_float)  temp.resize(rows);
		

	// init tx,ty
	vector<float> tx, ty;
	for (int j = 0; j < cols; j++) tx.push_back(dat[0][j].x);
	for (int i = 0; i < rows; i++) ty.push_back(dat[i][0].y);


	// fitting on x (horizontal) direction
	for (int i = 0; i < rows; i++)
	{
		vector<float> row_val;
		for (int j = 0; j < cols; j++)
		{			
			row_val.push_back(dat[i][j].z);
		}
		fitting_curve(tx,row_val,ControlPoints[i]);
	}
	tranpose(ControlPoints);

	// fitting on y (vertical) direction
	for (int i = 0; i < ControlPoints.size(); i++)
	{	
		fitting_curve(ty, ControlPoints[i], out_float[i]);
	}

	tranpose(out_float);

	for (int i = 0; i < out.size(); i++)
	{
		for (int j = 0; j < out[0].size(); j++)
		{
			out[i][j].x = dat[i][j].x;
			out[i][j].y = dat[i][j].y;
			out[i][j].z = out_float[i][j];
		}
	}
}

void tranpose(vector<vector<float>>& dat)
{
	vector<vector<float>> temp;
	for (int j = 0; j < dat[0].size(); j++)
	{
		vector<float> line;
		for (int i = 0; i < dat.size(); i++)
		{
			line.push_back(dat[i][j]);
		}
		temp.push_back(line);
	}

	dat.clear();
	for (int i = 0; i < temp.size(); i++)
	{
		vector<float> line;
		for (int j = 0; j < temp[0].size(); j++)
		{
			line.push_back(temp[i][j]);
		}
		dat.push_back(line);
	}
}


