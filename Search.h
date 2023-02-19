//
//  Search.h
//

#pragma once

#include <climits>
#include <string>

using namespace std;



const int VALUE_NOT_FOUND = INT_MAX;



int linearSearch (const string data_in[],
                  int count_in,
                  const string& value_in);
int unsortedFindSmallest (const string data_in[],
                          int count_in);
int unsortedFindLargest (const string data_in[],
                         int count_in);

void mySort (string data_in[],
             int count_in);

bool isSorted (const string data_in[],
               int count_in);
int sortedFindSmallest (const string data_in[],
                        int count_in);
int sortedFindLargest (const string data_in[],
                       int count_in);
int binarySearch (const string data_in[],
                  int count_in,
                  const string& value_in);
int binarySearchFirst (const string data_in[],
                       int count_in,
                       const string& value_in);
