#ifndef _DATASET_H
#define _DATASET_H

#include "vector"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#define MAXINPUTONELINE 100000
using namespace std;

class Doc
{

public:
	vector<string> vec;
	int length;
	Doc(string oneline,string seperator,vector<string> vec);
	//Parse(string oneline,string seperator);
	~Doc();

	/* data */
};

class Key
{

public:
	int a;
	int b;
	Key(int a,int b){
		this->a = a;
		this->b = b;
	}

	friend bool operator <( Key const& left, Key const& right ){
		return left.a < right.a || ( left.a == right.a && left.b < right.b );
	}


	~Key(){

	}
	

	/* data */
};


class Dataset
{
public:
	Doc** docs;
	int M;
	int V;
	vector<string> stop;
	map<string,int> wordtoid;
	map<int,string> idtoword;
	map<Key,int> wordtotopic;
	//int * wordtoid2;
	//int * idtoword2;
	//int ** wordtotopic2;
	map<Key,int> part2;
	//int** num_v_k;

	Dataset(string filename,int K);
	Dataset(string filename,int K,string flag);
	static vector<string> ParsetoSingleword(string str,string seperator,vector<string> vec);
	vector<string> ParsetoSingleword(string str,string seperator);
	~Dataset();

	/* data */
};

#endif