#include <iostream>

using namespace std;

/*
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
*/


int hammingWeight(int n) 
{
    int count = 0;

    while( n!= 0 )
    {
        count++;
        n = n & (n-1);   // n & (n-1) will set the least significant 1 to 0, leaving all other bits untouched
        // n will become 0 when the last 1 in the number is set to 0
    }

    return count;
}

int main()
{
    int count = hammingWeight(3);
    cout << count;
    return 1;
}