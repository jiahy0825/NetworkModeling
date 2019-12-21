#include "stdafx.h"
#include "OOK.h"

#include <string.h>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
//#include <iostream>
#include <iomanip>
#include <sstream>

#include <random>
#include <chrono>

 //# define PI 3.14159265358979323846 

using namespace std;

#define PI acos(-1)

// C++库中没有split函数，需要自己实现
vector<string> split(const string& str, const std::string& delim){
	vector<string> res;
	string::size_type pos1, pos2;
	pos2 = str.find(delim);
	pos1 = 0;
	while(string::npos != pos2){
		res.push_back(str.substr(pos1, pos2-pos1));
		pos1 = pos2 + delim.size();
		pos2 = str.find(delim, pos1);
	}
	if(pos1 != str.length())
	res.push_back(str.substr(pos1));
	return res;
}

string OOK::encode(vector<double>& vec){
	string res = "";
	if(vec.empty()){
		res = "OOK encode vector is empty";
		return res;
	}

	stringstream stream;
	stream << fixed << setprecision(4) << vec[0];
	for (int i = 1;i < vec.size();i++){
		stream << "," << vec[i];
	}
	res = stream.str();

	//res += to_string( ((int)(vec[0] * 100) / 100.0) );
	//for (int i = 1;i < vec.size();i++){
	//	res += "," + to_string( ((int)(vec[i] * 100) / 100.0) );
	//}

	return res;
}

vector<double> OOK::decode(string& str){
	if (str == "OOK encode vector is empty"){
		return vector<double>();
	}
	vector<string> vec = split(str, ",");
	vector<double> res;
	for (int i = 0;i < vec.size();i++){
		res.push_back(stod(vec[i]));
	}
	return res;
}

vector<double> OOK::modulate(string& str, int period){
	vector<double> res;
	int ch;
	for (char c : str){
		ch = c - '0';
		for (int i = 1;i <= period;i++){
			res.push_back(ch * sin(2 * PI * i / period));
			//res.push_back(ch * cos(2 * PI * i / period));
		}
	}
	return res;
}

vector<double> OOK::demodulate(vector<double>& vec, int period){
	string res = "";
	int idx = 0;
	// vec * sin
	while (idx < vec.size()){
		for (int i = 1;i <= period;i++){
			vec[idx + i - 1] = vec[idx + i - 1] * sin(2 * PI * i / period);
			//vec[idx + i - 1] = vec[idx + i - 1] * cos(2 * PI * i / period);
		}
		idx += period;
	}
	// 滑动平均
	// 计算r[n]的滑动平均需要将周期除以2
	vector<double> roll;
	period /= 2;
	double sum = 0;
	for (int i = 0;i < vec.size();i++){
		sum += vec[i];
		if (i >= period){
			sum -= vec[i - period];
		}
		roll.push_back(sum / period);
	}

	// 此处更新modulePoints，为画图做准备
	return roll;
}

vector<double> OOK::addNoise(vector<double>& vec, double sigma){
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
  
	default_random_engine generator(seed);
	// 第一个参数为高斯分布的平均值，第二个参数为标准差
	std::normal_distribution<double> distribution(0.0, sigma);

	vector<double> res;
	for (int i = 0; i < vec.size();i++){
		res.push_back(vec[i] + distribution(generator));
	}
	return res;
}