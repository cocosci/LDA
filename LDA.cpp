
#include "LDA.h"
#include <queue>
#include <vector>
LDA::LDA(int argc, char** argv){
	this->niter = atoi(argv[1]);
	this->inputfilename = argv[2];
	this->K = atoi(argv[3]);
	this->alpha = atof(argv[4]);
	this->beta = atof(argv[5]);	
	string flag = argv[7];

	if(flag.compare("dir")==0){
		printf("Loading data...\n");
		this->input = new Dataset(this->inputfilename,this->K,flag);
	}
	else{
		//printf("!!\n");
		printf("Loading data...\n");
		this->input = new Dataset(this->inputfilename,this->K);
	}	
	
	//printf("done\n");

		//printf("one\n");

	this->initthreemap();
	
	//printf("one\n");
	for (int i = 0; i < this->K; ++i)
	{
		for (int j = 0; j < this->input->V; ++j)
		{
			Key p (i,j);
			this->phi.insert(pair<Key,double>(p,0));
		}
	}

	this->topkwordspertopic = atoi(argv[6]);
}
void LDA::printcurrentassn(){
	for (int j = 0; j < this->input->M; ++j)
		{
			for (int k = 0; k < this->input->docs[j]->length; ++k)
			{
				Key p(j,k);
				printf("%s(%d) ",this->input->docs[j]->vec[k].c_str(),this->input->wordtotopic[p] );
			}
			printf("\n");
		}
		printf("\n\n");
}
void LDA::Gibbssampling(){
	//int countount= 0 ;
	//FILE *f = fopen("topicassn.txt", "w");
	for (int i = 0; i < this->niter; ++i)
	{
		printf("====================Gibbs sampling at iteration %d=================\n",i );
		//int misscount = 0;
		//int outj = 0,outk = 0;
		//printcurrentassn();
		for (int j = 0; j < this->input->M; ++j)
		{
			for (int k = 0; k < this->input->docs[j]->length; ++k)
			{
				//Key p(j,k);
				double temp[this->K];
				//Key p1(j,k);
				int id = this->wordtoid2[j][k];	
				//printf("%s(%d) ",this->input->docs[j]->vec[k].c_str(),this->input->wordtotopic[p] );
				//printf("iteration %d, now samling w_%d,%d, i.e.%s----------\n",i,j,k,this->input->docs[j]->vec[k].c_str() );
				int ori = this->wordtotopic2[j][k];
				//Key p22221 (j,ori);
				//Key p22222 (id,ori);
				//this->part1[p22221]--;
				//this->part2[p22222]--;
				//this->part3[ori]--;
				this->num_v_k[id][ori]--;
				this->num_k[ori]--;
				this->num_k_j[j][ori]--;
				for (int t = 0; t < this->K; ++t)
				{
					//temp[t] = (this->Statpart1(j,k,t)*this->Statpart2(j,k,t))/(double)this->Statpart3(j,k,t);
					//temp[t] = 1;
					//int id = this->input->wordtoid
					//Key p33 (id,t);
					//Key p332 (j,t);
					//printf("The total count for the word /%s/ being assigned to topic %d is %d\n",this->input->docs[j]->vec[k].c_str(),t,this->num_v_k[id][t] );
					//printf("The total count for the words being assigned to topic %d in in doc %d is %d\n",t,j,this->num_k_j[j][t] );
					//printf("The total count for all the words being assigned to topic %d in all docs  is %d\n",t,this->num_k[t] );
					//temp[t] = this->ThreeinOneSampling(j,k,t);
					//temp[t] = ((double)(this->part2[p33]  + this->beta)/(this->part3[t] +this->input->V * this->beta))* ((double)( this->part1[p332]  + this->alpha )/(this->input->docs[j]->length-1+ this->K*this->alpha) );					
					//printf("%d %d %d %d\n",this->part2[p33]== this->num_v_k[id][t]);
					temp[t] = 	((double)(this->num_v_k[id][t]  + this->beta)/(this->num_k[t] +this->input->V * this->beta))* ((double)( this->num_k_j[j][t]  + this->alpha )/(this->input->docs[j]->length-1+ this->K*this->alpha) );					
						//Key p2(j,t);					
						//Key p22 (id,t);
						//if (t==this->input->wordtotopic[p1]){
						//	temp[t] = (double)(this->part1[p2]-1  + this->alpha)*(this->part2[p22]-1  + this->beta)/(this->part3[this->input->wordtotopic[p1]] -1 + this->input->V * this->beta);
						//}
						//else{
						//	temp[t] = (double)(this->part1[p2] + this->alpha)*(this->part2[p22] + this->beta)/(this->part3[this->input->wordtotopic[p1]] + this->input->V * this->beta);
						//}
//
					//printf("prob of t%d = %f\n",t,temp[t]);					
				}
				int topicassn = GetMax(temp,this->K);
				//if(i == 999)
				
				//int ori = this->input->wordtotopic[p];
				//printf("original topic assgiment of w_%d,%d, i.e.%s is %d\n",j,k,this->input->docs[j]->vec[k].c_str(),ori );
				//printf("new topic assgiment is %d\n\n\n",topicassn );
		//int flag = topicassn == ori;
		//if (!flag)
		//{
		//	//printf("topicassn=%d,ori=%d\n", topicassn,ori);
		//	misscount++;
		//}
				//this->input->wordtotopic.insert(pair<Key,int>(p,topicassn)); 
				//printf("before%d\n",this->input->wordtotopic[p] );
				//this->input->wordtotopic[p]=topicassn;
				this->wordtotopic2[j][k] = topicassn;
				// calculate phi optimized
				//printcurrentassn();
			
				//printf("after%d\n",this->input->wordtotopic[p] );
if(i==this->niter-1){					
	//this->phi.insert(pair<Key,double>(p22,this->phi[p22]+1));
	//this->phi.insert(pair<Key,double>(p21,this->phi[p21]-1));
	//int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
	Key p22 (topicassn,id);
	this->phi[p22] = this->phi[p22]+1;
	//this->phi[p21]--;						
//  	//int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
				//Key p (i,id);
	//fprintf(f, "%d ",topicassn );
}
				//update the three mapping strucutures to keep track of the part1,2,3.
				//printf("%d %d %d\n",this->part1 );
				
				//Key p222221 (j,topicassn);
				//Key p222222 (id,topicassn);
				//this->part1[p222221]++;
				//this->part2[p222222]++;
				//this->part3[topicassn]++;
//
				this->num_v_k[id][topicassn]++;
				this->num_k[topicassn]++;
				this->num_k_j[j][topicassn]++;
				//this->updatethreemap(j,k,flag,ori,topicassn);
			}
			//printf("\n");
			//if (i==this->niter-1)
		//fprintf(f, "\n\n ");
		}
		//if (misscount==0)
		//{
		//	///* code */break;
		//	printf("from last time, the total number of changed topic assignments is %d\n", misscount);	
		//	break;
		//}
		//else{
		//	printf("from last time, the total number of changed topic assignments is %d\n", misscount);	
		//}		
	}
	//fclose(f);
	//printf("%d\n",this->input->V );
	//writephi();
}
void LDA::writephi(){
	FILE *f = fopen("phibefore.txt", "w");
	for(int i = 0;i<this->K;i++){
	for (int j = 0; j < this->input->M; ++j)
	{
		for (int k = 0; k < this->input->docs[j]->length; ++k)
		{
			int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
			Key p (i,id);
			fprintf(f, "%d ",(int)this->phi[p] );
		}
		fprintf(f, "\n");
	}
	fprintf(f, "--------------------------------------------\n");
}
	fclose(f);
}
void LDA::updatethreemap(int j, int k, int flag, int ori, int recent){
	if(!flag){
		//part1
		//printf("update %d,%d,%d,%d,%d\n",j,k,flag,ori,recent );
		Key p1 (j,ori);
		//printf("thispart%d\n",this->part1[p1] );
		this->part1[p1]=this->part1[p1]-1;
		//printf("thispartff%d\n",this->part1[p1] );

		Key p2 (j,recent);
		this->part1[p2] = this->part1[p2]+1;
		//part2
		int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
		Key p3 (id,ori);
		this->part2[p3] = this->part2[p3] -1;
		Key p4 (id,recent);
		this->part2[p4] = this->part2[p4] +1;
		//part3
		this->part3[ori]--;
		this->part3[recent]++;
	}
}	

void LDA::initthreemap(){
	this->num_k_j = new int*[this->input->M];
	this->num_k = new int[this->K];
	this->wordtotopic2 = new int*[this->input->M];
	this->wordtoid2 = new int*[this->input->M];
	int res1 = 0,res2 = 0,res3 = 0;
	for (int i = 0; i < this->input->M; ++i)
	{	
		this->num_k_j[i] = new int[this->K];
		this->wordtotopic2[i] = new int[this->input->docs[i]->length];
		this->wordtoid2[i] = new int[this->input->docs[i]->length];
	}

	for (int k = 0; k < this->K; ++k)
	{	
		for (int i = 0; i < this->input->M; ++i)
		{		
			for (int t = 0; t < this->input->docs[i]->length; ++t)
			{			
				Key p2 (i,t);	
				this->wordtotopic2[i][t] = this->input->wordtotopic[p2];
				this->wordtoid2[i][t] = this->input->wordtoid[this->input->docs[i]->vec[t]];	
				if(this->wordtotopic2[i][t]==k){
					res3++;
					res1++;
				}											
			}
			//printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
			Key p1(i,k);
			this->part1.insert(pair<Key,int>(p1,res1));//all words in doc i that are assigned to k
			this->num_k_j[i][k]=res1;
			//printf("@@@@@@@@@@%d\n",res1 );
			res1 = 0;
		}
		this->num_k[k] = res3;
		this->part3.insert(pair<int,int>(k,res3));
		//printf("@@@@@@@@@@####%d\n",res3 );
		res3 = 0;
	}

	this->part2 = this->input->part2;
	this->num_v_k = new int*[this->input->V];


	for (int i = 0; i < this->input->V; ++i)
	{
		this->num_v_k[i] = new int[this->K];
		for (int j = 0; j<this->K;++j)
		{
			Key p (i,j);
			this->num_v_k[i][j] = this->input->part2[p];
			//printf("%d--%d==%d,%d\n",i,j,this->part2[p],this->input->part2[p] );
		}
	}
//	for (int k = 0; k < this->K; ++k)
//	{
//		printf("%d\n", k);
//		for(int ipart2 = 0;ipart2 < this->input->V;ipart2++)
//		{
//			printf("%d\n",this->input->V );
//			printf("%d\n", ipart2);
//			for (int i = 0; i < this->input->M; ++i)
//			{
//				for (int t = 0; t < this->input->docs[i]->length; ++t)
//				{
//					Key p2(i,t);
//					if(this->input->docs[i]->vec[t].compare(this->input->idtoword[ipart2]) && this->input->wordtotopic[p2]== k)
//					{
//						res2++;
//					}
//				}
//			}
//			Key p3(ipart2,k);
//			this->part2.insert(pair<Key,int>(p3,res2));
//		}
//	
//	}
	
}
void LDA::CalculateThetanPhi(){


	//calculate n(z,w) for all w.
	for (int i = 0; i < this->K; ++i)
	{
		//printf("%d\n",i );
		for (int m = 0; m < this->input->M; ++m)
		{
			for (int n = 0; n < this->input->docs[m]->length; ++n)
			{
				Key p1 (m,n);
				if(this->input->wordtotopic[p1]==i){
					this->phisum[i]++;
				}
				//delete p1;
			}
		}
		//printf("####################phi%d\n",this->phisum[i] );
	}

	for (int i = 0; i < this->K; ++i)
	{
		//printf("%d\n",i );
		for (int j = 0; j < this->input->V; ++j)
		{
			
			Key p2 (i,j);
			//this->phi.insert(pair<Key,double>(p2,this->phi[p2]/(double)phisum[i]));
			//printf("phiphip%f\n", this->phi[p2]);
			this->phi[p2]=(this->phi[p2]+this->beta)/(double)(this->phisum[i]+this->input->V*this->beta);
			//delete p2;
		}
	}

	for (int i = 0; i < this->input->M; ++i)
	{
		//printf("%d\n",i );
		for (int j = 0; j < this->K; ++j)
		{	
			// first two loops deal with the theta matrix
			int thetacount = 0;
			//for (int m = 0; m < this->input->M; ++m)
			//{
				for (int n = 0; n < this->input->docs[i]->length; ++n)
				{
					// calculate n(d,z)
					Key p1 (i,n);
					if(this->wordtotopic2[i][n]==j){
						thetacount++;
					}
					//delete p1;
				}
			//}
			Key p2 (i,j);
			//this->theta.insert(pair<Key,double>(p2,(double)(thetacount)/(double)(this->input->docs[i]->length)));
			//printf("%d %d\n",thetacount,this->input->docs[i]->length );
			this->theta.insert(pair<Key,double>(p2,(double)(thetacount+this->alpha)/(double)(this->input->docs[i]->length+this->K*this->alpha)));
			//delete p2;
		}
		//printf("\n");
	}
}
void LDA::Saveres(){
	printf("**************************Important Results************************\n");
	printf("For doc-topic, go to 'theta.txt'.\n");
	printf("For topic-word, go to 'top k words per topic.txt'.\n");
	FILE *f = fopen("theta.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	for (int i = 0; i < this->input->M; ++i)
	{
		for (int j = 0; j < this->K; ++j)
		{	
			Key p2 (i,j);
			fprintf(f, "%f ", this->theta[p2]);
			//delete p2;
		}
		fprintf(f, "\n" );
	}
	fclose(f);

	FILE *f2 = fopen("phi.txt", "w");
	if (f2 == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	for (int i = 0; i < this->K; ++i)
	{
		for (int j = 0; j < this->input->V; ++j)
		{	
			Key p2 (i,j);
			fprintf(f2, "%f ", this->phi[p2]);
			//delete p2;
		}
		fprintf(f2, "\n" );
	}
	fclose(f2);

	FILE *f3 = fopen("wordtotopic.txt", "w");
	if (f3 == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	for (int i = 0; i < this->input->M; ++i)
	{
		for (int j = 0; j < this->input->docs[i]->length; ++j)
		{	
			Key p2 (i,j);
			fprintf(f3, "%d ", this->input->wordtotopic[p2]);
			//delete p2;
		}
		fprintf(f3, "\n" );
	}
	fclose(f3);

	LDA::PhitoMat();
}
//此处有问题，part2不是减一。而是w_jk的。。。 反正是phi不收敛，感觉topic混在一起。
//首先，topic是给每一个jk而不是一个id一个。分母原来也有错误。part2之前的访问也不对。然后增加了几个写函数。
// 结果从来就不好，不是改差的，之前调成了一个比较好的。
// 之前也不收敛。
double LDA::ThreeinOneSampling(int j, int k,int t){
	Key p1(j,k);
	Key p2(j,t);
	int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
	Key p22 (id,t);
//	if (t==this->input->wordtotopic[p1]){
//		//return (double)(this->part1[p2]-1  + this->alpha)*(this->part2[p22]-1  + this->beta)/(this->part3[this->input->wordtotopic[p1]] -1 + this->input->V * this->beta);
//		//return (double)((this->part2[p22]-1)*this->beta+this->alpha+(this->part1[p2]-1))/(this->part3[this->input->wordtotopic[p1]] -1+this->input->V * this->beta * (this->input->docs[j]->length-1) + this->K*this->alpha);
//		//printf("Calculate the prob of this word being assigned to topic %d,(%f/%f)*(%f/%f)\n",t,this->part2[p22]-1  + this->beta,this->part3[this->input->wordtotopic[p1]] -1+this->input->V * this->beta,this->part1[p2]-1  + this->alpha ,this->input->docs[j]->length-1+ this->K*this->alpha );
//		return ((double)(this->part2[p22]-1  + this->beta)/(this->part3[this->input->wordtotopic[p1]] -1+this->input->V * this->beta))* ((double)( this->part1[p2]-1  + this->alpha )/(this->input->docs[j]->length-1+ this->K*this->alpha) );
//	}
//	else{
		//return (double)(this->part1[p2] + this->alpha)*(this->part2[p22] + this->beta)/(this->part3[this->input->wordtotopic[p1]] + this->input->V * this->beta);
		//return (double)((this->part2[p22])*this->beta+this->alpha+(this->part1[p2]))/(this->part3[this->input->wordtotopic[p1]] +this->input->V * this->beta * (this->input->docs[j]->length-1) + this->K*this->alpha);
		//printf("Calculate the prob of this word being assigned to topic %d,(%f/%f)*(%f/%f)\n",t,this->part2[p22]  + this->beta,this->part3[this->input->wordtotopic[p1]] +this->input->V * this->beta,this->part1[p2]  + this->alpha ,this->input->docs[j]->length-1+ this->K*this->alpha );
	return ((double)(this->part2[p22]  + this->beta)/(this->part3[t] +this->input->V * this->beta))* ((double)( this->part1[p2]  + this->alpha )/(this->input->docs[j]->length-1+ this->K*this->alpha) );
//	}
	
}
double LDA::Statpart1(int j, int k,int t){
	Key p1(j,k);
	Key p2(j,t);
	if (t==this->input->wordtotopic[p1]){
		return this->part1[p2] -1 + this->alpha;
	}
	else{
		return this->part1[p2] + this->alpha;
	}
}
double LDA::Statpart2(int j, int k,int t){
	Key p1(j,k);
	int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
	Key p2(id,t);
	if (t==this->input->wordtotopic[p1]){
		return this->part2[p2] -1 + this->beta;
	}
	else{
		return this->part2[p2] + this->beta;
	}
}
double LDA::Statpart3(int j, int k,int t){
	Key p1(j,k);
	//int id = this->input->wordtoid[this->input->docs[j]->vec[k]];
	if (t==this->input->wordtotopic[p1]){
		return this->part3[t] -1 + this->input->V * this->beta;
	}
	else{
		return this->part3[t] + this->input->V * this->beta;
	}
}

int LDA::GetMax(double temp[],int size){
	//double current = -1;
	//int index = -1;
	//for (int i = 0; i < size; ++i)
	//{
	//	//printf("%f ",temp[i] );
	//	if (current < temp[i]){
	//		current = temp[i];
	//		index = i;
	//	}
	//
	//}
	////printf("\n");
	////printf("current index is %d\n",index );
	//return index;

	int topic = 0;
	for (int i = 1; i < size; ++i)
	{
		temp[i] += temp[i-1];
	}
	double u = ((double)random() / RAND_MAX) * temp[size - 1];
	//printf("%f ,, %f\n",u,temp[size - 1] );
	for (; topic < size; ++topic)
	{
		if(temp[topic]>u)
			break;
	}
	//printf("%d\n",topic );
	return topic;
}
// get the indices of n largest elements in phi.
void LDA::PhitoMat(){
	//int mat[this->K][this->topkwordspertopic];
	FILE *f = fopen("top k words per topic.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}

	
	
	for (int i = 0; i < this->K; ++i)
	{
	//	printf("%d\n",i );
		fprintf(f, "Topic %d:\n", i);
		std::vector<double> test;
		for (int j = 0; j < this->input->V; ++j)
		{
		//	printf("%d\n",j );
			Key p (i,j);
			//mat[i][j] = this->phi[p];
			test.push_back(this->phi[p]);
		}
		priority_queue<pair<double, int> > q;// > > not >>
		for (int m = 0; m < test.size(); ++m) {
			//printf("%d\n",m );
			q.push(std::pair<double, int>(test[m], m));
		}
		int k = this->topkwordspertopic; // number of indices we need
		for (int n = 0; n < k; ++n) {
			int ki = q.top().second;
			fprintf(f, "%s\n", this->input->idtoword[ki].c_str());
			q.pop();
	  	}
	  	fprintf(f, "\n");
	}
	fclose(f);
	//printf("####%d\n",this->input->V);
}
LDA::~LDA(){
	delete input;
}

