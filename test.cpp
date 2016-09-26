#include "LDA.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	LDA* lda = new LDA(argc,argv);
	lda->Gibbssampling();
	lda->CalculateThetanPhi();
	lda->Saveres();
}

