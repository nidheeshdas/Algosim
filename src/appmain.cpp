//#define DEFINE_GLOBALS
#include "LibAlgoSim.h"
#include <X11/Xlib.h>
#include <ctime>
state& state::operator=(const state& s)
{
	StepName = s.StepName;
	values = s.values;
	return *this;
}

string itoa(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

string itobs(int x, int numBits)
{
	stringstream ss;
	for (int i = 0; i < numBits; i++)
		ss << ((x & (1 << numBits - i - 1)) ? 1 : 0);
	return ss.str();
}

void appmain::processEvent(const state &ev)
{
}

void appmain::Init(IAlgoSim *sim)
{
	cur_algo = sim->GetAlgorithm();
	cur_anim = sim->GetAnimation();
	cur_blackboard = sim->GetBlackboard();
	cur_sim = sim;

	cur_algo->start();
	cur_anim->start();
	cur_blackboard->start();
	memory.clear();
}

void appmain::Run()
{
	cur_appmain = this;
	cur_sim->Run();
}
extern Display * _XGrDisplay;
void appmain::betweenStep()
{
	GrEvent ev;
	bool quit = false;
	struct timespec ts, rem;
	ts.tv_sec = 0;
	ts.tv_nsec = 100000000;
	do
	{
		state temp = memory[current_state];
		temp.id = 1;
		state st(2, "NEXTSTEP");
		EventSender<state>::send(st);
		EventSender<state>::send(temp);
		while (1)
		{
			nanosleep(&ts, &rem);
			xcomm.lock();
			if (GrEventCheck())
			{
				GrEventRead(&ev);
				xcomm.unlock();
				if (ev.p1 == GrKey_q || ev.p1 == GrKey_Q)
					exit(0);
				if (ev.p1 == GrKey_Space)
				{
					//next step
					quit = true;
					break;
				}
				if (ev.p1 == GrKey_f || ev.p1 == GrKey_F)
				{
					OneStepForward();
					break;
				}
				if (ev.p1 == GrKey_b || ev.p1 == GrKey_B)
				{
					OneStepBack();
					break;
				}
			}
			else
				xcomm.unlock();
		}
		state st2(2, "NEXTSTEP");
		EventSender<state>::send(st2);
	} while (!quit);
}

void appmain::OneStepBack()
{
	if (current_state != 0)
		current_state -= 1;
}

void appmain::OneStepForward()
{
	if (current_state != (memory.size() - 1))
		current_state += 1;

}

state appmain::GetPrevState()
{
	state st;
	st.StepName = "NULL";
	if (current_state != 0)
	{
		st = memory[current_state - 1];
	}
	return st;
}
