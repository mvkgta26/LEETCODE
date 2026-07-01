#include <functional>
#include <mutex>

using namespace std;

class TrafficLight 
{
  private:
  	char greenRoad;
	mutex m;
	
  public:
	TrafficLight() 
	{
		greenRoad = 'A';
	}

	void carArrived(
		int carId,           // ID of the car
		int roadId,          // ID of the road the car travels on. Can be 1 (road A) or 2 (road B)
		int direction,       // Direction of the car
		function<void()> turnGreen,  // Use turnGreen() to turn light to green on current road
		function<void()> crossCar    // Use crossCar() to make car cross the intersection
	) 
	{
		unique_lock<mutex> lock(m);
		
		// Current car is in Road A
		if ( roadId == 1 )
		{
			if (greenRoad == 'B')
			{
				turnGreen();
				greenRoad = 'A';
			}
			
			crossCar();
		}
		
		// Current car is in Road B
		else if ( roadId == 2 )
		{
			if (greenRoad == 'A')
			{
				turnGreen();
				greenRoad = 'B';
			}
			
			crossCar();
		}
		
		lock.unlock();
	}
};
