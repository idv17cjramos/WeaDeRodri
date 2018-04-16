#pragma once
#include <vector>
#include <queue>
class Map
{
public:
	Map();
	~Map();
private:
	class Tree {
	public:
		class Point {
		public:
			Point(int xval, int yval);
			int x, y;
		};
		class Rect {
		public:
			Rect(int xval, int yval, int hval, int wval);
			int x, y, h, w;
			Point center();

		};
		class Leaf {
		public:
			Leaf();
			Leaf(Leaf* const& left, Leaf* const& right);
			~Leaf();
			Rect *container = nullptr;
			Leaf* l = nullptr;
			Leaf* r = nullptr;
			std::vector<Leaf*> getLeafs();
			std::queue<Leaf*> getLevel(int level, std::queue<Leaf*> queue);
		}*head = nullptr;
		Tree(int w, int h);
		~Tree();
		Leaf* SplitContainer(Leaf* head, int iteration);
		std::vector<Leaf*> RandomSplitContainer(Leaf* container);
		int randomRange(int min, int max);
		void draw();
	private:
		int _width, _height;
	} *_map;
};

