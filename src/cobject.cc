// this file has function definitions for cobject.h

#include "cobject.h"
#include "interface.h"
#include "macro.h"
#include "offsets.h"
#include "utils.h"
#include "api.h"
#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <xorstr.hpp>

void cCObject::Setup()
{
	this->GetPingOffset();
	this->GetAttackSpeedOffset();

	return;
}

// search through memory blocks until found the pointer combination (takes about 2-10 seconds depending on PC)
void cCObject::GetPingOffset()
{
	for (int i = 0x0; i < 0xBFFFFFF; i += 0x4000)
	{
		// init static buffer, else compiler complains
		static PTR buffer[0x4000];
		
		// set buffer to null
		ZeroMemory(buffer, sizeof(buffer));

		// read next 0x4000 addresses from i
#pragma warning( push )
#pragma warning( disable : 6387 )
		ReadProcessMemory(Interface->process_handle, (PVOID)i, &buffer, sizeof(buffer), NULL);
#pragma warning( pop )

		for (int j = 0; j < 0x4000; j++)
		{
			// check if address ends with DB0 and the one after it with DC4
			if (static_cast<int>(buffer[j] & 0x0fff) == 3504 && static_cast<int>(buffer[j + 1] & 0x0fff) == 3524)
			{
				// if it does we got the ping offset (ofc - 0x24 cuz dats where i was first found)
				this->kPingOffset = (i + (j * 4)) - 0x24;
				return;
			}
		}
	}
}

// search through memory blocks until found the pointer combination (takes about 2-10 seconds depending on PC)
void cCObject::GetAttackSpeedOffset()
{
    for (int i = 0x00000000; i < 0xFFFFFFFF; i += 0x4000)
    {
        static PTR buffer[16384];
		ZeroMemory(buffer, 0x4000);
#pragma warning( push )
#pragma warning( disable : 6387 )
        ReadProcessMemory(Interface->process_handle, (PVOID)i, &buffer, 16384, 0);
#pragma warning( pop )
        for (int j = 0; j < 0x4000; j++)
        {
            if (static_cast<int>(buffer[j] & 0x0ff) == 186)
            {
				if (strcmp(Interface->ReadCharPointer((i + ((j - 3) * 4))).c_str(), xorstr_("game_DynamicMenuText_[Attributes]_AttackSpeedWithRatio")) == 0)
				{
					if (strcmp(Interface->ReadCharPointer((i + ((j + 62) * 4))).c_str(), xorstr_("game_DynamicMenuText_[Attributes]_LifeSteal")) == 0)
					{
						this->kAttackSpeedOffset = (i + (j * 4)) - 0x14;
						return;
					}
				}
            }
        }
    }
}

PTR cCObject::GetLocalPlayer()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kLocalPlayer);
}

float cCObject::GetGameTime()
{
	return Interface->ReadMemory<float>(Interface->process_address + Offsets::kGameTime);
}

/* */

PTR cCObject::GetRenderer()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kRenderer);
}

Vector::Vector2<int> cCObject::GetScreenSize()
{
	return Vector::Vector2<int>
	{
		Interface->ReadMemory<int>(GetRenderer() + Offsets::kRendererWidth),
		Interface->ReadMemory<int>(GetRenderer() + Offsets::kRendererHeight)
	};
}

/* */

PTR cCObject::GetHeroList()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kHeroList);
}

PTR cCObject::GetMinionList()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kMinionList);
}

/* */

std::string cCObject::GetChampionName(PTR address)
{
	return Interface->ReadCharPointer(address + Offsets::kChampionName);
}

float cCObject::GetAttackRange()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kAttackRange);
}

float cCObject::GetHealth(PTR address)
{
	return Interface->ReadMemory<float>(address + Offsets::kHealth);
}

float cCObject::GetBaseAD()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kBaseAD);
}

float cCObject::GetBonusAD()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kBonusAD);
}

float cCObject::GetTotalAD()
{
	return GetBaseAD() + GetBonusAD();
}

float cCObject::GetArmorPenetration()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kArmorPenetration);
}

float cCObject::GetLethality()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kLethality);
}

API::TEAM cCObject::GetTeam(PTR address)
{
	return Interface->ReadMemory<int>(address + Offsets::kTeam) == 100 ? API::TEAM::BLUE : API::TEAM::PURPLE;
}

float cCObject::GetArmor(PTR address)
{
	return Interface->ReadMemory<float>(address + Offsets::kArmor);
}

Vector::Vector3<float> cCObject::GetWorldPosition(PTR address)
{
	return Vector::Vector3<float>
	{
		Interface->ReadMemory<float>(address + Offsets::kPosition),
		Interface->ReadMemory<float>(address + Offsets::kPosition + 0x4),
		Interface->ReadMemory<float>(address + Offsets::kPosition + 0x8),
	};
}

Vector::Vector2<float> cCObject::GetScreenPosition()
{
	return {};
}

/* */

bool cCObject::IsTargetable(PTR address)
{
	return Interface->ReadMemory<int>(address + Offsets::kIsTargetable) == 1 ? true : false;
}

bool cCObject::IsVisible(PTR address)
{
	return static_cast<INT8>(Interface->ReadMemory<int>(address + Offsets::kIsVisible)) == 1 ? true : false;
}

bool cCObject::IsVulnerable(PTR address)
{
	return Interface->ReadMemory<int>(address + Offsets::kIsVulnerable) == 0 ? true : false;
}

bool cCObject::IsAlive(PTR address)
{
	return GetHealth(address) > 0.0f ? true : false;
}






cCObject* CObject = new cCObject();