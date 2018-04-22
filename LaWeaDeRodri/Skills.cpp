#include "HelperFunctions.h"
#include "Skills.h"
#include "RPGCharacter.h"

int SkillFunctions::Attack(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	int damage = stats.strength * 4 * ((float)1 / (2.2f / (float)skillPoints));
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
	damage *= randomRange(0, 150) < stats.luck ? 1.5f : 1;
	RPGCharacter::SetOutString("Dealt " + std::to_string(damage) + " damage.");
	return damage;
}

int SkillFunctions::IDidNotHitHer(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::Oh(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::HiMark(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::HowIsYourSexLife(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::MegalomaniumSlap(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::DiosJuzga(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::YoSeLosMando(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::SilverRain(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::PinchesFurros(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::LlamarAlComandante(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::VanishToFurZone(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::BanHammer(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::BanHammerConquest7890099(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::JerichoPunisher(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::UCantCM(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::Rko(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::ManitaDePuerco(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::GarfiasSmash(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

int SkillFunctions::Urracarrana(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib)
{
	return 0;
}

