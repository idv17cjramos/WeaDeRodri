#include "RPGCharacter.h"
#include "HelperFunctions.h"
#include "Skills.h"
#include <fstream>

Stats RPGCharacter::_classStats[RPGClass::RPGClassEnumEnd] = /*Rellenando  un arreglo de stats con una inicialización de arreglo. Con esto llenas de madrazo el arreglo.
															lo rellenas con un inicializador de una estructura.*/	
{
	Stats{5,9,5,9,3}, //Warrior
	Stats{6,5,4,7,10}, //Paladin
	Stats{6,4,6,6,7}, //Barbarian
	Stats{1,4,8,9,3}, //Archer
	Stats{2,4,7,1,8}, //Thief
	Stats{4,4,6,5,5}, //Priest
	Stats{8,3,8,10,8}, //Mage
	Stats{7,10,9,1,4}, //Summoner
};

RPGCharacter::RPGCharacter(RPGClass classT, size_t lvl, std::string name) : _skills(nullptr)
{
	_level = 1;
	_experience = 0;
	_maxSkills = 0;
	_hp = _maxHP = _basehp;
	_mp = _maxMP = _basemp;
	_defense = _baseDefense;
	_nextLevelExperience = 10;
	_class = classT;
	_stats = _classStats[classT];
	_name = name;
	switch (_class)
	{
		//TODO: llenar tabla de saltos
	case Warrior:
		_maxSkillsCap = RPGWarriorSkillsEnumEnd;
		_skills = new Skill[RPGWarriorSkillsEnumEnd];
		break;
	case Paladin:
		_maxSkillsCap = RPGPaladinSkillsEnumEnd;
		_skills = new Skill[RPGPaladinSkillsEnumEnd];
		break;
	case Barbarian:
		_maxSkillsCap = RPGBarbarianSkillsEnumEnd;
		_skills = new Skill[RPGBarbarianSkillsEnumEnd];
		break;
	case Archer:
		_maxSkillsCap = RPGArcherSkillsEnumEnd;
		_skills = new Skill[RPGArcherSkillsEnumEnd];
		break;
	case Thief:
		_maxSkillsCap = RPGThiefSkillsEnumEnd;
		_skills = new Skill[RPGThiefSkillsEnumEnd];
		break;
	case Priest:
		_maxSkillsCap = RPGPriestSkillsEnumEnd;
		_skills = new Skill[RPGPriestSkillsEnumEnd];
		break;
	case Mage:
		_maxSkillsCap = RPGMageSkillsEnumEnd;
		_skills = new Skill[RPGMageSkillsEnumEnd];
		break;
	case Summoner:
		_maxSkillsCap = RPGSummonerSkillsEnumEnd;
		_skills = new Skill[RPGSummonerSkillsEnumEnd];
		break;
	default:
		break;
	}
	_skills[0] = { SkillFunctions::Attack, 1, 0, "Attack", Attributes{Element::ElementNone, Physical::Blunt} };
	for (int i = 0; i < lvl; ++i)
		LevelUp();
}

RPGCharacter::RPGCharacter(std::string filePath)
{
	std::fstream file("Save/" + _name + ".dat", std::ios::in);
	int cls, stre, strp, wke, wkp;
	file >> _name >> cls >> _level >> _experience >>
		_nextLevelExperience >> _defense >> _maxSkills >>
		_maxSkillsCap >> _hp >> _mp >> _maxHP >>
		_maxMP >> _ferrum >> _stats.strength >> 
		_stats.stamina >> _stats.dexterity >>
		_stats.intelligence >> _stats.luck >>
		stre >> strp >> wke >> wkp;
	_class = (RPGClass)cls;
	_afin.strength.elements = (Element)stre;
	_afin.strength.phys = (Physical)strp;
	_afin.weakness.elements = (Element)wke;
	_afin.weakness.phys = (Physical)wkp;

	//Se queda hasta aqui.
	file << _head.getName() << " " << _head.getType() <<
		" " << _head.getUsage() << " " << _head.getValue() <<
		" " << _head.getDescription() << " ";
	file << _chest.getName() << " " << _chest.getType() <<
		" " << _chest.getUsage() << " " << _chest.getValue() <<
		" " << _chest.getDescription() << " ";
	file << _boots.getName() << " " << _boots.getType() <<
		" " << _boots.getUsage() << " " << _boots.getValue() <<
		" " << _boots.getDescription() << " ";
	file << _weapon.getName() << " " << _weapon.getType() <<
		" " << _weapon.getUsage() << " " << _weapon.getValue() <<
		" " << _weapon.getDescription() << " ";
	file << _inventory.size() << " ";
	for (auto &i : _inventory)
		file << i.getName() << " " << i.getType() <<
		" " << i.getUsage() << " " << i.getValue() <<
		" " << i.getDescription() << " ";
	file.close();
}

RPGCharacter::~RPGCharacter()
{
	if(_skills)
		delete[] _skills;
}

void RPGCharacter::Update()
{
	if (_experience >= _nextLevelExperience)
	{
		_experience -= _nextLevelExperience;
		LevelUp();
	}
}

void RPGCharacter::UseSkill(RPGCharacter & other, size_t skillNum)
{
	if (_skills[skillNum].mpUsage > _mp)
		return;
	other.Damage(_skills[skillNum].skillFunc(_stats, _skills[skillNum].skillPoint,
		other.GetAffinities(), _skills[skillNum].attrib));
	UseMp(_skills[skillNum].mpUsage);
}

size_t RPGCharacter::getLevel() const
{
	return _level;
}

size_t RPGCharacter::gethp() const
{
	return _hp;
}

size_t RPGCharacter::getmp() const
{
	return _mp;
}

size_t RPGCharacter::getDefense() const
{
	return _defense;
}

size_t RPGCharacter::getStrength() const
{
	return _stats.strength;
}

size_t RPGCharacter::getStamina() const
{
	return _stats.stamina;
}

size_t RPGCharacter::getDexterity() const
{
	return _stats.dexterity;
}

size_t RPGCharacter::getIntelligence() const
{
	return _stats.intelligence;
}

size_t RPGCharacter::getLuck() const
{
	return _stats.luck;
}

void RPGCharacter::EquipHead(RPGItem item)
{
	if (item.getType() == RPGItemType::Head)
		_head = RPGItem(item);
}

void RPGCharacter::EquipChest(RPGItem item)
{
	if (item.getType() == RPGItemType::Chest)
		_chest = RPGItem(item);
}

void RPGCharacter::EquipLegs(RPGItem item)
{
	if (item.getType() == RPGItemType::Legs)
		_boots = RPGItem(item);
}

void RPGCharacter::EquipWeapon(RPGItem item)
{
	if (item.getType() == RPGItemType::Weapon)
	{
		_weapon = RPGItem(item);
		_skills[0].attrib.phys = (Physical)item.getValue();
	}
}

void RPGCharacter::AddItem(RPGItem item)
{
	_inventory.push_back(item);
}

std::vector<std::string> RPGCharacter::GetItemNames() const
{
	std::vector<std::string> itemNames;
	for (auto &i : _inventory)
		itemNames.push_back(i.getName());
	return itemNames;
}

std::string RPGCharacter::GetItemDescription(size_t index) const
{
	return _inventory[index].getDescription();
}

std::vector<std::string> RPGCharacter::GetEquipmentNames() const
{
	std::vector<std::string> itemNames = { _head.getName(),_chest.getName(),_boots.getName(),_weapon.getName() };
	return itemNames;
}

std::string RPGCharacter::GetEquipmentDescription(RPGItemType index) const
{
	switch (index)
	{
	case Head:
		return _head.getDescription();
	case Chest:
		return _chest.getDescription();
	case Legs:
		return _boots.getDescription();
	case Weapon:
		return _weapon.getDescription();
	}
	return std::string();
}

void RPGCharacter::ConsumeItem(size_t index)
{
	RPGItemType t = _inventory[index].getType();
	if (t != RPGItemType::Consumable)
		return;
	switch (_inventory[index].getUsage())
	{
	case HealHP:
		Damage(0 - _inventory[index].getValue());
		break;
	case HealMP:
		UseMp(0 - _inventory[index].getValue());
		break;
	case AddStr:
		_stats.strength += _inventory[index].getValue();
		break;
	case AddStam:
		_stats.stamina += _inventory[index].getValue();
		break;
	case AddDex:
		_stats.dexterity += _inventory[index].getValue();
		break;
	case AddInt:
		_stats.intelligence += _inventory[index].getValue();
		break;
	case AddLuk:
		_stats.luck += _inventory[index].getValue();
		break;
	}
	_inventory.erase(_inventory.begin() + index, _inventory.begin() + index);
}

void RPGCharacter::AddExperience(size_t exp)
{
	_experience += exp;
}

void RPGCharacter::AddSkillPoint(size_t skillNum)
{
	++_skills[skillNum].skillPoint;
}

std::string RPGCharacter::GetSkillName(size_t skillNum)
{
	return _skills[skillNum].name;
}

size_t RPGCharacter::GetSkillAmmount()
{
	return _maxSkills;
}

void RPGCharacter::Damage(int damage)
{
	if (damage > 0)
		damage *= (1 / (float)_defense) + .3f;
	_hp -= _hp - damage <= _maxHP ? damage : _maxHP - _hp;
}

void RPGCharacter::UseMp(int mpDamage)
{
	_mp -= _mp - mpDamage <= _maxMP ? mpDamage : _maxMP - _mp;
}

int RPGCharacter::getFerrum()
{
	return _ferrum;
}

void RPGCharacter::AddFerrum(int ferrum)
{
	if ((_ferrum + ferrum) <= 0)
		return;
	_ferrum += ferrum;
}

bool RPGCharacter::isAlive()
{
	return _hp > 0;
}

std::string RPGCharacter::GetName()
{
	return _name;
}

Affinities RPGCharacter::GetAffinities()
{
	return _afin;
}

void RPGCharacter::SaveToFile()
{
	std::fstream file("Save/" + _name + ".dat", std::ios::out | std::ios::trunc);
	file << _name << " " << _class << " " <<
		_level << " " << _experience << " " << _nextLevelExperience << " " <<
		_defense << " " << _maxSkills << " " <<
		_maxSkillsCap << " " << _hp << " " << 
		_mp << " " << _maxHP << " " << _maxMP << " " <<
		_ferrum << " " << _stats.strength << " " <<
		_stats.stamina << " " << _stats.dexterity << 
		" " << _stats.intelligence << " " << 
		_stats.luck << " " << _afin.strength.elements << " " << _afin.strength.phys << " " <<
		_afin.weakness.elements << " " << 
		_afin.weakness.phys << " ";
	file << _head.getName() << " " << _head.getType() <<
		" " << _head.getUsage() << " " << _head.getValue() <<
		" " << _head.getDescription() << " ";
	file << _chest.getName() << " " << _chest.getType() <<
		" " << _chest.getUsage() << " " << _chest.getValue() <<
		" " << _chest.getDescription() << " ";
	file << _boots.getName() << " " << _boots.getType() <<
		" " << _boots.getUsage() << " " << _boots.getValue() <<
		" " << _boots.getDescription() << " ";
	file << _weapon.getName() << " " << _weapon.getType() <<
		" " << _weapon.getUsage() << " " << _weapon.getValue() <<
		" " << _weapon.getDescription() << " ";
	file << _inventory.size() << " ";
	for(auto &i : _inventory)
		file << i.getName() << " " << i.getType() <<
		" " << i.getUsage() << " " << i.getValue() <<
		" " << i.getDescription() << " ";
	file.close();
}

size_t RPGCharacter::toNextLevel()
{
	return _nextLevelExperience - _experience;
}

void RPGCharacter::LevelUp()
{
	++_level;
	for (int i = 0; i < _statsPerLevel; ++i)
	{
		int randomSelector = randomRange(0, 100);
		switch (_class)
		{
		case Warrior:
			if (randomSelector < 33)
				++_stats.strength;
			else if (randomSelector < 66)
				++_stats.stamina;
			else if (randomSelector < 75)
				++_stats.dexterity;
			else if (randomSelector < 85)
				++_stats.luck;
			else if (randomSelector < 100)
				++_stats.intelligence;
			break;
		case Paladin://stam,int,str,luk,dex
			if (randomSelector < 30)
				++_stats.stamina;
			else if (randomSelector < 60)
				++_stats.intelligence;
			else if (randomSelector < 80)
				++_stats.strength;
			else if (randomSelector < 90)
				++_stats.luck;
			else if (randomSelector < 100)
				++_stats.dexterity;
			break;
		case Barbarian://str,lck,dex,stam,int
			if (randomSelector < 50)
				++_stats.strength;
			else if (randomSelector < 70)
				++_stats.luck;
			else if (randomSelector < 80)
				++_stats.dexterity;
			else if (randomSelector < 90)
				++_stats.stamina;
			else if (randomSelector < 100)
				++_stats.intelligence;
			break;
		case Archer://dex,lck,int,str,stmn
			if (randomSelector < 33)
				++_stats.dexterity;
			else if (randomSelector < 66)
				++_stats.luck;
			else if (randomSelector < 80)
				++_stats.intelligence;
			else if (randomSelector < 90)
				++_stats.strength;
			else if (randomSelector < 100)
				++_stats.stamina;
			break;
		case Thief://lck,dex,stm,int,str
			if (randomSelector < 50)
				++_stats.luck;
			else if (randomSelector < 80)
				++_stats.dexterity;
			else if (randomSelector < 90)
				++_stats.stamina;
			else if (randomSelector < 95)
				++_stats.intelligence;
			else if (randomSelector < 100)
				++_stats.strength;
			break;
		case Priest://stm,int,lck,dex,str
			if (randomSelector < 33)
				++_stats.stamina;
			else if (randomSelector < 66)
				++_stats.intelligence;
			else if (randomSelector < 80)
				++_stats.luck;
			else if (randomSelector < 90)
				++_stats.dexterity;
			else if (randomSelector < 100)
				++_stats.strength;
			break;
		case Mage://int,lck,dex,str,stm
			if (randomSelector < 40)
				++_stats.intelligence;
			else if (randomSelector < 70)
				++_stats.luck;
			else if (randomSelector < 80)
				++_stats.dexterity;
			else if (randomSelector < 90)
				++_stats.strength;
			else if (randomSelector < 100)
				++_stats.stamina;
			break;
		case Summoner://int,dex,lck,stm,str=
			if (randomSelector < 33)
				++_stats.intelligence;
			else if (randomSelector < 60)
				++_stats.dexterity;
			else if (randomSelector < 80)
				++_stats.luck;
			else if (randomSelector < 90)
				++_stats.stamina; 
			else if (randomSelector < 100)
				++_stats.strength;
			break;
		}
	}
	_maxHP = _hp = _basehp + (10 * _stats.stamina);
	_maxMP = _mp = _basemp + (5 * _stats.intelligence);
	_maxSkills += !(_level % _skillStep) && _maxSkills < _maxSkillsCap ? 1 : 0;
	for (int i = 0; i < _skillPointsPerLevel; ++i)
		AddSkillPoint(randomRange(0, _maxSkills + 1));
}
