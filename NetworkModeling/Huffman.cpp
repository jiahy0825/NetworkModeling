#include "stdafx.h"
#include "Huffman.h"

#include <string.h>
#include <string>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

void Huffman::initTree(string& str){
	map<char, int> m;
	priority_queue<node> q;
	node* tmp;
	for(char c : str){
		if (m.find(c) == m.end()){
			m[c] = 1;
		}else{
			m[c] += 1;
		}
	}
	for(map<char, int>::iterator iter = m.begin();iter != m.end();iter++){
		tmp = new node(iter->first);
		tmp->freq = iter->second;
		tmp->isLeaf = true;
		q.push(*tmp);
	}
	while (q.size() > 1){
		node left = q.top();
		q.pop();
		node right = q.top();
		q.pop();
		root = new node();
		root->freq = left.freq + right.freq;
		root->left = new node(left); //&left;
		root->right = new node(right); //&right;
		q.push(*root);
	}
}

void Huffman::dfs(string str, node* tmp){
	if(tmp->isLeaf){
		code[tmp->ch] = str;
		return;
	}
	if(tmp->left){
		dfs(str + "0", tmp->left);
	}
	if(tmp->right){
		dfs(str + "1", tmp->right);
	}
}

string Huffman::encode(string& str){
	initTree(str);
	code.clear();
	dfs("", root);

	// 计算平均码长
	map<char, int> m;
	for(char c : str){
		if (m.find(c) == m.end()){
			m[c] = 1;
		}else{
			m[c] += 1;
		}
	}
	averageCodeLength = 0;
	for (map<char, int>::iterator iter = m.begin();iter != m.end();iter++){
		averageCodeLength += (iter->second) * 1.0 / str.length() * code[iter->first].length();
	}

	string res = "";
	for(char c : str){
		res += code[c];
	}
	return res;
}

string Huffman::decode(string& str){
	string res = "";
	node* tmp = root;
	for (char c : str){
		try{
			if (c == '0'){
				tmp = tmp->left;
			}else if(c == '1'){
				tmp = tmp->right;
			}else{
				throw 1;
			}
			if(tmp->isLeaf){
				res += tmp->ch;
				tmp = root;
			}
			if(tmp == NULL){
				throw 1;
			}
		}catch (int e) {
			if (e == 1){
				"Huffman Decode error, invalid node : " + c;
			}
			return "Huffman Decode error code : " + to_string(e);
		}
	}
	return res;
}

