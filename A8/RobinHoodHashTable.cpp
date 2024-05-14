#include "RobinHoodHashTable.h"
#include <iostream>

RobinHoodHashTable::RobinHoodHashTable(size_t numBuckets, std::shared_ptr<HashFamily> family)
{
    function = family->get();
    table.resize(numBuckets);
    for (size_t i = 0; i < table.size(); i++)
    {
        table[i].data = -1;
        table[i].offset = 0;
    }
}

RobinHoodHashTable::~RobinHoodHashTable() {}

void RobinHoodHashTable::insert(int data)
{
    int index = function(data) % table.size();
    size_t offset = 0;
    if (contains(data))
    {
        return;
    }

    while(true)
    {
        if(table[index].data == -1)
        {
            table[index].data = data;
            table[index].offset = offset;
            return;
        }
        else if(table[index].offset < offset)
        {
            swap(table[index].offset, offset);
            swap(table[index].data, data);
        }
        offset++;
        index = (index + 1) % table.size();
    }
}

bool RobinHoodHashTable::contains(int key) const
{
    size_t index = function(key) % table.size();
    size_t offset = 0;

    while (true)
    {
        if (table[index].data == key)
        {
            return true;
        }
        if (table[index].data == -1 && table[index].offset == 0)
        {
            return false;
        }
        index = (index + 1) % table.size();
        offset++;
        if (offset >= table.size())
        {
            return false;
        }
    }
}

void RobinHoodHashTable::remove(int key)
{
    size_t index = function(key) % table.size();
    size_t offset = 0;

    while (table[index].data != -1 && offset <= table[index].offset)
    {
        if (table[index].data == key)
        {
            size_t nextIndex = (index + 1) % table.size();
            while (table[nextIndex].data != -1 && table[nextIndex].offset > 0)
            {
                table[index] = table[nextIndex];
                index = nextIndex;
                nextIndex = (index + 1) % table.size();
            }
            table[index].data = -1;
            table[index].offset = 0;
            return;
        }
        index = (index + 1) % table.size();
        offset++;
    }
}

