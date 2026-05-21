#include <string>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <iostream>


using namespace std;

enum class VehicleType
{
	bike,
	car,
	truck	
};

enum class ParkingSpotType
{
	small,
	medium,
	large
};


// Represent each vehicle
class Vehicle
{
private:
	string license;
	
public:
	VehicleType type;
	
	Vehicle(string license, VehicleType type)
	{
		this->license = license;
		this->type = type;
	}
	
};


// Represent each parking spot
class ParkingSpot
{
private:
	int spotNumber;
	
public:
	ParkingSpotType type;
	Vehicle* vehicle;	// The vehicle in the parking spot
	bool available;
	
	
	ParkingSpot(int spotNum, ParkingSpotType type)
	{
		this->spotNumber = spotNum;
		this->type = type;
	}
	
	bool canFit(Vehicle* v)
	{
		if( v->type == VehicleType::truck && ( type == ParkingSpotType::medium || type == ParkingSpotType::small) )
		{
			return false;
		}
		
		return true;
	}
	
	void ParkInSpot()
	{
		this->available = 0;
	}
	
	void UnParkInSpot()
	{
		this->available = 1;
	}
};


class Ticket
{
public:
	int ticketNum;
	Vehicle* v;
	ParkingSpot* spot;
	time_t startTime;
	time_t endTime;
	
	Ticket(Vehicle* v, ParkingSpot* p)
	{
		this->v = v;
		this->spot = p;
		this->startTime = time(nullptr);
	}
	
	void closeTicket()
	{
		this->endTime = time(nullptr);
	}
	
	int calculateFee()
	{
		int fee = ( 100 * (this->endTime - this->startTime)/3600 );
		return fee;
	}
	
};


class ParkingLot
{
private:
	vector<ParkingSpot*> spots;
	unordered_map<int, Ticket*> ticketNumMap;
	int ticketNum = 0;
	

	
public:	
	void addSpot(ParkingSpot* spot)
	{
		spots.push_back(spot);
	}

	ParkingSpot* findFreeSpot(Vehicle* v)
	{
		for (int i=0; i<spots.size(); i++)
		{
			if ( spots[i]->canFit(v) && spots[i]->available )
			{
				return spots[i];
			}
		}
		
		return nullptr;
	}
	
	Ticket* ParkVehicle(Vehicle* v)
	{
		ParkingSpot* p = findFreeSpot(v);
		Ticket* t = new Ticket(v, p);
		ticketNumMap[ticketNum++] = t;
		p->ParkInSpot();
		
		return t;
	}
	
	void freeSpot(Ticket* t)
	{
		t->closeTicket();
		int fee = t->calculateFee();
		cout << "The fee is: " << fee << endl;
		t->spot->UnParkInSpot();
		ticketNumMap.erase(t->ticketNum);
		
		delete t;
	}
	
};


void main()
{
	ParkingLot* lot = new ParkingLot();
	
	lot->addSpot(new ParkingSpot(1, ParkingSpotType::small));
	lot->addSpot(new ParkingSpot(2, ParkingSpotType::medium));
	lot->addSpot(new ParkingSpot(3, ParkingSpotType::large));
	
	Vehicle* car1 = new Vehicle("A123", VehicleType::car);
	
	Ticket* t = lot->ParkVehicle(car1);
	
	lot->freeSpot(t);
}

