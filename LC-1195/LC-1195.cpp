#include <iostream>
#include <vector>
#include <condition_variable>
#include <mutex>

using namespace std;

class FizzBuzz
{
	private:
		int n; 
		int i_state;
		condition_variable cv;
		mutex m;
		
	public:
		FizzBuzz(int n)
		{
			this->n = n;
			this->i_state = 1;
		}

		// printFizz() outputs "fizz".
		void fizz(function<void()> printFizz)
		{
			unique_lock<mutex> lock(m);
			
			while ( i_state <=  n )
			{
				// Check state: The number is divisible by 3 but not 5
				while ( ( i_state <=n ) && !(this->i_state % 3 == 0 && this->i_state % 5 != 0) )
				{
					cv.wait(lock);
				}
				
				// Exit when the state exceeds n. It should execute code.
				if ( i_state > n )	
				{
					cv.notify_all();	// Not actually necessary
					lock.unlock();
					return;
				}
				
				printFizz();
				
				i_state++;
				cv.notify_all();
			}
		}

		// printBuzz() outputs "buzz".
		void buzz(function<void()> printBuzz)
		{
			unique_lock<mutex> lock(m);
			
			while ( i_state <=  n )
			{
				// Check state: The number is divisible by 5 but not 3
				while ( ( i_state <=n ) && !(this->i_state % 5 == 0 && this->i_state % 3 != 0) )
				{
					cv.wait(lock);
				}
				
				// Exit when the state exceeds n. It should execute code.
				if ( i_state > n )	
				{
					cv.notify_all();
					lock.unlock();
					return;
				}
				
				printBuzz();
				
				i_state++;
				cv.notify_all();
			}
		}

		// printFizzBuzz() outputs "fizzbuzz".
		void fizzbuzz(function<void()> printFizzBuzz)
		{
			unique_lock<mutex> lock(m);
			
			while ( i_state <=  n )
			{
				// Check state: The number is divisible by 3 and 5
				while ( ( i_state <=n ) && !(this->i_state % 5 == 0 && this->i_state % 3 == 0) )
				{
					cv.wait(lock);
				}
				
				// Exit when the state exceeds n. It should execute code.
				if ( i_state > n )	
				{
					cv.notify_all();
					lock.unlock();
					return;
				}
				
				printFizzBuzz();
				
				i_state++;
				cv.notify_all();
			}
			
			lock.unlock();
		}

		// printNumber(x) outputs "x", where x is an integer.
		void number(function<void(int)> printNumber)
		{
			unique_lock<mutex> lock(m);
			
			while ( i_state <=  n )
			{
				// Check state: The number is not divisible by 3 and 5
				while ( ( i_state <=n ) && !(this->i_state % 5 != 0 && this->i_state % 3 != 0) )
				{
					cv.wait(lock);
				}
				
				// Exit when the state exceeds n. It should execute code.
				if ( i_state > n )	
				{
					cv.notify_all();
					lock.unlock();
					return;
				}
				
				printNumber(i_state);
				
				i_state++;
				cv.notify_all();
			}
			
			lock.unlock();
		}
};