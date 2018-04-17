#include "RPGCharacter.h"
#include "HelperFunctions.h"
#include "Skills.h"

Stats RPGCharacter::_classStats[RPGClass::RPGClassEnumEnd] = 
{
	//TODO: Llenar los stats iniciales.
	Stats{}, //Warrior
	Stats{}, //Paladin
	Stats{}, //Barbarian
	Stats{}, //Archer
	Stats{}, //Thief
	Stats{}, //Priest
	Stats{}, //Mage
	Stats{}, //Summoner
};

RPGCharacter::RPGCharacter(RPGClass classT, size_t lvl) : _skills(nullptr)
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
	switch (_class)
	{
		//TODO: llenar tabla de saltos
	case Warrior:
		_skills = new Skill[RPGWarriorSkillsEnumEnd];
		break;
	case Paladin:
		_skills = new Skill[RPGPaladinSkillsEnumEnd];
		break;
	case Barbarian:
		_skills = new Skill[RPGBarbarianSkillsEnumEnd];
		break;
	case Archer:
		_skills = new Skill[RPGArcherSkillsEnumEnd];
		break;
	case Thief:
		_skills = new Skill[RPGThiefSkillsEnumEnd];
		break;
	case Priest:
		_skills = new Skill[RPGPriestSkillsEnumEnd];
		break;
	case Mage:
		_skills = new Skill[RPGMageSkillsEnumEnd];
		break;
	case Summoner:
		_skills = new Skill[RPGSummonerSkillsEnumEnd];
		break;
	default:
		break;
	}
	_skills[0] = { SkillFunctions::Attack, 1, 0, "Attack", Attributes{Element::ElementNone, Physical::Blunt} };
	for (int i = 0; i < lvl; ++i)
		LevelUp();
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
		_weapon = RPGItem(item);
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

void RPGCharacter::LevelUp()
{
	++_level;
	int statPointsRemaining = 5;
	for (int i = 0; i < statPointsRemaining; ++i)
	{
		int randomSelector = randomRange(0, 100);
		switch (_class)
		{
			//TODO: asignar prioridades de stats.
		case Warrior:
			break;
		case Paladin:
			break;
		case Barbarian:
			break;
		case Archer:
			break;
		case Thief:
			break;
		case Priest:
			break;
		case Mage:
			break;
		case Summoner:
			break;
		}
	}
	//TODO: Refreshear mp y hp con respecto a los stats mas incremento base. 
	//TODO: Desbloquear habilidades a ciertos niveles en especifico.
}
