#include <stack>
#include<iostream>
#include<string>

using namespace std;


bool isValid(string s)
{
	// Preliminary check: See if string legnth is even. Else, obviously the parantheses are unmatched.
	if (s.size() % 2 != 0)
	{
		return 0;
	}


	stack<char> stk;

	for (int i = 0; i < s.size(); i++)
	{
		char paran = s[i];

		//Opening paranthesis
		if (paran == '(' || paran == '{' || paran == '[')
		{
			stk.push(paran);
		}


		//Closing paranthesis
		if (paran == ')' || paran == '}' || paran == ']')
		{
			// If stack is already empty but there is a closing bracket in string: This closing bracket is alone, extra and unmatched
			if (stk.empty())
			{
				return 0;
			}


			char corres_open_paran = stk.top();  // Most recent open paranthesis

			// Brackets match
			if (paran == ')' && corres_open_paran == '(' ||
				paran == ']' && corres_open_paran == '[' ||
				paran == '}' && corres_open_paran == '{'
				)
			{
				stk.pop(); // Remove the top char on the stack. Most recent open paranthesis
			}

			else  //Brackets mismatch
			{
				return 0; // Return function and stop
			}
		}

	}

	// Check if stack is empty : This means all open brackets have been closed by a corresponding closing bracket
	if (stk.empty())
	{
		return 1;
	}

	// If stack is not empty : This means NOT ALL open brackets have been closed by a corresponding closing bracket
	else
	{
		return 0;
	}
}


int main()
{
	cout << "Hello";

	string str = "({[]})[](){{[]}}";
	int val = isValid(str);
	cout << "Valid: " << val;

	return 0;
}