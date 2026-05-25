

// class frame
// {	
// public:
// 	int a = 2;
	
// 	frame()
// 	{
// 		1;
// 	}
	
// 	virtual int printer()
// 	{
// 		return a;
// 	}
	
// 	virtual ~frame()
// 	{
// 		cout << "Virtual destructor \n";
// 	}
// };


// class childFrame : public frame
// {
// public:
// 	int b = 4;
	
// 	childFrame()
// 	{
// 		1;
// 	}
	
// 	int printer() override
// 	{
// 		return b;
// 	}
	
// 	~childFrame()
// 	{
// 		cout << "Childframe destructor \n";
// 	}
// };


// int main()
// {
	
// 	{
// 		frame* fr1 = new frame();
// 		frame* fr2 = new childFrame();
		
// 		fr1->printer();
// 		fr2->printer();
		
// 		delete fr1;
// 		delete fr2;
// 	}
	
// 	return 0;
// }