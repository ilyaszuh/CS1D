#include "LinearProbingHashTable.h"
#include <iostream>
using namespace std;

LinearProbingHashTable::LinearProbingHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family)
    : function(family->get()), table(numBuckets, -1) 
{
}

LinearProbingHashTable::~LinearProbingHashTable() {}

void LinearProbingHashTable::insert(int data)
{
    size_t index = function(data) % table.size();

    while (table[index] != -1 && table[index] != data)
    {
        index = (index + 1) % table.size();
    }

    if (table[index] == -1)
    {
        table[index] = data;
    }
}

bool LinearProbingHashTable::contains(int data) const
{
    size_t val = function(data);
    size_t index = val % table.size();

    while (table[index] != -1)
    {
        if (table[index] == data)
        {
            return true;
        }
        index = (index + 1) % table.size();
    }

    return false;
}

void LinearProbingHashTable::remove(int data)
{
    size_t index = function(data) % table.size();

    while (table[index] != -1)
    {
        if (table[index] == data)
        {
            table[index] = -1;

            size_t nextIndex = (index + 1) % table.size();
            while (table[nextIndex] != -1)
            {
                int displaced = table[nextIndex];
                table[nextIndex] = -1;
                insert(displaced); 
                nextIndex = (nextIndex + 1) % table.size();
            }

            return;
        }
        index = (index + 1) % table.size();
    }
}
