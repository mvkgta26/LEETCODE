#include <functional>
#include <condition_variable>

using namespace std;

class FooBar 
{
	private:
		int n;
	
	public:
		mutex m;
		condition_variable cv;
		int state = 0;	// 0 = foo, 1 = bar
	
		FooBar(int n) 
		{
			this->n = n;
		}
	
		void foo(function<void()> printFoo) 
		{
			
			for (int i = 0; i < n; i++) 
			{
				unique_lock<mutex> lock(m);
				
				while (state != 0)
				{
					cv.wait(lock);
				}
				
				printFoo();
				
				state = 1;
				
				cv.notify_all();
				
				lock.unlock();
			}
	
		}
	
		void bar(function<void()> printBar) 
		{
			
			for (int i = 0; i < n; i++) 
			{
				unique_lock<mutex> lock(m);
				
				while (state != 1)
				{
					cv.wait(lock);
				}
				
				printBar();
				
				state = 0;
				
				cv.notify_all();
				
				lock.unlock();
			}
		}
};