#include "SparseTableRMQ.h"
#include <iostream>
#include <cmath>
using namespace std;

//Helper function to create only the minimum number of collums
size_t  sizeOfCol(size_t size, size_t querySize);

//Refrance:
//Errichto Algorithms, (2022), Sparse Table & RMQ (Range Minimum Query) [video],
//YouTube, https://www.youtube.com/watch?v=0jWeUdxrGm4
SparseTableRMQ::SparseTableRMQ(const RMQEntry* elems, std::size_t numElems)
{
	Log = 0;
	//n = Number of elements
	n = numElems;

	b = new int[n];
	for(size_t i = 0; i < n; i++)
	{
		b[i] = elems[i].value();
	}

    Log = log2(n);

	 bin_log = new int [n + 1];
	//Populate bin_log
	bin_log[1] = 0;
    for(size_t i = 2; i <= n; i++)
    {
        bin_log[i] = bin_log[i / 2] + 1;
    }
	//Sparse table
	 a = new size_t* [Log + 1];
    int colSize = 0;
	//Make colums
    for(size_t i = 0; i <= Log; i++)
    {
			//Creates only the right amount of collums
			//Doesnt create extra spots in the array
			//You mentioned this was extra credit if we were able to impliment this
        colSize = sizeOfCol(n, pow(2, i));
        a[i] = new size_t[colSize];
    }

	//Initialize row 0 to o -> n-1
    for(size_t i = 0; i < n; i++)
    {
        a[0][i] = i;
    }

	//Sort the whole sparse table
    for(size_t i = 1; i <= Log; i++)
    {
        for(size_t j = 0; j + (1 << i) <= n; ++j)
        {
				if(b[a[i - 1][j]] < b[a[i - 1][j + (1 << (i - 1))]])
				{
					a[i][j] = a[i - 1][j];
				}
				else
				{
					a[i][j] = a[i - 1][j + (1 << (i - 1))];
				}
        }
    }
}

SparseTableRMQ::~SparseTableRMQ()
{
   for(size_t i = 0; i <= Log; i++)
   {
    	  delete[] a[i];
   }
   delete [] a;
	delete [] b;
	delete [] bin_log;
}

size_t SparseTableRMQ::rmq(size_t low, size_t high) const 
{
    high--;
    int length = high - low + 1;
    int k = bin_log[length];
 	 if(b[a[k][low]] < b[a[k][high - (1 << k) + 1]])
	 {
		return a[k][low];
	 }
	 else
	 {
		return a[k][high - (1 << k) + 1];
	 }
}

size_t  sizeOfCol(size_t size, size_t querySize)
{
    int sizeOfCol = 0;
     while(querySize != size)
    {
        sizeOfCol++;
        querySize++;
	}
    return sizeOfCol + 1;
}
