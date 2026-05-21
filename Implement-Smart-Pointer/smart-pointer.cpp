#include<iostream>
#include <utility>

using namespace std;


class UniquePtr
{
private:
	int* n;	

public:
	UniquePtr(int num)
	{
		this->n = new int(num);
	}
	
	// Overload: Return reference to n
	int& operator *()
	{
		return *n;
	}
	
	// Ending const: Promises that the function wont modify the state of the current UniquePtr object. This is needed to allow * operator to be called on const UniquePtr objects. WIHTOUT THIS, there will be a COMPILE ERROR, when we try to apply * on const object
	// Starting const: Promises that this function returns a read-only access to the lvalue *n. This is needed to ensure that the function returns a read-only reference of lvalue *n. NOT DOING THIS CONST WILL NOT RAISE COMPILE ERROR IN ITSELF, but it will be wrong for the API, because you will give write access to the value in the const object.
	const int& operator *() const
	{
		return *n;
	}
	
	// Copy constructor and copy assignment
	// Use const for input, because it promises that other will not be modified. This allows const UniquePtr objects to be passed as input to copy.
	// Without the const in the input, the compiler will raise an error if you try to copy from const object
	UniquePtr(const UniquePtr &other)
	{
		this->n = new int (*other);
	}
	
	UniquePtr& operator = (const UniquePtr& other)
	{
		if (this == &other)
		{
			return *this;
		}
		
		delete n;
		this->n = new int (*other);
		
		return *this;	// this is a UniquePtr* type. *this will be a UniquePtr type. The return UniquePtr object will be converted to UniquePtr& reference
	}
	
	// Move constructor and move assignment
	UniquePtr(UniquePtr&& other)
	{
		this->n = other.n;
		other.n = nullptr;
	}
	
	UniquePtr& operator = (UniquePtr&& other)
	{
		if (this == &other)
		{
			return *this;
		}
		
		delete n;	// Clear up the space allocated in the old pointer
		
		// Steal pointer
		this->n = other.n;
		other.n = nullptr;
		
		return *this;
	}
	
	
	// RAII destructor
	~UniquePtr()
	{
		delete n;
	}
};



int main()
{
	UniquePtr i(3);
	UniquePtr a = i;	// test copy constructor
	UniquePtr b(0);
	b = i;				// test copy assignment
	
	cout << *a << endl;
	cout << *b << endl;
	
	UniquePtr c = move(a);		// test move constructor
	UniquePtr d(0);
	d = move(b);				// test move assignment
	
	cout << *c << endl;
	cout << *d << endl;

	return 0;
}
