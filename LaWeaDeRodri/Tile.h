#pragma once
#include "Entity.h"
#include "Definitions.h"

class Tile :
	public Entity
{
public:
	Tile();
	~Tile();
private:
	TileType _tType;

};

