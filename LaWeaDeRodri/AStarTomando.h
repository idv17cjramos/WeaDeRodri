#pragma once
#include "Map.h"
#include <vector>

class Point
{
public:
	Point()
	{
		x = y = 0;
	}
	Point(const int& xP, const int& yP)
	{
		x = xP;
		y = yP;
	}
	int x, y;
	bool operator==(const Point& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Point& rhs) const { return !((*this) == rhs); }
	static int Distance(const Point& lhs, const Point& rhs)
	{
		return (int)(sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2)));
	}
	static int Manhattan(const Point& lhs, const Point& rhs)
	{
		return (int)(abs(lhs.x - rhs.y) + abs(lhs.x - rhs.y));
	}
};

class AStarTomando
{
public:
	AStarTomando();
	~AStarTomando();
	void SetStart(Point start);
	void SetEnd(Point end);
	Point getCurrPosition();
	Point nextStep();
	void CalculateRoute();
	void SetMap(Map * const& map);
private:
	Point _start, _end;
	std::vector<Tile> _nodeList;
	int _iterator = 0;
	Map* _map = nullptr;
	int getSmallestF(const std::vector<__int64>& fvals);
	bool tileInSet(std::vector<Tile>& set, Tile& tile);
	void reconstructPath(const std::vector<Tile>& cameFrom, const Tile& current);
};

