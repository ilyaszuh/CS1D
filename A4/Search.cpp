#include "Search.h"
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

//Make two functions to search each half

size_t lower_search(const string& pattern, const string& text, const vector<size_t>& sa)
{
	size_t low = 0, high = sa.size() - 1;
    while (low < high)
	 {
    	size_t mid = low + (high - low) / 2;
    		int cmp = text.compare(sa[mid], pattern.length(), pattern);
   	 	if (cmp < 0)
    		    low = mid + 1;
    		else
    		    high = mid - 1;
		}
    return low;
}

size_t upper_search(const string& pattern, const string& text, const vector<size_t>& sa)
{
	size_t low = 0, high = sa.size() - 1;
    while (low < high)
	 {
    	size_t mid = low + (high - low) / 2;

    		int cmp = text.compare(sa[mid], pattern.length(), pattern);

    		if (cmp > 0)
   		     high = mid - 1;
    		else
    		    low = mid + 1;
		}
    return low;
}


vector<size_t> searchFor(const string& pattern,
                         const string& text,
                         const SuffixArray& suffixArr)
{
	vector<size_t> result;

	if (pattern.empty()) {
      for(size_t i = 0; i < suffixArr.size(); i++) {
      	result.push_back(suffixArr[i]);
        }
   	return result;
	}


	 size_t lower_bound = lower_search(pattern, text, suffixArr);
    size_t upper_bound = upper_search(pattern, text, suffixArr);



      for(size_t i = lower_bound; i <= upper_bound; i++)
		{
			if(pattern.empty() && suffixArr[i] == text.size())
			{
				result.push_back(suffixArr[i]);
			}
			else
			{
      	   	if (text.compare(suffixArr[i], pattern.length(), pattern) == 0) {
   	      	    result.push_back(suffixArr[i]);
				}
			}
    }


  return result;
}
