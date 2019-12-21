#include "stdafx.h"
#include "Hamming.h"

#include <string.h>
#include <string>
#include <cstring>

int Hamming::encodeLen(int m){
	int res = 1;
	while ((int)pow(2, res) < m + res + 1){
		res++;
	}
	return res;
}

int Hamming::decodeLen(int n){
	double res = log(n) / log(2);
	int r = (int)res;
	// res可能计算的值为精确值
	if (abs(res - r) < 1e-5){
		return r;
	}
	return r + 1;
}

int Hamming::help(string& str, int start, int k){
	int res = 0;
	int n = str.length();
	while (start < n){
		for(int i = 0;i < k && i + start < n;i++){
			res = res ^ (str[i + start] - '0');
		}
		start += 2 * k;
	}
	return res;
}

string Hamming::encode(string& str){
	int m = str.length();
	int r = encodeLen(m);
	int n = m + r;
	// 首字符保留
	string res = string(n + 1, '0');
	int k = 1;
	int idx = 0;
	for (int i = 1;i <= n;i++){
		if (i == k){
			res[i] = '0';
			k *= 2;
		}else{
			res[i] = str[idx++];
		}
	}
	//assert(idx == m && k == (int)pow(2, r));
	k = 1;
	for (int i = 0;i < r;i++){
		res[k] = (char)('0' + help(res, k, k));
		k *= 2;
	}
	return res;
}

string Hamming::decode(string& str){
	// n中包括保留的首字符
	int n = str.length();
	n--;
	int r = decodeLen(n);
	int k = 1;
	string hamm = "";
	for (int i = 0;i < r;i++){
		hamm += (char)('0' + help(str, k, k));
		k *= 2;
	}
	reverse(hamm.begin(), hamm.end());
	int idx = 0;
	for(int i = 0;i < hamm.length();i++){
		idx = idx * 2 + hamm[i] - '0';
	}
	//assert(idx <= n);
	if (idx > n){
		return "Hamming Decode error";
	}
	// 对idx位取反
	str[idx] = (char)('0' + !(str[idx] - '0'));
	string res = "";
	k = 1;
	for (int i = 1;i <= n;i++){
		if (i == k){
			k *= 2;
		}else{
			res += str[i];
		}
	}
	return res;
}