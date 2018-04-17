#include "Skills.h"
#include "RPGCharacter.h"

int SkillFunctions::Attack(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	int damage = stats.strength * 4 * (int)skillPoints;
	if (sourceAttrib.phys & Physical::Blunt && targetAffin.weakness.phys & Physical::Blunt)
		damage *= 1.5f;
	else if (sourceAttrib.phys & Physical::Blunt && targetAffin.strength.phys & Physical::Blunt)
		damage *= .5f;
	if (sourceAttrib.phys & Physical::Slash && targetAffin.weakness.phys & Physical::Slash)
		damage *= 1.5f;
	else if (sourceAttrib.phys & Physical::Slash && targetAffin.strength.phys & Physical::Slash)
		damage *= .5f;
	if (sourceAttrib.phys & Physical::Thrust && targetAffin.weakness.phys & Physical::Thrust)
		damage *= 1.5f;
	else if (sourceAttrib.phys & Physical::Thrust && targetAffin.strength.phys & Physical::Thrust)
		damage *= .5f;
	return damage;
}
