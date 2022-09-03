#ifndef SPACEGLIDER_SRC_COBJECT_H_
#define SPACEGLIDER_SRC_COBJECT_H_

#pragma once

#include "macro.h"
#include "vector.h"

#include <xorstr.hpp>
#include <string>

namespace CObject
{
	enum TEAM
	{
		UNKNOWN = 0,
		BLUE = 1,
		PURPLE = 2
	};

	class LocalPlayer
	{
	public:

		__inline LocalPlayer(PTR x) : address(x) {};
		__inline LocalPlayer() {};

		PTR address = 0x0;
		std::string champion_name = xorstr_("");
		float attack_speed = 0.0f;
		float total_ad = 0.0f;
		float armor_penetration = 0.0f;
		float lethality = 0.0f;
		int ping = 0;
		bool is_alive = false;
		TEAM team = TEAM::UNKNOWN;
		Vector::Vector3<float> world_position = { 0.0f, 0.0f, 0.0f };
		Vector::Vector2<float> screen_position = { 0.0f, 0.0f };
	};

	// For the sole purpose of performance, we are not using
	// UnknownPlayer or AllyPlayer, only EnemyPlayer

	class EnemyPlayer
	{
	public:
		__inline EnemyPlayer(PTR x) : address(x) {};

		PTR address = 0x0;
		std::string champion_name = xorstr_("");
		float health = 0.0f;
		float armor = 0.0f;
		bool is_alive = false;
		bool is_targetable = false;
		bool is_visible = false;
		bool is_vulnerable = false;
		TEAM team = TEAM::UNKNOWN;
		Vector::Vector3<float> world_position = { 0.0f, 0.0f, 0.0f };
		Vector::Vector2<float> screen_position = { 0.0f, 0.0f };
	};

	void LoadLocalPlayer(LocalPlayer& local_player);
	void LoadEnemyPlayer(EnemyPlayer& enemy_player);

	void UpdateLocalPlayer(LocalPlayer& local_player);
	void UpdateEnemyPlayer(EnemyPlayer& enemy_player);

}

#endif