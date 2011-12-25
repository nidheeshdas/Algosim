#include "LibAlgoSim.h"
#include <vector>
class algorithm : public Algorithm_base
{
public:
	int count;
	algorithm()
	{
		count = 0;
	}
	void processEvent(const state&st)
	{

	}
	state CreateCurrentState()
	{
		state s;
		vector<int> temp;
		s.StepName = Step_Name;
		temp.push_back(reg_AC.to_ulong());
		temp.push_back(reg_Q.to_ulong());
		temp.push_back(reg_M.to_ulong());
		temp.push_back(f);
		temp.push_back(count);
		s.values = temp;
		return s;
	}
	void ReInitialiseFromState(state s)
	{
		Step_Name = s.StepName;
		reg_AC = s.values[0];
		reg_Q = s.values[1];
		reg_M = s.values[2];
		f = s.values[3];
		count = s.values[4];
	}
	void StartMachine()
	{
		Step_Name = "Initialise";
		CreateState();
		while (count < regSize)
		{
			if (reg_Q[0] == 1)
			{
				reg_AC = reg_AC.to_ulong() + reg_M.to_ulong();
				Step_Name = "Add M to A";
				CreateState();
			}
			else
			{
				Step_Name = "Add zero to A";
				CreateState();
			}
			f = (reg_M[regSize - 1] & reg_Q[0]) | f;
			reg_Q >>= 1;
			reg_Q[regSize - 1] = reg_AC[0];
			reg_AC >>= 1;
			reg_AC[regSize - 1] = f;
			count++;
			Step_Name = "Right Shift F.A.Q";
			CreateState();
		}
		reg_AC = reg_AC.to_ulong() - reg_M.to_ulong() * reg_Q[0];
		Step_Name = "Subtract M from A";
		CreateState();
		reg_Q[0] = 0;
		Step_Name = "Set Q[0] to 0";
		CreateState();
		Step_Name = "Final Output";
		CreateState();

	}
};
