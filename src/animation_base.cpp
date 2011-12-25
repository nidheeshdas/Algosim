#include "LibAlgoSim.h"
Animation_base::Animation_base()
{
	listenForEvents();
}
void Animation_base::processEvent(const state& s)
{
	bool quit = false;
	while (!quit)
	{
		PTYPES_NAMESPACE::message* msg = jobs.getmessage();
		try
		{
			switch (msg->id)
			{
			case 2:
			case 1:
				process(*(static_cast<state*> (msg)));
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


