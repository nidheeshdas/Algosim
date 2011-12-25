#include <iostream>
#include <cstdlib>
#include "LibAlgoSim.h"
#include "algorithm.cpp"
#include "blackboard.cpp"
#include "animation.cpp"

using namespace std;

class mysim: public IAlgoSim
{
	bool isNumber(string s)
	{
		for (int i = 0; i < s.length(); i++)
			if (s[i] < '0' || s[i] > '9')
				return false;
		return true;
	}
public:
	void Run()
	{
		string in1, in2;
		do
		{
			gc << "\nEnter First Number: ";
			gc.print(0, 400);
			in1 = gc.scan();
			if (isNumber(in1))
				break;
			gc.clrscr();
			gc << "\n\nPlease enter a number (in decimal format using 0-9)";
			gc.print(1, 370);
		} while (1);
		do
		{
			gc << "\nEnter Second Number: ";
			gc.print(0, 430);
			in2 = gc.scan();
			if (isNumber(in2))
				break;
			gc.clrscr();
			gc << "\n\nPlease enter a number (in decimal format using 0-9)";
			gc.print(1, 370);
		} while (1);
		cur_algo->reg_Q = atoi(in1.c_str());
		cur_algo->reg_M = atoi(in2.c_str());
		cur_blackboard->Init();
		cur_algo->StartMachine();
	}
	mysim()
	{
		name = "Robertson's Algorithm";
	}
	Algorithm_base* GetAlgorithm()
	{
		return new algorithm;
	}
	Blackboard_base* GetBlackboard()
	{
		return new blackboard;
	}
	Animation_base* GetAnimation()
	{
		return new animation;
	}

};

extern "C"
IAlgoSim* maker()
{
	return new mysim();
}
