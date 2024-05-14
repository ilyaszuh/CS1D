#include "CuckooHashTable.h"
#include <iostream>
using namespace std;

/**
 * Since cuckoo hashing requires two tables, you should create two tables
 * of size numBuckets / 2. Because our testing harness attempts to exercise
 * a number of different load factors, you should not change the number of
 * buckets once the hash table has initially be created.
 */
CuckooHashTable::CuckooHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family)
{
    function = family->get();
    function2 = family->get();
    t1.resize(numBuckets / 2 , -1);
    t2.resize(numBuckets / 2 , -1);
    MAX_ITERATIONS = numBuckets;
}

CuckooHashTable::~CuckooHashTable() {}

void CuckooHashTable::insert(int data)
{
    size_t h1 = function(data) % t1.size();
    size_t h2 = function2(data) % t2.size();

    if(contains(data))
    {
        return;
    }

    for(int i = 0; i < MAX_ITERATIONS; i++)
    {
        if(t1[h1] == -1)
        {
            t1[h1] = data;
            return;
        }

        if(t2[h2] == -1)
        {
            t2[h2] = data;
            return;
        }

        int temp = t1[h1];
        t1[h1] = data;
        data = temp;
        h2 = function2(data) % t2.size();

        temp = t2[h2];
        t2[h2] = data;
        data = temp;
        h1 = function(data) % t1.size();
    }

}

bool CuckooHashTable::contains(int data) const
{
    size_t h1 = function(data) % t1.size();
    size_t h2 = function2(data) % t2.size();

    return (t1[h1] == data || t2[h2] == data);
}

void CuckooHashTable::remove(int data)
{

    size_t h1 = function(data) % t1.size();
    size_t h2 = function2(data) % t2.size();

    if(t1[h1] == data)
    {
        t1[h1] = -1;
    }
    else if(t2[h2] == data)
    {
        t2[h2] = -1;
    }
}

