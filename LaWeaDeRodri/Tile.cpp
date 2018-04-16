#include "Tile.h"

unsigned char Tile::_realTiles[TileEnumEnd] = 
{
	157, //Forest
	176, //Path
	234, //Rock
	224, //Lava
	247, //Water
	254, //Treasure
	154, //Merchant
	158 //Boss
};
unsigned short Tile::_realColors[TileEnumEnd] = 
{
	LetterColor::GREEN | BackgroundColor::BBLACK,
	LetterColor::WHITE | BackgroundColor::BBLACK,
	LetterColor::DARKYELLOW | BackgroundColor::BBLACK,
	LetterColor::RED | BackgroundColor::BBLACK,
	LetterColor::BLUE | BackgroundColor::BCYAN,
	LetterColor::YELLOW | BackgroundColor::BBLACK,
	LetterColor::MAGENTA | BackgroundColor::BBLACK,
	LetterColor::DARKRED | BackgroundColor::BBLACK,
};

Tile::Tile()
{
	_xSize = 1;
	_ySize = 1;
}

Tile::Tile(TileType type, TileStatus status) : Tile()
{
	SetStatus(status);
	SetTileType(type);
}


Tile::~Tile()
{
}

void Tile::SetStatus(TileStatus status)
{
	_status = status;
}

void Tile::SetTileType(TileType type)
{
	_tType = type;
	setSprite(&_realTiles[type], &_realColors[type], 1, 1);
}

TileStatus Tile::GetStatus() const                                             
{
	return _status;
}

TileType Tile::GetType() const
{
	return _tType;
}
