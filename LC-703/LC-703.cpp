/*  
-----------------------------------------
Logic:
    Create a minHeap.
    In the minHeap, always maintain only the largest k elements among all the elements added so far.
        When inserting 'k+1'th element, push it into the minHeap and then pop the minHeap top.
        This way, the minHeap will maintain the k largest elements added so far.
    If we do this, the minHeap top will always have the kth largest element (which is the output)

Corner Case:
    The initialiser vector array could be smaller than 'k'.
    You will have to handle this case.
------------------------------------------
*/

#include <iostream>
#include <queue>

using namespace std;


class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> minHeap;    //We create these class member variables
    int k;


    KthLargest(int k, vector<int>& nums) 
    {
        this->k = k;

        for (int i=0; i<nums.size(); i++)
        {
            // After the first k elements are pushed to the minHeap,
            // check if the new element nums[i] is smaller than the stack top.
            // If so we can ignore this element, no need to push and then pop.
            // It will not affect the fact that the minHeap will have the k largest elements
            if ( (i >= k) && (nums[i] <= minHeap.top()) )
            {
                // Ignore
            }

            else
            {
                minHeap.push(nums[i]);

                // If we have pushed the 'k+1'th element in the minHeap, 
                // After pushing, remove the smallest character to make the minHeap size = k
                // At any point, the minHeap should just hold the largest k characters
                if (minHeap.size() > k)    // Actually, if (minHeap.size() == k+1)
                {
                    minHeap.pop();
                }
            }
        }
    }
    
    int add(int val) 
    {
        // If val is smaller/equal to the minHeap top (Smallest element in the current minHeap), then ignore val
        // This val does not affect the output: kth largest element
        if ( minHeap.size() == k && val <= minHeap.top() )
        {   
            // Ignore
        }

        // If val is > minHeap top, push val to the minHeap and pop the top
        // (Pop the smallest element in the heap after pushing val to the minHeap)
        // After the pop, the minHeap top will now have the kth largest element 
        else
        {
            minHeap.push(val);

            if (minHeap.size() > k)    // Actually, if (minHeap.size() == k+1)
            {
                minHeap.pop();
            }
        }

        return minHeap.top();
    }

};


int main()
{
    cout << "Hello World" << endl;
    return 0;
}

