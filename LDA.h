#ifndef _LDA_H
#define _LDA_H

#include "dataset.h"
class LDA
{
public:
	int niter;
	int K;
	float alpha;//historical value
	float beta;//historical value
	int topkwordspertopic;
	string inputfilename;
	//string outputfilename;
	map<Key,double> phi;// it's wrong to say the word id belong to topic is this prob. 
	//map<Key,double> phiinit;
	map<Key,double> theta;

	map<Key,int> part1;
	map<Key,int> part2;
	map<int,int> part3;
	int ** num_k_j;
	int ** num_v_k;
	int * num_k;
	int ** wordtotopic2;
	int ** wordtoid2;
	int phisum[1000];//assume we have more than 1000 topics.
	Dataset* input;


	LDA(int argc, char** argv);
	//void init(int argc, char** argv);
	void writephi();
	void Gibbssampling();
	void CalculateThetanPhi();
	void Saveres();
	void PhitoMat();
	void initthreemap();
	void printcurrentassn();
	void updatethreemap(int j, int k, int flag, int ori, int recent);
	double Statpart1(int j, int k,int t);
	double Statpart2(int j, int k,int t);
	double Statpart3(int j, int k,int t);
	double ThreeinOneSampling(int j, int k,int t);
	int GetMax(double temp[], int size);
	~LDA();

	/* data */
};
#endif