#include "SAIS.h"
#include "DC3.h"
#include <iostream>
#include <algorithm>
using namespace std;

bool compare(const vector<size_t>& text, size_t begin1, size_t end1, size_t begin2, size_t end2){
  if(end1 - begin1 != end2 - begin2){
    return false;
  }

  for (size_t i = begin1, j = begin2; i <= end1 && j <= end2; i++, j++) {
      if (text[i] != text[j]) {
          return false;
       }
   }

    return true;
}

bool islms(const vector<int>& lms, int num)
{
	for(size_t i = 0; i < lms.size(); i++)
	{
		if(num == lms[i])
		{
			return true;
		}
	}
	return false;
}

vector<vector<int>> initindex2d(vector<vector<int>> index2d, const vector<vector<int>>& index2dcopy)
{
	for(size_t i = 0; i < index2dcopy.size(); i++)
	{
		index2d[i][0] = index2dcopy[i][0];
		index2d[i][1] = index2dcopy[i][1];
	}
	return index2d;
}

vector<int> step2(vector<int> sa,
						vector<vector<int>> index2d,
						const vector<vector<int>>& index2dcopy,
						const vector<size_t>& text,
						vector<int>& lms,
						vector<char> ls)
{

	//Pass 1
	for(size_t i = lms.size() - 1; i >= 0 && i < lms.size(); i--)
	{
		if(lms[i] > 0)
		{
			sa[index2d[text[lms[i]]][1]] = lms[i];
			index2d[text[lms[i]]][1]--;
		}
	}

	cout << "After pass 1:\n";
	for(size_t i = 0; i < sa.size(); i++)
	{
		cout << sa[i] << ", ";
	}
	cout << endl;

	index2d = initindex2d(index2d, index2dcopy);

	//Pass 2
	for(size_t i = 0; i < sa.size(); i++)
	{
		if(ls[sa[i] - 1] == 'l' && (sa[i] - 1) > 0)
		{
			sa[index2d[text[sa[i]-1]][0]] = sa[i] - 1;
			index2d[text[sa[i] - 1]][0]++;
		}
	}

	cout << "After pass 2:\n";
	for(size_t i = 0; i < sa.size(); i++)
	{
		cout << sa[i] << ", ";
	}
	cout << endl;

	index2d = initindex2d(index2d, index2dcopy);

	//Pass 3
	for(size_t i = sa.size() - 1; i > 0; i--)
	{
		if(ls[sa[i] - 1] == 's')
		{
			sa[index2d[text[sa[i]-1]][1]] = sa[i] - 1;
			index2d[text[sa[i] - 1]][1]--;
		}
	}

	index2d = initindex2d(index2d, index2dcopy);

	cout << "After pass 3:\n";
	for(size_t i = 0; i < sa.size(); i++)
	{
		cout << sa[i] << ", ";
	}
	cout << endl;


	return sa;
}

SuffixArray sais(const vector<size_t>& text) {
//Need to also find number of buckts
//Make array initialized to 0
//Make it size of ascii table 128
//For to go through each elemend of the text
//Get the ascii value of each char, go to place in array and ++
//Make 2d array for head and tail pointers
	vector<int> bucketCount(27, 0);
	vector<char> ls(0, -1);
	vector<int> lms(text.size(), -1);
	vector<int> sa(text.size(), -1);
	vector<size_t> returnSa(text.size(), -1);
	size_t numBuckets = 0;
	int n = 0;
	int index = 0;

	cout << "Text string: \n";
	for(size_t i = 0; i < text.size(); i++)
	{
		cout << text[i] << ", ";
	}
	cout << endl;

	for(size_t i = 0; i < text.size(); i++)
	{
		n++;
	}
	ls.insert(ls.begin(), 's');

	for(int i = n - 1; i > 0; i--)
	{
		if(text[i - 1] < text[i])
		{
			ls.insert(ls.begin(), 's');
		}
		else if(text[i - 1] > text[i])
		{
			ls.insert(ls.begin(), 'l');
		}
		else
		{
			ls.insert(ls.begin(), ls.front());
		}
	}

	for(int i = 0; i < n; i++)
	{
		bucketCount[text[i]]++;
	}

	cout << "LS array:\n";
	for(int i = 0; i < n; i++)
	{
		cout << ls[i] << ", ";
	}
	cout << endl;


	for(int i = 0; i < n; i++)
	{
		if(ls[i - 1] == 'l' && ls[i] == 's' && i != 0)
		{
			sa[i] = i;
		}
	}

	index = 0;
	for(size_t i = 0; i < sa.size(); i++)
	{
		if(sa[i] >= 0)
		{
			lms[index] = sa[i];
			index++;
		}
	}
	lms.resize(index);

	for(size_t i = 0; i < sa.size(); i++)
	{
		sa[i] = 0;
	}

	cout << "LMS array:\n";
	for(size_t i = 0; i < lms.size(); i++)
	{
		cout << lms[i] << ", ";
	}
	cout << endl;

	index = 0;
	while(bucketCount[index] != 0)
	{
		numBuckets++;
		index++;
	}
	bucketCount.resize(numBuckets);

	cout << "Size of buckets:\n";
	for(size_t i = 0; i < bucketCount.size(); i++)
	{
		cout << bucketCount[i] << ", ";
	}
	cout << endl;

	cout << "Num buckets = " << numBuckets << endl;
	vector<vector<int>> index2d(numBuckets, vector<int>(2, 0));
	vector<vector<int>> index2dcopy(numBuckets, vector<int>(2, 0));

    for (size_t i = 0; i < numBuckets; i++) {
        if (i == 0) {
            index2dcopy[i][0] = 0;
        } else {
            index2dcopy[i][0] = index2dcopy[i - 1][1] + 1;
        }

        index2dcopy[i][1] = index2dcopy[i][0] + bucketCount[i] - 1;
    }

	index2d = initindex2d(index2d, index2dcopy);


	cout << "Index Array: \n";
	for(size_t i = 0; i < index2d.size(); i++)
	{
		cout << index2d[i][0] << ", " << index2d[i][1] << endl;
	}

	sa = step2(sa, index2d, index2dcopy, text, lms, ls);

	vector<int> lmsTails(text.size(), -1);

	for(size_t i = 0; i < lms.size(); i++)
	{
		lmsTails[lms[i]] = lms[i + 1];
	}
	lmsTails.back() = lms.back();

	cout << "Lms Tails\n";
	for(size_t i = 0; i < lmsTails.size(); i++)
		cout << lmsTails[i] << ", ";
	cout << endl;

	vector<int> lmsTracker;
	vector<int> reducedText(text.size(), -1);

	int count = 0;
	size_t lmsCount = 0;

	lmsTracker.push_back(sa.front());
	reducedText[sa.front()] = count;
	count++;

	for(size_t i = 1; i < text.size(); i++)
	{
		if(ls[sa[i]] == 's' && ls[sa[i] - 1] == 'l')
		{
			lmsTracker.push_back(sa[i]);
			lmsCount++;

      	size_t begin1 = sa[i];
      	size_t end1 = lmsTails[sa[i]];
      	size_t begin2 = lmsTracker[lmsCount - 1];
      	size_t end2 = lmsTails[begin2];

	      bool result = compare(text, begin1, end1, begin2, end2);

			if(!result)
			{
				reducedText[sa[i]] = count;
				count++;
			}
			else
			{
				count--;
				reducedText[sa[i]] = count;
			}
		}
	}

	for(size_t i = 0; i < reducedText.size(); i++)
	{
		int j = 0;
		while(text[sa[i] + j] == text[sa[i + 1] + j])
		{
			if(sa[i] + j == sa[i + i])
			{
				reducedText[i] = reducedText[i + 1];
			}
			j++;
		}
	}

	vector<size_t> lmsdup(reducedText.size());
	index = 0;
	for(size_t i = 0; i < reducedText.size(); i++)
	{
		if(reducedText[i] != -1)
		{
			lmsdup[index] = reducedText[i];
			index++;
		}
	}
	lmsdup.resize(index);

	cout << "Reduced Text\n";
	for(size_t i = 0; i < lmsdup.size(); i++)
	{
			cout << lmsdup[i] << ", ";
	}

	cout << endl;

	const auto dc3Text = dc3(lmsdup);

	cout << "After dc3\n";
	for(size_t i = 0; i < dc3Text.size(); i++)
	{
		cout << dc3Text[i] << ", ";
	}
	cout << endl;

	cout << "lms before change\n";
	for(size_t i = 0; i < lms.size(); i++)
	{
			cout << lms[i] << ", ";
	}

	cout << endl;

	cout << "lmsdup size = " << lmsdup.size() << endl;
	cout << "lms size = " << lms.size() << endl;

	for(size_t i = 0; i < dc3Text.size(); i++)
	{
		lmsdup[i] = lms[dc3Text[i]];
	}

	for(size_t i = 0; i < lms.size(); i++)
	{
		lms[i] = lmsdup[i];
	}


	cout << "Re-ordered lms after order\n";
	for(size_t i = 0; i < lms.size(); i++)
	{
			cout << lms[i] << ", ";
	}

	cout << endl;

	for(size_t i = 0; i < sa.size(); i++)
	{
		sa[i] = 0;
	}

	cout << "Index Array: \n";
	for(size_t i = 0; i < index2d.size(); i++)
	{
		cout << index2d[i][0] << ", " << index2d[i][1] << endl;
	}


	sa = step2(sa, index2d, index2dcopy, text, lms, ls);

	for(size_t i = 0; i < sa.size(); i++)
		returnSa[i] = sa[i];

  return returnSa;
}





