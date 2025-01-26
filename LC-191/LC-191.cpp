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

/*
Proof for why n & (n-1) will set the least significant 1 in the bit representation to 0, and leave everything else untouched
When you do n='b31 b30 .... bk=1 0 ... 0 0' - 1 :
    All the bits lower than bk are 0's, bk is the first 1
    When you subtract by 1, all the 0's before bk will become 1, and bk will become 0 (since it is the first 1, it will be carried to the right)
    Now the number n-1 is: b31 b30 ..... bk=0 1 1 ...1
    Hence, n & (n-1) : b31 b30 .... bk=0 0 0 .. 0, which is just n but with the least significant 1 turned to 0
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