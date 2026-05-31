#include <vector>


using namespace std;


enum FSMState
{
	normalState,
	coolMode,
	heatMode,
	heatAlarm,
	coolAlarm
};

struct config
{
	double minTemp;
	double maxTemp;
	double targetTemp;	
};


struct tempState
{
	FSMState roomFSMState;
	int currTemp;
	int supplyPos;
	int exhaustPos;
};

class temperatureController
{
private:
	struct config roomConfig;
	struct tempState roomState;
	double supplyCommand;
	double exhaustCommand;

public:
	temperatureController(struct config inputConfig)
	{
		//  mutex
		roomConfig = inputConfig;
		// mutex
	}
	
	
	void runCycle()
	{
		// readRoomState
		//roomstate = io.readState();
		
		updateState();
		
		
		if ( roomState.roomFSMState == FSMState::coolMode )
		{
			double error = roomConfig.targetTemp - roomState.currTemp;
			supplyCommand = func(error);
			exhaustCommand = MAX;		
		}
		
		io.setChillSupply
		io.setExhaustSupply
	}
	
	void updateState()
	{
		if (roomState.currTemp > roomConfig.maxTemp)
		{
			roomState.roomFSMState = FSMState::coolMode;
		}
	}
	
	
	void setManualConfig()
	{
		
	};
	
	void readConfig()
	{
		// mutex
		
		//mutex 
	};
};


int main()
{
	
}