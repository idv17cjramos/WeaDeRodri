#pragma once
#include <vector>
#include <queue>
#include <string>
#include "Tile.h"
#include <fstream>
class Map
{
public:
	Map(int w, int h, float ratioW, float ratioH, int iterations);
	Map(std::string path);
	~Map();
	void drawMap();
	void SaveMapToFile(std::string path);
	Tile getTileAt(size_t x, size_t y) const;
	void setPlayerPositon(int x, int y);
private:
	void LoadFromFile(std::string path);
	class Tree {
	public:
		class Point {
		public:
			Point(int xval, int yval);
			Point operator-(Point other);
			int x, y;
		};
		class Rect {
		public:
			Rect();
			Rect(int xval, int yval, int wval, int hval);
			Rect(Rect* head);
			int x, y, h, w;
			Point center();
			void drawPath(std::vector<Tile>& tmap, int w, Rect* other);
		};
		class Leaf {
		public:
			Leaf();
			Leaf(Leaf* const& left, Leaf* const& right);
			Leaf(Rect* rect);
			~Leaf();
			Rect *container = nullptr;
			Leaf* l = nullptr;
			Leaf* r = nullptr;
			std::vector<Leaf*> getLeafs();
			std::queue<Leaf*> getLevel(int level, std::queue<Leaf*>& queue);
		};
		class Room {
		public:
			Room(Rect* const& container);
			Room(const Rect& container);
			Room();
			~Room();
			Rect *rect = nullptr;
		};
		Tree(int w, int h, float ratioW, float ratioH, std::vector<Tile>& tmap, int iterations);
		~Tree();
		Leaf* SplitContainer(Rect* head, int iteration);
		std::vector<Rect*> RandomSplitContainer(Rect* container);
	private:
		Leaf *_head = nullptr;
		std::vector<Room> _rooms;
		int _width, _height;
		float _ratioW, _ratioH;
		void draw(std::vector<Tile>& tmap, int w);
		void drawPaths(std::vector<Tile>& tmap, int w);
		void populate(std::vector<Tile>& tmap, int w);
		void recursiveDrawPath(std::vector<Tile>& tmap, int w, Leaf* head);
	} *_map = nullptr;
	std::vector<Tile> _tiledMap;
	int _width, _height;
	friend std::ostream& operator<<(std::ostream& o, Map map);
	friend std::istream& operator>>(std::istream& i, Map& map);
};


