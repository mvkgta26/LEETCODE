#include <vector>

using namespace std;


int lastStoneWeight(vector<int>& stones) 
{
    //priority_queue<int> maxHeap;
    //sort(stones.begin(), stones.end());
    int n = stones.size();

    int end = n-1;
    int newstone = 0;

    // 2 Edge Cases
    while (end != 0 && end != -1)
    {
        sort(stones.begin(), stones.end() - ( (n-1) - end) );  // Sort array till the current end

        // Get the max 2 stones 
        int max_1 = stones[end];
        int max_2 = stones[end-1];

        if (max_1 == max_2)
        {
            end = end - 2;
        }

        else
        {
            newstone = abs(max_2 - max_1);
            end = end - 1;
            stones[end] = newstone;
        }
        
    }

    // If no stone left
    if (end == -1)
        return 0;

    // One stone left
    return stones[0];
}