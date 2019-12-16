#pragma once

#include <string>
#include <map>

using namespace std;

typedef struct node{
	char ch;
	int freq;
	bool isLeaf;
	struct node* left;
	struct node* right;

	node(char c = ' '){
		this->ch = c;
		this->freq = 0;
		this->isLeaf = false;
		this->left = NULL;
		this->right = NULL;
	}

	node(node* tmp){
		this->ch = tmp->ch;
		this->freq = tmp->freq;
		this->isLeaf = tmp->isLeaf;
		this->left = tmp->left;
		this->right = tmp->right;
	}

	 //运算符重载，定义优先队列的比较结构
	friend bool operator <(const node &a,const node &b)
	{
		return a.freq > b.freq;           //这里是权值小的优先出队列
	}
}node;

class Huffman{
public:
	node* root;
	map<char, string> code;

	Huffman();
	//~Huffman(void);

	void initTree(string& str);
	void dfs(string str, node* tmp);
	string encode(string& str);

	string decode(string& str);


};