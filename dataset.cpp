
#include <dirent.h>

#include "dataset.h"
#include  <random>
#include <cstdlib>
/*each line is a document. But now we need to */

Doc::Doc(string str,string seperator,vector<string> vec){  
	// call the static method in Dataset to parse each paragraph into list of words and push back
	// to the vector. Stop words are screened.
	this->vec = Dataset::ParsetoSingleword(str,seperator,vec);
	this->length = this->vec.size();  

	//printf("sfsfs%d\n",this->length );
}
Doc::~Doc(){

}
Dataset::Dataset(string directoryname,int K,string flag){
	FILE* stopwords = fopen("stopwords.txt","r");
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, K);
	if(!stopwords){
		
		return ;
	}
	//printf("@@\n");
	// Init the stop vector.
	char bufferstop[MAXINPUTONELINE];
	fgets(bufferstop,MAXINPUTONELINE-1,stopwords);
	this->stop = ParsetoSingleword(bufferstop,"' '\r\t\n");
	fclose(stopwords);

	int file_count = 0;
	DIR * dirp;
	struct dirent * entry;
	dirp = opendir(directoryname.c_str()); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) {
	    if (entry->d_type == DT_REG) { /* If the entry is a regular file */
	         file_count++;			
	    }
	}
	closedir(dirp);

	this->M = file_count;
	this->docs = new Doc*[this->M];
	this->V=0;

	int i = 0;
	dirp = opendir(directoryname.c_str()); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL) {
	    if (entry->d_type == DT_REG) { /* If the entry is a regular file */
	         //file_count++;
	         //cout<<entry->d_name<<endl;
			string filename = directoryname+entry->d_name;
			//printf("%s\n",filename.c_str() );
			FILE* input = fopen(filename.c_str(),"r");
			if(!input){
				return ;
			}
			//printf("%d\n",i );
			char buffer[MAXINPUTONELINE];
			string oneline;
			vector<string> vec;
			while(fgets(buffer,MAXINPUTONELINE-1,input)){
				oneline+=buffer;
			}

			//printf("%s\n",oneline.c_str() );

			this->docs[i]=new Doc(oneline,"\t\r\n' '",this->stop);
			// two maps are instantiated here.
			for (int j = 0; j < this->docs[i]->length; ++j)
			{
				//printf("%d\n",j );
				int outinittopic = -1;
				if(wordtoid.find(this->docs[i]->vec[j].c_str()) == wordtoid.end()){
					int id = this->V;
					wordtoid.insert(pair<string,int>(this->docs[i]->vec[j],id));
					idtoword.insert(pair<int,string>(id,this->docs[i]->vec[j]));
					// we just assign 0 to all the distinct words for the moment.
					//wordtotopic.insert(pair<string,int>(this->docs[i]->vec[j],0));
					// we randomly assign topic 0...K-1 to each word in each document.
					// potential bug?? the topic is associated to distinct word or a,b? wordtotopic should be a,b word, not distinct word
					//time_t  tt;
					//srand((unsigned) time(&tt));
						(this->V)++;
					}
					Key  p (i,j);
					//int inittopic = (int)((double)rand()/RAND_MAX*K);



   					// printf("************************%d\n",K );
    				
  	
         
    

					int inittopic = (int)dis(gen) ;
							//printf("%d\n",inittopic );
					outinittopic = inittopic;
					//printf("%d ",inittopic);
					//printf("&&&&&&&&&&&%d\n",(int)((double)random()/RAND_MAX*K) );
					wordtotopic.insert(pair<Key,int>(p,inittopic));
					//printf("%d\n",wordtotopic[p] );
					//delete p;
					
					
					
				
					
				// // The following three lines hugely improve the initthreemat performance.
				 	int id = this->wordtoid[this->docs[i]->vec[j]];
				 	Key p22 (id,outinittopic);
				 	if(this->part2.find(p22)==this->part2.end()){
				 		this->part2.insert(pair<Key,int>(p22,1));
				 	}
				 	else{
				 		//this->part2.insert(pair<Key,int>(p22,this->part2[p22]+1));
				 		this->part2[p22] = this->part2[p22]+1;
				 	}
			}
		//	printf("sdfsdffsfsfs--\n");
			//printf("\n");
			fclose(input);
			i++;
	    }
	    
	    //printf("ff%d\n",i );
	}
	closedir(dirp);

	//cout<<file_count<<endl;
}
Dataset::Dataset(string filename,int K){
	std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0, K);
	FILE* input = fopen(filename.c_str(),"r");
	FILE* stopwords = fopen("stopwords.txt","r");
	if(!input||!stopwords){
		return ;
	}
	// Init the stop vector.
	char bufferstop[MAXINPUTONELINE];
	fgets(bufferstop,MAXINPUTONELINE-1,stopwords);

	this->stop = ParsetoSingleword(bufferstop,"' '\r\t\n");
	// Init the docs**, to maps.
	char buffer[MAXINPUTONELINE];
	string oneline;
	fgets(buffer,MAXINPUTONELINE-1,input);
	this->M = atoi(buffer);
	if(this->M <= 0){
		return ;
	}
	this->docs = new Doc*[this->M];
	this->V=0;
	for (int i = 0; i < this->M; ++i)
	{
		//printf("%d\n",i );
		vector<string> vec;
		fgets(buffer,MAXINPUTONELINE-1,input);
		oneline = buffer;
		//printf("%s\n\n",oneline.c_str() );
		this->docs[i]=new Doc(oneline,"\t\r\n' '",this->stop);
		// two maps are instantiated here.
		for (int j = 0; j < this->docs[i]->length; ++j)
		{
			int outinittopic = -1;
			if(wordtoid.find(this->docs[i]->vec[j].c_str()) == wordtoid.end()){
				int id = this->V;
				wordtoid.insert(pair<string,int>(this->docs[i]->vec[j],id));
				idtoword.insert(pair<int,string>(id,this->docs[i]->vec[j]));
				// we just assign 0 to all the distinct words for the moment.
				//wordtotopic.insert(pair<string,int>(this->docs[i]->vec[j],0));
				// we randomly assign topic 0...K-1 to each word in each document.
				// potential bug?? the topic is associated to distinct word or a,b? wordtotopic should be a,b word, not distinct word				
					(this->V)++;


				}
				Key  p (i,j);

   				// printf("************************%d\n",K );
				int inittopic = (int)dis(gen) ;//不收敛！！说明吉布斯采样有问题！
				//int inittopic = (int)((double)random()/RAND_MAX*K); //收敛
				//printf("%d, ", inittopic);
				outinittopic = inittopic;
				//printf("%d ",inittopic);
				//printf("&&&&&&&&&&&%d\n",(int)((double)random()/RAND_MAX*K) );
				wordtotopic.insert(pair<Key,int>(p,inittopic));

			// // The following three lines hugely improve the initthreemat performance.
			 	
			 	int id = this->wordtoid[this->docs[i]->vec[j]];
			 	Key p22 (id,outinittopic);
			 	if(this->part2.find(p22)==this->part2.end()){
			 		this->part2.insert(pair<Key,int>(p22,1));
			 	}
			 	else{
			 		//this->part2.insert(pair<Key,int>(p22,this->part2[p22]+1));
			 		//printf("before%d\n",this->part2[p22]);
			 		this->part2[p22] = this->part2[p22]+1;
			 					 		//printf("after%d\n",this->part2[p22]);

			 	}
			 	//this->num_v_k[id][outinittopic]++;
		}
		//printf("\n");
	}
	
	// close file.
	fclose(input);
	fclose(stopwords);

	//map<int,string>::iterator it;

}

vector<string> Dataset::ParsetoSingleword(string str,string seperator){
	//I referred to https://github.com/mrquincle/gibbs-lda's code for this part.
	//Basically just chop each word off each time and push it back to the vector.
	vector<string> res;
	int start = str.find_first_not_of(seperator);
	while(start>=0&&start<str.length()){
		int end = str.find_first_of(seperator,start);
		if(end<0||end>str.length()){
			end = str.length();
		}
		res.push_back(str.substr(start,end-start));	
		start = str.find_first_not_of(seperator,end+1);
	}
	return res;
}

vector<string> Dataset::ParsetoSingleword(string str,string seperator,vector<string> vec){
	//I referred to https://github.com/mrquincle/gibbs-lda's code for this part.
	//Basically just chop each word off each time and push it back to the vector.
	//The third parameter is the stopword vector.
	vector<string> res;
	int start = str.find_first_not_of(seperator);

	while(start>=0&&start<str.length()){
		int end = str.find_first_of(seperator,start);
		if(end<0||end>str.length()){
			end = str.length();
		}
				

		string currentword = "";
		if(str.substr(end-1,1).compare(",")==0||str.substr(end-1,1).compare("?")==0||str.substr(end-1,1).compare(".")==0)
		{
			//printf("%s\n", str.substr(start,end-start).c_str());
			currentword = str.substr(start,end-start-1);
			//printf("%s\n", currentword.c_str());
		}
		else
		{
			currentword = str.substr(start,end-start);
		}
		if(!(std::find(vec.begin(), vec.end(), currentword) != vec.end())){
			res.push_back(currentword);
		}
		start = str.find_first_not_of(seperator,end+1);
	}
	return res;
}
Dataset::~Dataset(){
	for (int i = 0; i < M; ++i)
	{
		delete docs[i];	
	}
	delete docs;
}
