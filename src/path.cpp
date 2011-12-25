#include <vector>
#include <cmath>
#include "LibAlgoSim.h"

using namespace std;
point::point(int a, int b)
{
	x = a;
	y = b;
}

void path::CalculateTotalDistance()
{
	int total = 0;
	for (int i = 0; i < m_path.size() - 1; i++)
	{
		total += sqrt(pow((m_path[i].x - m_path[i + 1].x), 2) + pow((m_path[i].y - m_path[i + 1].y), 2));
		m_totalDistance = total;
	}
}
point path::GetPointByDistance(int p)
{
	CalculateTotalDistance();
	if (p > m_totalDistance)
		p %= m_totalDistance;
	int temp_dist = 0;
	int total = 0;
	for (int i = 0; i < m_path.size() - 1; i++)
	{
		total += sqrt(pow((m_path[i].x - m_path[i + 1].x), 2) + pow((m_path[i].y - m_path[i + 1].y), 2));
		if (total > p)
		{
			int req_dist = p - temp_dist;
			float ang_sin = (m_path[i].y - m_path[i + 1].y) / sqrt(pow((m_path[i].x - m_path[i + 1].x), 2) + pow((m_path[i].y - m_path[i + 1].y), 2));
			point po;
			po.y = m_path[i].y - (ang_sin * req_dist);
			float ang_cos = 0;
			if (ang_sin == 0)
				ang_cos = 1;
			else if (ang_sin == 1)
				ang_cos = 0;
			else
				ang_cos = sqrt(1 - pow(((int) ang_sin), 2));
			if (m_path[i].x < m_path[i + 1].x)
				po.x = m_path[i].x + (ang_cos * req_dist);
			else
				po.x = m_path[i].x - (ang_cos * req_dist);
			return po;

		}
		temp_dist = total;
	}

}

void path::AddPoint(int x, int y)
{
	point p(x, y);
	m_path.push_back(p);
}
point path::GetPointByPercentage(int p)
{
	CalculateTotalDistance();
	p = (p / 100.00) * m_totalDistance;
	return GetPointByDistance(p);

}
