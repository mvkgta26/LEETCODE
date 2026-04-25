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
			while(1)
			{
				unique_lock<mutex> lock (m);
				
				while (  curr_num <= n && zero_state == 0 )
				{
					cv.wait(lock);	
				}
				
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
				
				while ( curr_num <= n && (zero_state == 1 || curr_num % 2 != 0) )
				{
					cv.wait(lock);
				}
				
				if (curr_num > n)	
				{
					cv.notify_all();
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
				
				// Wait if current number is not odd
				while ( curr_num <= n && ( zero_state == 1 || curr_num % 2 != 1 ) )
				{
					cv.wait(lock);
				}
				
				if (curr_num > n)	
				{
					cv.notify_all();
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