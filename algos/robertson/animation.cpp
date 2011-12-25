#include "LibAlgoSim.h"
#include <vector>
class animation: public Animation_base
{
public:
	sprite aInputX;
	sprite aInputY;
	sprite aFtoA;
	sprite aAtoQ;
	sprite aQtoF;
	sprite aMtoF;
	sprite aAtoPA;
	sprite aPAtoA;
	sprite aXtoPA;
	sprite aCUtoPA;
	sprite aMtoX;
	sprite aCUtoX;
	sprite aQtoCU;
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

		aMtoF.AddPoint(565, 125);
		aMtoF.AddPoint(565, 35);
		aMtoF.AddPoint(160, 35);
		aMtoF.updatePoint.x = 60;
		aMtoF.updatePoint.y = 70;
		aMtoF.bitLength = 1;
		aMtoF.start();

		aQtoF.AddPoint(495, 120);
		aQtoF.AddPoint(495, 70);
		aQtoF.AddPoint(155, 70);
		aQtoF.updatePoint.x = 60;
		aQtoF.updatePoint.y = 70;
		aQtoF.bitLength = 1;
		aQtoF.start();

		aFtoA.AddPoint(30, 90);
		aFtoA.AddPoint(30, 120);
		aFtoA.updatePoint.x = 100;
		aFtoA.updatePoint.y = 150;
		aFtoA.start();

		aAtoQ.AddPoint(245, 150);
		aAtoQ.AddPoint(280, 150);
		aAtoQ.start();

		aQtoCU.AddPoint(485, 185);
		aQtoCU.AddPoint(485, 315);
		aQtoCU.start();

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
			aQtoF.control.post();
			aMtoF.control.post();
			aQtoCU.control.post();
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
			aQtoF.control.post();
			aMtoF.control.post();
			aQtoCU.control.post();
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
		if (s.StepName == "Right Shift F.A.Q")
		{
			if (st.StepName != "NULL")
				aFtoA.prev_value = st.values[0];
			else
				aFtoA.prev_value = 0;
			aFtoA.control.post();
			if (st.StepName != "NULL")
				aAtoQ.prev_value = st.values[1];
			else
				aAtoQ.prev_value = 0;
			aAtoQ.control.post();
		}
		if (s.StepName == "Subtract M from A")
		{
			aQtoCU.control.post();
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
			aMtoF.control.reset();
			aQtoF.control.reset();
			aFtoA.control.reset();
			aAtoQ.control.reset();
			aQtoF.control.reset();
			aMtoF.control.reset();
			aAtoPA.control.reset();
			aPAtoA.control.reset();
			aXtoPA.control.reset();
			aCUtoPA.control.reset();
			aMtoX.control.reset();
			aCUtoX.control.reset();
			aQtoCU.control.reset();
			aAtoOut.control.reset();
			aQtoOut.control.reset();
		}
	}
};
