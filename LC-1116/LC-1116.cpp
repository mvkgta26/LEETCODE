/*
	Termination:
		// Zero thread will be the first thread to run when curr_num > n. All others wait at that point.
		// Once the zero thread terminates, it wakes up all the other threads, who all go on to execute their termination code 
*/


#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std;

class ZeroEvenOdd 
{
	private:
		int n;
	
	public:
		condition_variable cv;
		mutex m;
		int curr_num = 1; 
		int zero_state=1;	// If 1, print 0, otherwise, dont
		
	
		ZeroEvenOdd(int n) 
		{
			this->n = n;
		}
	
		// printNumber(x) outputs "x", where x is an integer.
		void zero(function<void(int)> printNumber) 
		{
			// Keep looping till curr_num > n
			while(1)
			{
				unique_lock<mutex> lock (m);
				
				// zero thread will be the first thread to run when curr_num > n. All others wait at that point first.
					// Once the zero thread terminates, it wakes up all the other threads, who all go on to execute their termination code 
				// while ( curr_num <= n && zero_state == 0 )
				while ( zero_state == 0 )
				{
					cv.wait(lock);	
				}
				
				// Termination: Terminate when all n is done
				if (curr_num > n)	
				{
					cv.notify_all();
					return;
				};
				
				printNumber(0);
				
				zero_state = 0;
				
				cv.notify_all();
				lock.unlock();
			}
		}
	
		void even(function<void(int)> printNumber) 
		{
			while (1)
			{
				unique_lock<mutex> lock (m);
				
				// curr_num <= n : Dont sleep if finished guard. If it sleeps now, the zero thread will not raise a signal because it itself would be sleeping. It will keep sleeping indefinitely.
				while ( curr_num <= n && (zero_state == 1 || curr_num % 2 != 0) )
				{
					cv.wait(lock);
				}
				
				// Termination: Terminate when all n is done, signl other threads so that they wake up and terminate
				if (curr_num > n)	
				{
					// cv.notify_all();		// Not neeed, the even and odd threads both get woken by zero thread that runs first when curr_num > n
					return;
				}
				
				printNumber(curr_num);
				curr_num++;
				zero_state = 1;
				
				cv.notify_all();
				lock.unlock();
			}
			
		}
	
		void odd(function<void(int)> printNumber) 
		{
			while (1)
			{
				unique_lock<mutex> lock (m);
				
				// curr_num <= n : Dont sleep if finished guard. If it sleeps now, the zero thread will not raise a signal because it itself would be sleeping. It will keep sleeping indefinitely.
				// Wait if current number is not odd
				while ( curr_num <= n && ( zero_state == 1 || curr_num % 2 != 1 ) )
				{
					cv.wait(lock);
				}
				
				// Termination: Terminate when all n is done
				if (curr_num > n)	
				{
					// cv.notify_all();		// Not neeed, the even and odd threads both get woken by zero thread that runs first when curr_num > n
					return;
				}
				
				printNumber(curr_num);
				curr_num++;
				zero_state = 1;
				
				cv.notify_all();
				lock.unlock();
			}
		}
};