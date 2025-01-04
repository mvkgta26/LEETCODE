#include <stdio.h>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

int main()
{
    vector<int> arr = {1,2,3,4,5,6};
    vector<int> subarr(arr.begin()+1, arr.begin()+4);

    for (int i=0; i<subarr.size(); i++)
    {
        cout << subarr[i] << " ";
    }

    return 0;
}