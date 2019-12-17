#pragma once

#include <string>
#include <cstring>
#include <string.h>

using namespace std;

class ASCIICode{
public:
	ASCIICode(){};
	~ASCIICode(){};

	string encodeChar(char ch);
	char decodeChar(string& str, int start);
	string encode(string& str);
	string decode(string& str);
};