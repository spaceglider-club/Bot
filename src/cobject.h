#ifndef SPACEGLIDER_SRC_COBJECT_H_
#define SPACEGLIDER_SRC_COBJECT_H_

#pragma once

#include "macro.h"
#include "api.h"
#include "vector.h"

#include <windows.h>
#include <string_view>

class cCObject
{
public:
	void Setup();

	PTR GetLocalPlayer();
	float GetGameTime();

	PTR GetRenderer();
	Vector::Vector2<int> GetScreenSize();

	PTR GetHeroList();
	PTR GetMinionList();

	std::string GetChampionName(PTR address);
	float GetAttackRange();
	float GetHealth(PTR address);
	float GetAttackSpeed();
	int GetPing();
	float GetBaseAD();
	float GetBonusAD();
	float GetTotalAD();
	float GetArmorPenetration();
	float GetLethality();
	API::TEAM GetTeam(PTR address);
	float GetArmor(PTR address);
	Vector::Vector3<float> GetWorldPosition(PTR address);
	Vector::Vector2<float> GetScreenPosition();


	bool IsTargetable(PTR address);
	bool IsVisible(PTR address);
	bool IsVulnerable(PTR address);
	bool IsAlive(PTR address);





	void GetAttackSpeedOffset();
	void GetPingOffset();

	PTR kPingOffset = NULL;
	PTR kAttackSpeedOffset = NULL;

};
extern cCObject* CObject;


#endif