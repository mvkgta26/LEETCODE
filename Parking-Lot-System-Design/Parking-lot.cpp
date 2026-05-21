/*
	Design a Parking Lot System
	Problem

	Design a parking lot system that can support:

	Multiple floors
	Different vehicle types: bike, car, truck
	Different parking spot types: small, medium, large
	Entry gate and exit gate
	Ticket generation
	Parking fee calculation
	Spot availability tracking
	Requirements

	A vehicle enters the parking lot.

	The system should:

	Check if a suitable spot is available.
	Assign a spot.
	Generate a parking ticket.
	Mark that spot as occupied.

	When the vehicle exits:

	Read the ticket.
	Calculate parking duration.
	Calculate fee.
	Free the parking spot.
*/


#include <string>
#include <ctime>
#include <vector>
#include <unordered_map>
#include <iostream>

// enum class VehicleType {
// 	BIKE = 0,
// 	CAR = 1,
// 	TRUCK = 2
// };

using namespace std;

enum class VehicleType 
{
	BIKE,
	CAR,
	TRUCK
};


enum class SpotType
{
	SMALL,
	MEDIUM,
	LARGE
};


// Class to identify and hold details about each vehicle
class Vehicle
{
public:
	string licensePlate;
	VehicleType type;
	
	Vehicle(VehicleType type)
	{
		this->type = type;
	}
};


// Class to identify and hold details about each parking spot
class ParkingSpot
{
public:
	int spotId;
	SpotType spottype;
	bool isOccupied;
	Vehicle* vehicle;
	
	ParkingSpot(int id, SpotType type)
	{
		spotId = id;
		spottype = type;
	}
	
	// Function to check if a vehicle can fit in a parking spot
	bool canFitVehicle(Vehicle* vehicle)
	{
		// if (vehicle->type == VehicleType::BIKE)		return true;
		
		if ( vehicle->type == VehicleType::CAR && this->spottype == SpotType::SMALL )	return false;
		
		else if (  vehicle->type == VehicleType::TRUCK && ( this->spottype == SpotType::MEDIUM || this->spottype == SpotType::SMALL ) )	return false;
		
		return true;
	}
	
	// Park vehicle v into this parking spot
	void park(Vehicle* v)
	{
		vehicle = v;
		isOccupied = 1;
	}

	// Remove a parked vehicle from this parking spot
	void removeVehicle()
	{
		vehicle = nullptr;
		isOccupied = false;
	}
	
};


class Ticket
{
public:
	int TicketId;
	Vehicle* vehicle; 
	ParkingSpot* spot;
	time_t startTime;
	
	Ticket(int id, Vehicle* v, ParkingSpot* spot)
	{
		TicketId = id;
		vehicle = v;
		this->spot = spot;
		startTime = time(nullptr);		 
	}
};


class ParkingLot
{
private:
	vector<ParkingSpot*> spots;
	unordered_map<int, Ticket*> activeTickets;		// Map ticket number to ticket object
	int nextTicketId = 1;

public:
	void addSpot(ParkingSpot* spot)
	{
		spots.push_back(spot);
	}
	
	ParkingSpot* findAvailableSpot(Vehicle* vehicle)
	{
		for ( auto spot : spots )
		{
			if ( !spot->isOccupied && spot->canFitVehicle(vehicle) )
			{
				return spot;	
			} 
		}
		
		return nullptr;
	}
	
	// Park vehicle in an available spot and get the corresponding ticket
	Ticket* parkVehicle(Vehicle* vehicle)
	{
		ParkingSpot* spot = findAvailableSpot(vehicle);
		
		if (spot == nullptr)
		{
			cout << "No Spot Avaiable\n";
			return nullptr;
		}
		
		spot->park(vehicle);
		
		// Create a new ticket and store
		Ticket* ticket = new Ticket(nextTicketId++, vehicle, spot);
		activeTickets[ticket->TicketId] = ticket;
		
		return ticket;
	}
	
	
	int calculateFee(Ticket* ticket)
	{
		time_t exitTime = time(nullptr);
		double seconds = difftime(exitTime, ticket->startTime);
		
		int hours = max(1, (int) ceil(seconds/3600));
		
		return hours * 10;
	}
	
	// Get the ticket 
	void exitVehicle(int ticketId)
	{
		// Check if ticket is active
		if ( activeTickets.find(ticketId) == activeTickets.end() )
		{
			cout << "Invalid ticket \n";
			return;
		}
		
		Ticket* ticket = activeTickets[ticketId];
		
		int fee = calculateFee(ticket);
		
		cout << "Fee: " << fee << endl;
		
		ticket->spot->removeVehicle();
		activeTickets.erase(ticketId);
		
		delete ticket;
	}
};



