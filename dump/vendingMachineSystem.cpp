#include <stack>
#include<iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <memory>
#include <string>
#include <unordered_map>

using namespace std;


enum class machineState
{
	chooseMode,
	getCashMode,
	dispenseMode,
	changeReturnMode
};

class product
{
public:
	int pid;
	string pname;
	int price;
	int quantity;
	
	product(int pid=0, string pname="", int price=0, int quantity=0)
	{
		this->pid = pid;
		this->pname = pname;
		this->price = price;
		this->quantity = quantity;
	}
};


class vendingMachine
{
	machineState state;
	unordered_map<int, product> inventory;
	product chosen_pdt;
	int cash_held;

public:
	vendingMachine()
	{
		this->state = machineState::chooseMode;
		cash_held = 0;
	}
	
	void addProduct(int pid, product pdt)
	{
		inventory[pid] = pdt;
	}
	
	void executeState()
	{
		while (1)
		{
			if (state == machineState::chooseMode)
			{
				int out = 1; 
				while ( out == 1 )
				{
					out = askToChoose();
				}
				
				state = machineState::getCashMode;
			}
			
			else if (state == machineState::getCashMode)
			{	
				int out = 1; 
				while ( out == 1 )
				{
					out = receiveCash();
				}
				
				state = machineState::dispenseMode;
			}
			
			else if (state == machineState::dispenseMode)
			{
				dispensePdt();
				
				state = machineState::changeReturnMode;
			}
			
			else if (state == machineState::changeReturnMode)
			{
				returnChange();
				
				state = machineState::chooseMode;
			}			
		}
	}
	
	
	int askToChoose()
	{
		int pid;
		cout << "Enter Product ID";
		cin >> pid;  
		
		if (inventory.find(pid) == inventory.end())
		{
			cout << "Please choose a valid product";

			return 1;
		}
		
		product currProduct = inventory[pid];
		
		if (currProduct.quantity == 0)
		{
			cout << "Please choose a different product";

			return 1;
		}
		
		chosen_pdt = currProduct;
		
		return 0;
	}
	
	int receiveCash()
	{
		cout << "Please input cash";
		int amtReceived;
		
		cin >> amtReceived;
		
		cash_held = cash_held + amtReceived;
		
		if (cash_held < chosen_pdt.price)
		{
			cout << "Insufficient cash, please input more cash";
			return 1;
		}
		
		return 0;
	}
	
	void dispensePdt()
	{
		cash_held = cash_held - chosen_pdt.price;
		inventory[chosen_pdt.pid].quantity--;
		// Dispense
	}
	
	void returnChange()
	{
		// return balance

		if (cash_held > 0)
			cout << "Returning change: " << cash_held << "\n";
		
		cash_held = 0;
	}
	
};

