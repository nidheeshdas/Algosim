#include <vector>
#include <cmath>
#include "LibAlgoSim.h"
using namespace std;
sprite::~sprite()
{
	waitfor();
}
void sprite::execute()
{
	point prev_pos;
	point poi;
	myConsole sgc = gc;
	sgc.gto.txo_bgcolor.v = GrBlack();
	while (1)
	{
		control.wait();
		if (updatePoint.x != -1)
			sgc.printAtXY(itobs(prev_value, bitLength), updatePoint.x, updatePoint.y);
		for (int i = 0; i < 100; i++)
		{
			poi = m_path.GetPointByPercentage(i);
			GrBitBlt(NULL, prev_pos.x - 10, prev_pos.y - 10, &cur_blackboard->ctemp, prev_pos.x - 10, prev_pos.y - 10, prev_pos.x + 10, prev_pos.y
					+ 10, GrWRITE);
			GrFilledCircle(poi.x, poi.y, 5, GrAllocColor(0, 0, 255));
			prev_pos = poi;
			i++;
			relax(50);
		}
		if (updatePoint.x != -1)
			sgc.printAtXY(itobs(new_value, bitLength), updatePoint.x, updatePoint.y);
		GrBitBlt(NULL, prev_pos.x - 10, prev_pos.y - 10, &cur_blackboard->ctemp, prev_pos.x - 10, prev_pos.y - 10, prev_pos.x + 10, prev_pos.y + 10,
				GrWRITE);
		relax(1000);
	}

}
void sprite::AddPoint(int x, int y)
{
	m_path.AddPoint(x, y);
}
