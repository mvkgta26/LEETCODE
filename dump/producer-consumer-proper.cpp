#include <iostream>
#include <algorithm>
#include <semaphore.h>
#include <mutex>


using namespace std;




class boundedBuffer
{
private:
	int n;
	vector<int> buffer;
	int write_ptr;
	int read_ptr;
	sem_t full;
	sem_t empty;
	mutex m;
	
public:
	boundedBuffer(int n)
	{
		this->n = n;
		buffer = vector<int>(n, 0);
		write_ptr = 0;
		read_ptr = 0;
		
		sem_init(&full, 0, 0);
		sem_init(&empty, 0, n);
	}
	
	void put(int num)
	{
		sem_wait(&empty);
		unique_lock<mutex> lock(m);
		
		buffer[write_ptr] = num;
		write_ptr = (write_ptr+1) % n;
		
		lock.unlock();
		sem_post(&full);
	}
	
	void get(int& out)
	{
		sem_wait(&full);
		unique_lock<mutex> lock(m);
		
		out = buffer[read_ptr];
		read_ptr = (read_ptr + 1) % n;
		
		lock.unlock();
		sem_post(&empty);
	}
	
	
	~boundedBuffer()
	{
		sem_destroy(&full);
		sem_destroy(&empty);
	}
	
};