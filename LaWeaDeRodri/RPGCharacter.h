#pragma once
#include <string>
#include <vector>
#include "Definitions.h"
#include "RPGItem.h"

struct Skill;
struct Attributes;
struct Affinities;
struct Stats;

typedef int(*AttackSkill)(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib);

typedef struct Attributes {
	Element elements;
	Physical phys;
}Attributes;

typedef struct Affinities {
	Attributes weakness,
		strength;
}Affinities;

typedef struct Stats {
	size_t	strength,
			stamina,
			dexterity,
			intelligence,
			luck;
}Stats;

typedef struct Skill {
	AttackSkill skillFunc;
	size_t skillPoint;
	int mpUsage;
	std::string name;
	Attributes attrib;
}Skill;

class RPGCharacter
{
public:
	RPGCharacter(RPGClass classT, size_t lvl);
	~RPGCharacter();
	void Update();
	void UseSkill(RPGCharacter& other, size_t skillNum);
	size_t getLevel() const;
	size_t gethp() const;
	size_t getmp() const;
	size_t getDefense() const;
	size_t getStrength() const;
	size_t getStamina() const;
	size_t getDexterity() const;
	size_t getIntelligence() const;
	size_t getLuck() const;
	void EquipHead(RPGItem item);
	void EquipChest(RPGItem item);
	void EquipLegs(RPGItem item);
	void EquipWeapon(RPGItem item);
	void AddItem(RPGItem item);
	std::vector<std::string> GetItemNames() const;
	std::string GetItemDescription(size_t index) const;
	std::vector<std::string> GetEquipmentNames() const;
	std::string GetEquipmentDescription(RPGItemType index) const;
	void ConsumeItem(size_t index);
	void AddExperience(size_t exp);
	void AddSkillPoint(size_t skillNum);
	std::string GetSkillName(size_t skillNum);
	size_t GetSkillAmmount();
	void Damage(int damage);
	void UseMp(int mpDamage);
	bool isAlive();
	std::string GetName();
	Affinities GetAffinities();
private:
	size_t	_level,
			_experience,
			_nextLevelExperience,
			_defense,
			_maxSkills,
			_hpBaseIncrement,
			_mpBaseIncrement;
	int		_hp,
			_mp,
			_maxHP,
			_maxMP;
	Stats _stats;
	RPGClass _class;
	Skill *_skills;
	std::string _name;
	Affinities _afin;
	RPGItem _head,
			_chest,
			_boots,
			_weapon;
	std::vector<RPGItem> _inventory;
	void LevelUp();
	const int _baseDefense = 5, _basehp = 20, _basemp = 5;
	static Stats _classStats[RPGClass::RPGClassEnumEnd];
};

