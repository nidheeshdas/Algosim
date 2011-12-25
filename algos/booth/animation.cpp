#include "LibAlgoSim.h"
#include <vector>
class animation: public Animation_base
{
public:
	sprite aInputX;
	sprite aInputY;
	sprite aAtoQ;
	sprite aAtoPA;
	sprite aPAtoA;
	sprite aXtoPA;
	sprite aCUtoPA;
	sprite aMtoX;
	sprite aCUtoX;
	sprite aQtoCU;
	sprite aQ1toCU;
	sprite aAtoOut;
	sprite aQtoOut;

	animation()
	{
		aInputX.AddPoint(700, 360);
		aInputX.AddPoint(700, 295);
		aInputX.AddPoint(455, 295);
		aInputX.AddPoint(455, 180);
		aInputX.updatePoint.x = 300;
		aInputX.updatePoint.y = 150;
		aInputX.start();

		aInputY.AddPoint(745, 360);
		aInputY.AddPoint(745, 190);
		aInputY.updatePoint.x = 600;
		aInputY.updatePoint.y = 150;
		aInputY.start();

		aAtoQ.AddPoint(245, 150);
		aAtoQ.AddPoint(280, 150);
		aAtoQ.updatePoint.x = 300;
		aAtoQ.updatePoint.y = 150;
		aAtoQ.start();

		aQtoCU.AddPoint(485, 185);
		aQtoCU.AddPoint(485, 315);
		aQtoCU.start();

		aQ1toCU.AddPoint(495, 185);
		aQ1toCU.AddPoint(495, 315);
		aQ1toCU.start();

		aCUtoX.AddPoint(610, 315);
		aCUtoX.AddPoint(610, 250);
		aCUtoX.AddPoint(570, 250);
		aCUtoX.start();

		aMtoX.AddPoint(610, 185);
		aMtoX.AddPoint(610, 220);
		aMtoX.AddPoint(570, 220);
		aMtoX.start();

		aXtoPA.AddPoint(505, 235);
		aXtoPA.AddPoint(350, 235);
		aXtoPA.start();

		aCUtoPA.AddPoint(610, 315);
		aCUtoPA.AddPoint(610, 275);
		aCUtoPA.AddPoint(390, 275);
		aCUtoPA.start();

		aAtoPA.AddPoint(50, 185);
		aAtoPA.AddPoint(50, 210);
		aAtoPA.AddPoint(195, 210);
		aAtoPA.AddPoint(195, 240);
		aAtoPA.start();

		aPAtoA.AddPoint(275, 320);
		aPAtoA.AddPoint(275, 350);
		aPAtoA.AddPoint(120, 350);
		aPAtoA.AddPoint(120, 185);
		aPAtoA.updatePoint.x = 100;
		aPAtoA.updatePoint.y = 150;
		aPAtoA.start();

		aAtoOut.AddPoint(50, 185);
		aAtoOut.AddPoint(50, 360);
		aAtoOut.start();

		aQtoOut.AddPoint(415, 185);
		aQtoOut.AddPoint(415, 360);
		aQtoOut.start();
	}
	void process(const state& s)
	{
		state st = cur_appmain->GetPrevState();
		if (s.StepName == "Initialise")
		{
			aInputX.new_value = s.values[1];
			if (st.StepName != "NULL")
				aInputX.prev_value = st.values[1];
			else
				aInputX.prev_value = 0;
			aInputX.control.post();
			aInputY.new_value = s.values[2];
			if (st.StepName != "NULL")
				aInputY.prev_value = st.values[2];
			else
				aInputY.prev_value = 0;
			aInputY.control.post();
		}
		if (s.StepName == "Add M to A")
		{
			aQtoCU.control.post();
			aQ1toCU.control.post();
			aCUtoX.control.post();
			aMtoX.control.post();
			aCUtoPA.control.post();
			aXtoPA.control.post();
			aAtoPA.control.post();
			aPAtoA.new_value = s.values[0];
			if (st.StepName != "NULL")
				aPAtoA.prev_value = st.values[0];
			else
				aPAtoA.prev_value = 0;
			aPAtoA.control.post();
		}
		if (s.StepName == "Add zero to A")
		{
			aQtoCU.control.post();
			aQ1toCU.control.post();
			aCUtoX.control.post();
			aCUtoPA.control.post();
			aXtoPA.control.post();
			aAtoPA.control.post();
			aPAtoA.new_value = s.values[0];
			if (st.StepName != "NULL")
				aPAtoA.prev_value = st.values[0];
			else
				aPAtoA.prev_value = 0;
			aPAtoA.control.post();
		}
		if (s.StepName == "Right-shift A.Q")
		{
			aAtoQ.new_value = s.values[1];
			if (st.StepName != "NULL")
				aAtoQ.prev_value = st.values[1];
			else
				aAtoQ.prev_value = 0;
			aAtoQ.control.post();
		}
		if (s.StepName == "Subtract M from A")
		{
			aQtoCU.control.post();
			aQ1toCU.control.post();
			aCUtoX.control.post();
			aMtoX.control.post();
			aCUtoPA.control.post();
			aXtoPA.control.post();
			aAtoPA.control.post();
			aPAtoA.new_value = s.values[0];
			if (st.StepName != "NULL")
				aPAtoA.prev_value = st.values[0];
			else
				aPAtoA.prev_value = 0;
			aPAtoA.control.post();
		}
		if (s.StepName == "Set Q[0] to 0")
		{

		}
		if (s.StepName == "Final Output")
		{
			aAtoOut.control.post();
			aQtoOut.control.post();
		}
		if (s.StepName == "NEXTSTEP")
		{
			aInputX.control.reset();
			aInputY.control.reset();
			aAtoQ.control.reset();
			aAtoPA.control.reset();
			aPAtoA.control.reset();
			aXtoPA.control.reset();
			aCUtoPA.control.reset();
			aMtoX.control.reset();
			aCUtoX.control.reset();
			aQtoCU.control.reset();
			aQ1toCU.control.reset();
			aAtoOut.control.reset();
			aQtoOut.control.reset();
		}
	}
};
