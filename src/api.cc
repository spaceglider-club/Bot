// this file has function definitions for cobject.h

#include "cobject.h"
#include "interface.h"
#include "macro.h"
#include "offsets.h"
#include "utils.h"
#include "api.h"
#include "vector.h"

#include <iostream>
#include <xorstr.hpp>
#include <DirectXMath.h>

void cAPI::Setup()
{
	this->GetPingOffset();
	this->GetAttackSpeedOffset();

	return;
}

// search through memory blocks until found the pointer combination (takes about 2-10 seconds depending on PC)
void cAPI::GetPingOffset()
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
void cAPI::GetAttackSpeedOffset()
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

PTR cAPI::GetLocalPlayer()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kLocalPlayer);
}

float cAPI::GetGameTime()
{
	return Interface->ReadMemory<float>(Interface->process_address + Offsets::kGameTime);
}

/* */

PTR cAPI::GetRenderer()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kRenderer);
}

Vector::Vector2<int> cAPI::GetScreenSize()
{
	return Vector::Vector2<int>
	{
		Interface->ReadMemory<int>(GetRenderer() + Offsets::kRendererWidth),
			Interface->ReadMemory<int>(GetRenderer() + Offsets::kRendererHeight)
	};
}

/* */

PTR cAPI::GetHeroList()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kHeroList);
}

PTR cAPI::GetMinionList()
{
	return Interface->ReadMemory<PTR>(Interface->process_address + Offsets::kMinionList);
}

/* */

std::string cAPI::GetChampionName(PTR address)
{
	return Interface->ReadCharPointer(address + Offsets::kChampionName);
}

float cAPI::GetAttackRange()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kAttackRange);
}

float cAPI::GetHealth(PTR address)
{
	return Interface->ReadMemory<float>(address + Offsets::kHealth);
}

float cAPI::GetAttackSpeed()
{
	return Interface->ReadMemory<float>(this->kAttackSpeedOffset);
}

int cAPI::GetPing()
{
	return Interface->ReadMemory<int>(this->kPingOffset);
}

float cAPI::GetBaseAD()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kBaseAD);
}

float cAPI::GetBonusAD()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kBonusAD);
}

float cAPI::GetTotalAD()
{
	return GetBaseAD() + GetBonusAD();
}

float cAPI::GetArmorPenetration()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kArmorPenetration);
}

float cAPI::GetLethality()
{
	return Interface->ReadMemory<float>(GetLocalPlayer() + Offsets::kLethality);
}

CObject::TEAM cAPI::GetTeam(PTR address)
{
	return Interface->ReadMemory<int>(address + Offsets::kTeam) == 100 ? CObject::TEAM::BLUE : CObject::TEAM::PURPLE;
}

float cAPI::GetArmor(PTR address)
{
	return Interface->ReadMemory<float>(address + Offsets::kArmor);
}

Vector::Vector3<float> cAPI::GetWorldPosition(PTR address)
{
	return Vector::Vector3<float>
	{
		Interface->ReadMemory<float>(address + Offsets::kPosition),
		Interface->ReadMemory<float>(address + Offsets::kPosition + 0x4),
		Interface->ReadMemory<float>(address + Offsets::kPosition + 0x8),
	};
}

Vector::Vector2<float> cAPI::GetScreenPosition()
{
	return Vector::Vector2<float>
	{
		Interface->ReadMemory<float>(GetRenderer() + Offsets::kRendererWidth),
			Interface->ReadMemory<float>(GetRenderer() + Offsets::kRendererHeight)
	};
}

/* */

bool cAPI::IsTargetable(PTR address)
{
	return Interface->ReadMemory<int>(address + Offsets::kIsTargetable) == 1 ? true : false;
}

bool cAPI::IsVisible(PTR address)
{
	return static_cast<INT8>(Interface->ReadMemory<int>(address + Offsets::kIsVisible)) == 1 ? true : false;
}

bool cAPI::IsVulnerable(PTR address)
{
	return Interface->ReadMemory<int>(address + Offsets::kIsVulnerable) == 0 ? true : false;
}

bool cAPI::IsAlive(PTR address)
{
	return GetHealth(address) > 0.0f ? true : false;
}

DirectX::XMMATRIX ReadMatrix(uintptr_t address)
{
	DirectX::XMMATRIX tempmatrix;
	for (int i = 0; i < 16; i++)
	{
		tempmatrix.r->m128_f32[i] = Interface->ReadMemory<float>(address + sizeof(float) * i);
	}
	return tempmatrix;
}

DirectX::XMMATRIX ViewMatrix()
{
	return ReadMatrix(Interface->process_address + Offsets::kViewProjectionMatrix);
}

DirectX::XMMATRIX ProjectionMatrix()
{
	return ReadMatrix(Interface->process_address + Offsets::kViewProjectionMatrix + 0x40);
}

DirectX::XMMATRIX GetViewProj()
{
	return DirectX::XMMatrixMultiply(ViewMatrix(), ProjectionMatrix());
}

Vector::Vector2<float> cAPI::GetScreenPosition(const Vector::Vector3<float>& pos)
{
	Vector::Vector2<int> screen = GetScreenSize();
	DirectX::XMMATRIX matrix = GetViewProj();
	Vector::Vector2<float> returnValue{ 0.0f, 0.0f };


	Vector::Vector4<float> cords;
	cords.x = pos.x * matrix.r->m128_f32[0] + pos.y * matrix.r->m128_f32[4] + pos.z * matrix.r->m128_f32[8] + matrix.r->m128_f32[12];
	cords.y = pos.x * matrix.r->m128_f32[1] + pos.y * matrix.r->m128_f32[5] + pos.z * matrix.r->m128_f32[9] + matrix.r->m128_f32[13];
	cords.z = pos.x * matrix.r->m128_f32[2] + pos.y * matrix.r->m128_f32[6] + pos.z * matrix.r->m128_f32[10] + matrix.r->m128_f32[14];
	cords.w = pos.x * matrix.r->m128_f32[3] + pos.y * matrix.r->m128_f32[7] + pos.z * matrix.r->m128_f32[11] + matrix.r->m128_f32[15];

	if (cords.w < 0.1f) return returnValue;

	Vector::Vector3<float> tempr;
	tempr.x = cords.x / cords.w;
	tempr.y = cords.y / cords.w;
	tempr.z = cords.z / cords.w;

	returnValue.x = (screen.x / 2 * tempr.x) + (tempr.x + screen.x / 2);
	returnValue.y = -(screen.y / 2 * tempr.y) + (tempr.y + screen.y / 2);

	return returnValue;
}

float get2ddist(Vector::Vector2<float> pos1, Vector::Vector2<float> pos2)
{
	return sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2));
}

float get3ddist(Vector::Vector3<float> pos1, Vector::Vector3<float> pos2)
{
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2) + pow(pos1.z - pos2.z, 2));
}

/*float get_screendist(uintptr_t address)
{
	return get2ddist(w2s(get_position(get_localplayer())), w2s(get_position(address)));
}

bool in_attackrange(uintptr_t address)
{
	return get3ddist(get_position(get_localplayer()), get_position(address)) < (get_attackrange() + 125) ? true : false;
}

float next_hit_dmg(float armor)
{
	float atkDamage = get_basead() + get_bonusad();
	float armorPen = get_armorpen();
	float lethality = get_lethality();
	int lvl = g_mem->rpm<int>(get_localplayer() + 0x33B4);

	float enemyArmor = (armor * armorPen) - (lethality * (0.6 + 0.4 * lvl / 18));
	float damageOnHit = atkDamage * (100 / (100 + enemyArmor));
	return damageOnHit;
}*/



cAPI* API = new cAPI();