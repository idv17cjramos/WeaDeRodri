#include "RPGItem.h"

RPGItem::RPGItem()
{
	_type = RPGItemType::RPGItemTypeEnumEnd;
	_usageType = RPGItemUsageType::HealHP;
	_value = 0;
	_name = "Nil.";
	_description = "Nil.";
}

RPGItem::RPGItem(RPGItemType type, RPGItemUsageType usage, std::string name, int value, std::string description)
{
	_type = type;
	_usageType = usage;
	_name = name;
	_value = value;
	_description = description;
}

RPGItem::RPGItem(const RPGItem & cpy)
{
	_type = cpy._type;
	_usageType = cpy._usageType;
	_name = cpy._name;
	_value = cpy._value;
	_description = cpy._description;
}

RPGItem::~RPGItem()
{
}

RPGItemType RPGItem::getType() const
{
	return _type;
}

std::string RPGItem::getName() const
{
	return _name;
}

std::string RPGItem::getDescription() const
{
	return _description;
}

int RPGItem::getValue() const
{
	return _value;
}

RPGItemUsageType RPGItem::getUsage() const
{
	return _usageType;
}
