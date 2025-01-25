// Algorithm: Use a max heap and maintain its size of k elements

#include <queue>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;


// Function to calculate the square of the distance and return it.
// You dont actually need to do sqrt to compare distances. You can just compare the squares
double calcDist(vector<int> coordinates)
{
    int x = coordinates[0];
    int y = coordinates[1];

    double sum = x*x + y*y;
    // double dist = sum;

    return dist;
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int k) 
{

    // Create a priority queue that sorts the vector<> based on the int key value
    // Priority queue syntax: std::priority_queue<ElementType, ContainerType, ComparatorType> pq;
    // Here the first input: Element Type: {int, vector<>} pair
    // The second input : vector< pair<int, vector<int>> > mentions that the container used to implement the priority queue is a vector which holds our pairs
    // There is no third input here, because the default is taken as less<>, which will make the pqueue as a maxheap
    priority_queue < pair< double, vector<int> >, 
                    vector< pair<double, vector<int>> >,
                    less<>
                    > 
                    pque;


    vector<vector<int>> outputs;

    for (int i=0; i<points.size(); i++)
    {
        vector<int> coordinate = points[i];

        double dist = calcDist(coordinate);

        pque.push({dist, coordinate});
        
        // If there are more than k elements in the priority que, pop off the max element from the priority que
        if (pque.size() > k)
        {
            pque.pop();
        }
    }
    
    // Empty the values from the priority queue into a vector outputs[]
    while (!pque.empty())
    {
        pair<double, vector<int>> output = pque.top();
        outputs.push_back(output.second);
        pque.pop();
    }
    
    return outputs;
}

int main()
{   
    vector<vector<int>> points = {{1,3},{-2,2}};

    vector<vector<int>> outputs = kClosest(points, 1);

    for (int i=0; i<outputs.size(); i++)
    {
        cout << outputs[i][0] << " ";
        cout << outputs[i][1] << " ";
        cout << "\n";
    }


    return 1;
}
