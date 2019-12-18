#pragma once

#include <string>
#include <cstring>
#include <string.h>
#include <vector>

using namespace std;


class OOK{
public:
	OOK(){};
	~OOK(){};

	string encode(vector<double>& vec);
	vector<double> decode(string& str);
	vector<double> modulate(string& str, int period = 16);
	vector<double> demodulate(vector<double>& vec, int period = 16);
};