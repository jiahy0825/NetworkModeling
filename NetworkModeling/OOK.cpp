#include "stdafx.h"
#include "OOK.h"

#include <string.h>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>

// # define PI 3.14159265358979323846 

using namespace std;

#define PI acos(-1)
vector<double> modulePoints;

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
	res += to_string(vec[0]);
	for (int i = 1;i < vec.size();i++){
		res += "," + to_string(vec[i]);
	}
	return res;
}

vector<double> OOK::decode(string& str){
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
		}
	}
	return res;
}

string OOK::demodulate(vector<double>& vec, int period){
	string res = "";
	int idx = 0;
	// vec * sin
	while (idx < vec.size()){
		for (int i = 1;i <= period;i++){
			vec[idx + i - 1] = vec[idx + i - 1] * sin(2 * PI * i / period);
		}
		idx += period;
	}
	// 滑动平均
	vector<double> roll;
	double sum = 0;
	for (int i = 0;i < vec.size();i++){
		sum += vec[i];
		if (i >= 16){
			sum -= vec[i - 16];
		}
		roll.push_back(sum / period);
	}

	// 此处更新modulePoints，为画图做准备
	modulePoints = roll;

	idx = period / 2;
	while (idx < roll.size()){
		if (roll[idx] > 0.25){
			res += "1";
		}else{
			res += "0";
		}
		//res += "**" + to_string(roll[idx]) + "**\r\n";
		idx += period;
	}
	return res;
}