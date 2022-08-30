#ifndef SPACEGLIDER_SRC_OFFSETS_H_
#define SPACEGLIDER_SRC_OFFSETS_H_

#pragma once

#include "macro.h"

namespace Offsets
{
	// Main Constants

	inline constexpr PTR kLocalPlayer			= 0x3118DDC;
	inline constexpr PTR kViewProjectionMatrix	= 0x3148A20;
	inline constexpr PTR kGameTime				= 0x3111E68;

	// Renderer Constants

	inline constexpr PTR kRenderer				= 0x314B90C;
	inline constexpr PTR kRendererWidth			= 0x8;
	inline constexpr PTR kRendererHeight		= 0xC;

	// List Constants

	inline constexpr PTR kHeroList				= 0x187BF54;
	inline constexpr PTR kMinionList			= 0x24C9788;

	// Champion Constants

	inline constexpr PTR kChampionName			= 0x2BD4;
	inline constexpr PTR kAttackRange			= 0x139C;
	inline constexpr PTR kHealth				= 0xE74;
	inline constexpr PTR kBaseAD				= 0x1354;
	inline constexpr PTR kBonusAD				= 0x12CC;
	inline constexpr PTR kArmorPenetration		= 0x1274;
	inline constexpr PTR kLethality				= 0x128C;
	inline constexpr PTR kIsTargetable			= 0xD04;
	inline constexpr PTR kIsVisible				= 0x274;
	inline constexpr PTR kIsVulnerable			= 0x3D4;
	inline constexpr PTR kTeam					= 0x34;
	inline constexpr PTR kPosition				= 0x1DC;
	inline constexpr PTR kArmor					= 0x137C;
};




#endif