#include <iostream>
#include "Listener.hh"
#include <ptypes/ptypes.h>
#include <ptypes/pasync.h>

using namespace std;

class myjob : public PTYPES_NAMESPACE::message
{
public:
	string what;
	myjob(string s, int iid) : message(iid), what(s) {}
	myjob():message(-1){}
};

class mylistener : public Listener<myjob>
{
public:
	mylistener()
	{
		listenForEvents();		
	}
	void processEvent(const myjob &m)
	{
		bool quit = false;
		while (!quit)
		{
		    // get the next message from the queue
		    PTYPES_NAMESPACE::message* msg = jobs.getmessage();
		    try
		    {
		        switch (msg->id)
		        {
		        case 1:
		            {
		               cout<<((myjob*)msg)->what<<get_id();
		            }
		            break;

		        case 0:
		            // MSG_QUIT is not used in our example
		            quit = true;
		            break;
		        }
		    }
		    catch(...)
		    {
		        // the message object must be freed!
		        delete msg;
		        throw;
		    }
		    delete msg;
		}

	}
};
int main()
{
	mylistener myl;
	myl.start();
	mylistener yml;
	yml.start();

	myjob mj1("\n\n1hi-", 1);
	myjob mj2("\n\n2hi-", 1);
	myjob stop("", 0);
	EventSender<myjob>::send(mj1);
	EventSender<myjob>::send(mj2);
	EventSender<myjob>::send(stop);

	myl.waitfor();
	yml.waitfor();
}
