#include <vector>


using namespace std;




class CircularBuffer
{
	
private:
	vector<int> buffer;
	int head = 0;
	int tail = 0;
	int full = 0;
	int N;
	
public:
	CircularBuffer(int capacity)
	{
		N = capacity;
		buffer.resize(N);
	}
	
	bool push(int val)
	{
		if (full == N)
		{
			return false;
		}
		
		buffer[tail] = val;
		tail = (tail + 1) % N;
		full++;
		
		return true;
	}
	
	bool pop(int& val)
	{
		if (full == 0)
		{
			return false;
		}
		
		val = buffer[head];
		head = (head + 1) % N;
		full--;
		
		return true;
	}
};