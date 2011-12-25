#include "LibAlgoSim.h"
Blackboard_base::Blackboard_base()
{
	listenForEvents();
}

void Blackboard_base::processEvent(const state& s)
{
	bool quit = false;
	while (!quit)
	{
		PTYPES_NAMESPACE::message* msg = jobs.getmessage();
		try
		{
			switch (msg->id)
			{
			case 1:
				process(*(static_cast<state*> (msg)));
				break;
			case 2:
				nextStep();
				break;
			case 0:
				quit = true;
				break;
			}
		} catch (...)
		{
			delete msg;
			throw ;
		}
		delete msg;
	}
}
