#include "Tile.h"

unsigned char Tile::_realTiles[TileEnumEnd] = 
{
	176, //Forest
	176, //Path
	176, //Lava
	176, //Water
	234, //Rock
	254, //Treasure
	154, //Merchant
	158, //Boss
	143, //Player
};
unsigned short Tile::_realColors[TileEnumEnd] = 
{
	LetterColor::GREEN | BackgroundColor::BBLACK,
	LetterColor::WHITE | BackgroundColor::BBLACK,
	LetterColor::RED | BackgroundColor::BBLACK,
	LetterColor::BLUE | BackgroundColor::BBLACK,
	LetterColor::DARKYELLOW | BackgroundColor::BBLACK,
	LetterColor::YELLOW | BackgroundColor::BBLACK,
	LetterColor::MAGENTA | BackgroundColor::BBLACK,
	LetterColor::DARKRED | BackgroundColor::BBLACK,
	LetterColor::MAGENTA | BackgroundColor::BBLACK,
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
	if (TileType::TileEnumEnd == type)
	{
		setSprite(nullptr, nullptr, 1, 1);
		return;
	}
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
