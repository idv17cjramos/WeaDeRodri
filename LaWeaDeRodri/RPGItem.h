#pragma once
#include <string>
#include "Definitions.h"
class RPGItem
{
public:
	RPGItem();
	RPGItem(RPGItemType type, RPGItemUsageType usage, std::string name, int value, std::string description);
	RPGItem(const RPGItem &cpy);
	~RPGItem();
	RPGItemType getType() const;
	std::string getName() const;
	std::string getDescription() const;
	int getValue() const;
	RPGItemUsageType getUsage() const;
	//TODO: Crear objetos estaticos de tipo RPGItem para cada item
private:
	RPGItemType _type;
	std::string _name, _description;
	int _value;
	RPGItemUsageType _usageType;
};

