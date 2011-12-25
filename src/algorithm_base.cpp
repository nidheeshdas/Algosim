#include <iostream>
#define DEFINE_GLOBALS
#include "LibAlgoSim.h"

/**

   \file
    Class definition file.

 */


using namespace std;

Algorithm_base::Algorithm_base()
{
	regSize = 16;
	reg_AC = 0;
	reg_Q = 0;
	reg_M = 0;
	f = false;
	listenForEvents();
}

void Algorithm_base::CreateState()
{
	state st = this->CreateCurrentState();
	memory.push_back(st);
	current_state = memory.size() - 1;

	cur_appmain->betweenStep();
	st = memory[current_state];
	this->ReInitialiseFromState(st);
}

