#include "AStarTomando.h"
#include <algorithm>


AStarTomando::AStarTomando()
{
}


AStarTomando::~AStarTomando()
{
}

void AStarTomando::SetStart(Point start)
{
}

void AStarTomando::SetEnd(Point end)
{
}

Point AStarTomando::getCurrPosition()
{
	return Point(_nodeList[_iterator].getX(), _nodeList[_iterator].getY());
}

Point AStarTomando::nextStep()
{
	++_iterator;
	if(_iterator >= _nodeList.size())
		return Point(_nodeList[_nodeList.size() - 1].getX(), _nodeList[_nodeList.size() - 1].getY());
	return Point(_nodeList[_iterator].getX(), _nodeList[_iterator].getY());
}

void AStarTomando::CalculateRoute()
{
	_nodeList.clear();
	if (_map == nullptr)
		return;
	if (_start == _end)
	{
		_nodeList.push_back(Tile());
		return;
	}
	std::vector<Tile> closedSet;
	std::vector<Tile> openSet;
	openSet.push_back(_map->getTileAt(_start.x,_start.y));
	std::vector<__int64> gScore, fScore;
	fScore.push_back(Point::Manhattan(_start, _end));
	gScore.push_back(0);
	Tile current;
	Point currPoint;
	int currindex;
	while (!openSet.empty())
	{
		currindex = getSmallestF(fScore);
		current = openSet[currindex];
		currPoint = Point(current.getX(), current.getY());
		if (currPoint == _end)
		{
			//reconstruir camino
			return;
		}
		std::remove(openSet.begin(), openSet.end(), current);
		closedSet.push_back(current);

	}
		
}

void AStarTomando::SetMap(Map * const & map)
{
	_map = map;
}

int AStarTomando::getSmallestF(const std::vector<__int64>& fvals)
{
	__int64 minVal = INT64_MAX;
	int ret = 0;
	for (int i = 0; i < fvals.size(); ++i)
	{
		if (fvals[i] <= minVal)
		{
			minVal = fvals[i];
			ret = i;
		}
	}
	return ret;
}
