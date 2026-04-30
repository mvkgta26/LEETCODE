/*
    LeetCode 1188 - Design Bounded Blocking Queue
    Question:
    Implement a thread-safe bounded blocking queue with fixed capacity.
    APIs to implement:
    - BoundedBlockingQueue(int capacity)
    - void enqueue(int element): blocks if queue is full
    - int dequeue(): blocks if queue is empty
    - int size(): returns current number of elements
*/


/*
	Problem: Design Bounded Blocking Queue (Thread-Safe)
	
	Main Idea:
		Use a mutex for mutual exclusion and two condition variables:
		  - notFull:  producers wait here when queue is at capacity
		  - notEmpty: consumers wait here when queue is empty
		
		enqueue: wait if full, push, notify a consumer
		dequeue: wait if empty, pop, notify a producer
		size:    lock and return current size
*/

#include <queue>
#include <mutex>
#include <condition_variable>
#include <semaphore.h>

using namespace std;

class BoundedBlockingQueue 
{
	
private:
	std::queue<int> q;
	std::mutex mtx;
	sem_t full; 
	sem_t empty;
	
public:
	BoundedBlockingQueue(int capacity) 
	{		
		// The second input parameter (0) signifies that the semaphore is shared between threads of the same process. if it is 1, that means it is shared between different proceses. 
		// (We usually only concern with concurrency between threads)
		sem_init(&full, 0, 0);		
		sem_init(&empty, 0, capacity);
	}
	
	// Block if full, then push and notify consumer
	void enqueue(int element) 
	{
		sem_wait(&empty);
		unique_lock<mutex> lock(mtx);
		
		q.push(element);
		
		lock.unlock();
		sem_post(&full);
	}
	
	// Block if empty, then pop and notify producer
	int dequeue() 
	{
		sem_wait(&full);
		unique_lock<mutex> lock(mtx);
		
		int val = q.front(); q.pop();
		
		lock.unlock();
		sem_post(&empty);
		
		return val;
	}
	
	int size() 
	{
		unique_lock<mutex> lock(mtx);
		
		int size = q.size();
		
		lock.unlock();
		
		return size;
	}

	~BoundedBlockingQueue()
	{
		sem_destroy(&full);
		sem_destroy(&empty);
	}
};
