#include <iostream>

using namespace std;

template <typename T>
class smartPointer
{
private:
	T* p;
	
public:
	smartPointer(T num=0)
	{
		p = new T(num);
	}
	
	// Overload the * operator, return the value in the pointer p
	T& operator * ()
	{
		return *(this->p); 
	}
	
	// Copy constructor
	smartPointer(smartPointer& other)
	{
		p = new T(*(other));
	}
	
	// Copy assignment
	smartPointer& operator = (const smartPointer<T>& other)
	{
		if (this == &other)
		{
			return *this;
		}
		
		delete p;
		
		p = new T(*(other.p));
		
		return *this;
	}
	
	// Move constructor
	smartPointer(smartPointer&& other)
	{		
		p = other.p;
		other.p = nullptr;
	}
	
	// Move assignment
	smartPointer& operator = (smartPointer&& other)
	{
		if (this == &other)
		{
			return *this;
		}	
		
		delete p;
		
		p = other.p;
		other.p = nullptr;
		
		return *this;
	}
	
	~smartPointer()
	{
		delete p;
	}
};


int main()
{
	smartPointer<float> ptr(2.5);
	cout << *ptr << endl;
	
	// smartPointer ptr2(ptr);
	// cout << *ptr2 << endl;
	
	// smartPointer ptr3 = smartPointer();
	// ptr3 = ptr;
	// cout << *ptr3 << endl;
	
	// smartPointer ptr4 = move(ptr3);
	// cout << *ptr4 << endl;
	
	// smartPointer ptr5;
	// ptr5 = move(ptr4);
	
	
	return 0;
}