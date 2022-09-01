#ifndef SPACEGLIDER_SRC_COBJECT_H_
#define SPACEGLIDER_SRC_COBJECT_H_

#pragma once

#include "macro.h"

#include <windows.h>
#include <string_view>

class cCObject
{
public:
	PTR getLocalPlayer();
	std::string GetChampionName();


	void GetAttackSpeedOffset();
	void GetPingOffset();

	PTR kPingOffset = NULL;
	PTR kAttackSpeedOffset = NULL;

};
extern cCObject* CObject;


#endif