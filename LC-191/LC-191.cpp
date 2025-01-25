#include <iostream>

using namespace std;

int hammingWeight(int n) 
{
    int count = 0;

    for (int i=0; i<31; i++)
    {
        // If bit-0 == 1
        if (n & 1 == 1)
            count++;
        
        n = n >> 1;
    }

    return count;
}

int main()
{
    int count = hammingWeight(3);
    cout << count;
    return 1;
}