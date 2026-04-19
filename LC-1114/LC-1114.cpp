#include <condition_variable>
#include <functional>
#include <mutex>

using namespace std;

class Foo {
  private:
	int counter;
	mutex m;
	condition_variable cv;

  public:
	Foo() : counter(1) {
	}

	void first(function<void()> printFirst) 
	{
	  unique_lock<mutex> lock(m);
	  
	  cv.wait(lock, [this] { return counter == 1; });

	  // printFirst() outputs "first". Do not change or remove this line.
	  printFirst();

	  ++counter;
	  cv.notify_all();
	  
	  lock.unlock();
	}

	void second(function<void()> printSecond) {
	  unique_lock<mutex> lock(m);
	  
	  cv.wait(lock, [this] { return counter == 2; });

	  // printSecond() outputs "second". Do not change or remove this line.
	  printSecond();

	  ++counter;
	  cv.notify_all();
	  
	  lock.unlock();
	}

	void third(function<void()> printThird) 
	{
	  unique_lock<mutex> lock(m);
	 
	  cv.wait(lock, [this] { return counter == 3; });
	  // printThird() outputs "third". Do not change or remove this line.
	  printThird();

	  ++counter;
	  cv.notify_all();
	  
	  lock.unlock();
	}
};
