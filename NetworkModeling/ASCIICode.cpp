#include "stdafx.h"
#include "ASCIICode.h"

#include <string>
#include <cstring>
#include <string.h>

using namespace std;

string ASCIICode::encodeChar(char ch){
	int k = 0x80;
	string res = "";
	for(int i = 0;i < 8;i++){
		if (ch & k){
			res += "1";
		}else{
			res += "0";
		}
		k >>= 1;
	}
	return res;
}

string ASCIICode::encode(string& str){
	string res = "";
	for (char c : str){
		res += encodeChar(c);
	}
	return res;
}

char ASCIICode::decodeChar(string& str, int start){
	int res = 0;
	for (int i = 0;i < 8;i++){
		res = res * 2 + (str[start + i] - '0');
	}
	return (char)res;
}

string ASCIICode::decode(string& str){
	int n = str.length();
	if(n % 8 != 0){
		return "ASCII code Error!";
	}
	string res = "";
	int start = 0;
	while (start < n){
		res += decodeChar(str, start);
		start += 8;
	}
	return res;
}