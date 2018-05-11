#include "AStarTomando.h"
#include <algorithm>
#include "HelperFunctions.h"

AStarTomando::AStarTomando()
{
}


AStarTomando::~AStarTomando()
{
}

void AStarTomando::SetStart(Point start)
{
	_start = start;
}

void AStarTomando::SetEnd(Point end)
{
	_end = end;
}

Point AStarTomando::getCurrPosition()
{
	if(_iterator == _nodeList.size())
		return Point(_nodeList[_iterator - 1].getX(), _nodeList[_iterator - 1].getY());
	if (_iterator < 0)
		return Point(_nodeList[0].getX(), _nodeList[0].getY());
	return Point(_nodeList[_iterator].getX(), _nodeList[_iterator].getY());
}

Point AStarTomando::nextStep()
{
	--_iterator;
	if(_iterator < 0)
		return Point(_nodeList[0].getX(), _nodeList[0].getY());
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
	std::vector<Tile> cameFrom(_map->getMap().size());
	openSet.push_back(_map->getTileAt(_start.x,_start.y));
	std::vector<__int64> gScore(_map->getMap().size(), 9999999999), fScore(_map->getMap().size(), 9999999999);
	size_t accessor = getAccessor(_start.x, _start.y, 300);
	gScore[accessor] = 0;
	fScore[accessor] = Point::Manhattan(_start, _end);
	Tile current;
	Point currPoint;
	int currindex;
	while (!openSet.empty())
	{
		currindex = getSmallestF(openSet, fScore);
		current = openSet[currindex];
		currPoint = Point(current.getX(), current.getY());
		size_t curracc = getAccessor(current.getX(), current.getY(), 300);
		if (currPoint == _end)
		{
			reconstructPath(cameFrom, current);
			return;
		}
		openSet.erase(openSet.begin() + currindex);
		closedSet.push_back(current);
		if (!tileInSet(closedSet, *current.down) && 
			(current.down->GetType() == TileType::Forest || current.down->GetType() == TileType::Path ||
				current.down->GetType() == TileType::Lava))
		{
			size_t downacc = getAccessor(current.down->getX(), current.down->getY(), 300);
			Point downPoint = Point(current.down->getX(), current.down->getY());
			if(!tileInSet(openSet,*current.down))
				openSet.push_back(*current.down);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(downPoint, _end);
			if (tentativeGScore < gScore[downacc])
			{
				cameFrom[downacc] = current;
				cameFrom[downacc].SetStatus(TileStatus::Walked);
				gScore[downacc] = tentativeGScore;
				fScore[downacc] = gScore[downacc] + Point::Manhattan(downPoint, _end);
			}
		}
		if (!tileInSet(closedSet, *current.up) &&
			(current.up->GetType() == TileType::Forest || current.up->GetType() == TileType::Path ||
				current.up->GetType() == TileType::Lava))
		{
			size_t upacc = getAccessor(current.up->getX(), current.up->getY(), 300);
			Point upPoint = Point(current.up->getX(), current.up->getY());
			if (!tileInSet(openSet, *current.up))
				openSet.push_back(*current.up);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(upPoint, _end);
			if (tentativeGScore < gScore[upacc])
			{
				cameFrom[upacc] = current;
				cameFrom[upacc].SetStatus(TileStatus::Walked);
				gScore[upacc] = tentativeGScore;
				fScore[upacc] = gScore[upacc] + Point::Manhattan(upPoint, _end);
			}
		}
		if (!tileInSet(closedSet, *current.left) &&
			(current.left->GetType() == TileType::Forest || current.left->GetType() == TileType::Path ||
				current.left->GetType() == TileType::Lava))
		{
			size_t leftacc = getAccessor(current.left->getX(), current.left->getY(), 300);
			Point leftPoint = Point(current.left->getX(), current.left->getY());
			if (!tileInSet(openSet, *current.left))
				openSet.push_back(*current.left);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(leftPoint, _end);
			if (tentativeGScore < gScore[leftacc])
			{
				cameFrom[leftacc] = current;
				gScore[leftacc] = tentativeGScore;
				cameFrom[leftacc].SetStatus(TileStatus::Walked);
				fScore[leftacc] = gScore[leftacc] + Point::Manhattan(leftPoint, _end);
			}
		}
		if (!tileInSet(closedSet, *current.right) &&
			(current.right->GetType() == TileType::Forest || current.right->GetType() == TileType::Path ||
				current.right->GetType() == TileType::Lava))
		{
			size_t rightacc = getAccessor(current.right->getX(), current.right->getY(), 300);
			Point rightPoint = Point(current.right->getX(), current.right->getY());
			if (!tileInSet(openSet, *current.right))
				openSet.push_back(*current.right);
			__int64 tentativeGScore = gScore[curracc] +
				Point::Manhattan(rightPoint, _end);
			if (tentativeGScore < gScore[rightacc])
			{
				cameFrom[rightacc] = current;
				cameFrom[rightacc].SetStatus(TileStatus::Walked);
				gScore[rightacc] = tentativeGScore;
				fScore[rightacc] = gScore[rightacc] + Point::Manhattan(rightPoint, _end);
			}
		}
	}
	return;
}

void AStarTomando::SetMap(Map * const & map)
{
	_map = map;
}

int AStarTomando::getSmallestF(std::vector<Tile>& openSet, const std::vector<__int64>& fvals)
{
	__int64 minVal = INT64_MAX;
	int retVal = 0;
	for (int i = 0; i < openSet.size(); ++i)
	{
		int val = fvals[getAccessor(openSet[i].getX(), openSet[i].getY(), 300)];
		if(val <= minVal)
		{
			retVal = i;
			minVal = val;
		}
	}
	return retVal;
}

bool AStarTomando::tileInSet(std::vector<Tile>& set, Tile tile)
{
	for(auto &i : set)
	{ 
		if (i.getX() == tile.getX() && i.getY() == tile.getY())
			return true;
	}
	return false;
}

void AStarTomando::reconstructPath(const std::vector<Tile>& cameFrom, Tile & current)
{
	Tile actualTile = cameFrom[getAccessor(current.getX(),current.getY(), 300)];
	_nodeList.push_back(actualTile);
	std::vector<Tile> rejectedList;
	while (actualTile.getX() != _start.x || actualTile.getY() != _start.y)
	{
		if (cameFrom[getAccessor(actualTile.down->getX(), actualTile.down->getY(), 300)].GetStatus() == TileStatus::Walked &&
			!tileInSet(_nodeList, cameFrom[getAccessor(actualTile.down->getX(), actualTile.down->getY(), 300)]) &&
			!tileInSet(rejectedList, cameFrom[getAccessor(actualTile.down->getX(), actualTile.down->getY(), 300)]))
			actualTile = cameFrom[getAccessor(actualTile.down->getX(), actualTile.down->getY(), 300)];
		else if (cameFrom[getAccessor(actualTile.up->getX(), actualTile.up->getY(), 300)].GetStatus() == TileStatus::Walked &&
			!tileInSet(_nodeList, cameFrom[getAccessor(actualTile.up->getX(), actualTile.up->getY(), 300)]) &&
			!tileInSet(rejectedList, cameFrom[getAccessor(actualTile.up->getX(), actualTile.up->getY(), 300)]))
			actualTile = cameFrom[getAccessor(actualTile.up->getX(), actualTile.up->getY(), 300)];
		else if (cameFrom[getAccessor(actualTile.left->getX(), actualTile.left->getY(), 300)].GetStatus() == TileStatus::Walked &&
			!tileInSet(_nodeList, cameFrom[getAccessor(actualTile.left->getX(), actualTile.left->getY(), 300)]) &&
			!tileInSet(rejectedList, cameFrom[getAccessor(actualTile.left->getX(), actualTile.left->getY(), 300)]))
			actualTile = cameFrom[getAccessor(actualTile.left->getX(), actualTile.left->getY(), 300)];
		else if (cameFrom[getAccessor(actualTile.right->getX(), actualTile.right->getY(), 300)].GetStatus() == TileStatus::Walked &&
			!tileInSet(_nodeList, cameFrom[getAccessor(actualTile.right->getX(), actualTile.right->getY(), 300)]) &&
			!tileInSet(rejectedList, cameFrom[getAccessor(actualTile.right->getX(), actualTile.right->getY(), 300)]))
			actualTile = cameFrom[getAccessor(actualTile.right->getX(), actualTile.right->getY(), 300)];
		else
		{
			rejectedList.push_back(_nodeList[_nodeList.size() - 1]);
			_nodeList.erase(_nodeList.end());
			actualTile = _nodeList[_nodeList.size() - 1];
			continue;
		}
		_nodeList.push_back(actualTile);
	}
	_iterator = _nodeList.size();
	//añadir a NodeList todos los elementos que tengan walked recorriendo desde current
	//https://en.wikipedia.org/wiki/A*_search_algorithm
}
