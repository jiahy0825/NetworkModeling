#pragma once

#include <string>
#include <cstring>
#include <string.h>

using namespace std;

class Hamming{
public:
	Hamming(){}
	~Hamming(){}

	int help(string& str, int start, int k);
	int encodeLen(int m);
	int decodeLen(int n);
	string encode(string& str);
	string decode(string& str);
	string encode74(string& str);
	string decode74(string& str);
};