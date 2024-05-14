#include "PrecomputedRMQ.h"
#include <iostream>
using namespace std;

PrecomputedRMQ::PrecomputedRMQ(const RMQEntry* elems, size_t numElems)
{
	//Make the 2d array
	size = numElems;
	a = new size_t*[numElems];
	for(size_t i = 0; i < numElems; i++)
	{
		a[i] = new size_t[numElems];
	}

	//for(size_t i = 0; i < numElems; i++)
	//{
//		a[i][i] = i;
//	}

	 	//size_t tempc = 0;
    	for(size_t i = 0; i < numElems; i++)
    	{
         	  //tempc = c;
   	        for(size_t j = i; j < numElems; j++)
   	        {
					 if(j == i)
						{
							a[i][j] = i;
						}
                else if(elems[j].value() < elems[a[i][j - 1]].value())
                {
                    a[i][j] = j;
                }
                else
                {
                    a[i][j] = a[i][j - 1];
                }
     	    }
   	}
}

PrecomputedRMQ::~PrecomputedRMQ() {
		for(size_t i = 0; i < size; i++)
		{

			delete [] a[i];
		}
	delete [] a;
}

size_t PrecomputedRMQ::rmq(size_t low, size_t high) const {
	size_t index = 0;
    if(size == 1)
    {
        return 0;
    }
    index = a[low][--high];
   return index;
}
