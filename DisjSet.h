#pragma once
class DisjSet
{
    int* rank;
    int* parent;
    int n;

    // Creates n single item sets
    void makeSet();

public:
    // Constructor to create and
    // initialize sets of n items
    DisjSet(int n);  
    // Finds set of given item x
    int find(int x);  
    // Do union of two sets represented
    // by x and y.
    void Union(int x, int y);
};