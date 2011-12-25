#include "LibAlgoSim.h"

class ControlUnit
{
	bitset<13> cm;
public:
	void Show(state s)
	{
		if (s.StepName == "Initialise")
		{
			cm[9] = 1;
			cm[10] = 1;
			cm[8] = 1;
		}
		if (s.StepName == "Add M to A")
		{
			cm[2] = 1;
			cm[3] = 1;
			cm[4] = 1;
		}
		if (s.StepName == "Add zero to A")
		{
			cm[2] = 1;
			cm[3] = 1;
			cm[4] = 1;
		}
		if (s.StepName == "Right Shift F.A.Q")
		{
			cm[0] = 1;
			cm[1] = 1;
			cm[11] = 1;
		}
		if (s.StepName == "Subtract M from A")
		{
			cm[2] = 1;
			cm[3] = 1;
			cm[4] = 1;
			cm[5] = 1;
		}
		if (s.StepName == "Set Q[0] to 0")
		{

		}
		if (s.StepName == "Final Output")
		{
			cm[7] = 1;
			cm[6] = 1;
		}
		PrintCM();
	}
	void PrintCM()
	{
		myConsole cgc = gc;
		cgc.setXY(445, 330);
		for (int i = 0; i < 13; i++)
		{
			if (cm[i] == 1)
			{
				cgc.gto.txo_fgcolor.v = GrBlack();
				cgc.gto.txo_bgcolor.v = GrAllocColor(0, 255, 0);
			}
			else
			{
				cgc.gto.txo_bgcolor.v = GrBlack();
				cgc.gto.txo_fgcolor.v = GrAllocColor(0, 255, 0);
			}
			cgc.printf("C" + itoa(i));
		}
	}
};
class blackboard: public Blackboard_base
{
public:
	int i;
	void Init()
	{
		listenForEvents();
		string imgPath = cur_sim->basePath + "/1booth.jpg";
		gc.DrawImage(0, 0, 800, 400, I_JPG, imgPath.c_str());
		GrCreateContext(gc.console_width, gc.console_height, NULL, &ctemp);
		GrBitBlt(&ctemp, 0, 0, NULL, 0, 0, gc.console_width, gc.console_height * (2.0 / 3), GrWRITE);
	}
	void nextStep()
	{
		myConsole ugc = gc;
		ugc.gto.txo_bgcolor.v = GrBlack();
		state s = memory[current_state];
		ugc.printAtXY(itobs(s.values[0], 16), 100, 150);
		ugc.printAtXY(itobs(s.values[1], 16), 300, 150);
		ugc.printAtXY(itobs(s.values[2], 16), 600, 150);
	}
	void process(const state& s)
	{
		gc.clearArea(0, 400, 800, 600);
		ControlUnit cm;
		//cm.Show(s);
		gc << "-------------------------------------------------------------------\n";
		gc << "|No |          Step         |  Accumulator     |    RegisterQ     |\n";
		gc << "-------------------------------------------------------------------\n";
		int p = current_state;
		if (p != 0)
		{
			p--;
			state it = memory[p];
			gc << "| " << setw(2) << p + 1 << "|" << setw(23) << left << it.StepName << "| " << setw(16) << left << itobs(it.values[0], 16) << " | "
					<< setw(16) << left << itobs(it.values[1], 16) << " |\n";
			if (p != (memory.size() - 1))
				p++;
		}
		state it = memory[p];
		gc << "| " << setw(2) << p + 1 << "|" << setw(23) << left << it.StepName << "| " << setw(16) << left << itobs(it.values[0], 16) << " | "
				<< setw(16) << left << itobs(it.values[1], 16) << " |\n";
		gc << "-------------------------------------------------------------------\n";
		gc.print(0, 400);
		gc.printAtXY("'space'->Next Step; 'F'->Go Forward; 'B'->Go Backward; 'Q'->quit", 10, 585);
	}
};
