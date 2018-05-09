#pragma once
#include "Entity.h"
#include "Definitions.h"

class Tile :
	public Entity
{
public:
	Tile();
	Tile(TileType type, TileStatus status = TileStatus::NotWalked);
	~Tile();
	void SetStatus(TileStatus status);
	void SetTileType(TileType type);
	TileStatus GetStatus() const;
	TileType GetType() const;
	Tile* left = nullptr, *right = nullptr, *up = nullptr, *down = nullptr;
private:
	TileType _tType = TileEnumEnd;
	TileStatus _status = TileStatus::NotWalked;
	static unsigned char _realTiles[TileEnumEnd];
	static unsigned short _realColors[TileEnumEnd];
};
