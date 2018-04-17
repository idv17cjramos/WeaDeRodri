#pragma once
struct Stats;
struct Affinities;
struct Attributes;
namespace SkillFunctions
{
	int Attack(Stats stats, size_t skillPoints, Affinities targetAffin, Attributes sourceAttrib);
}