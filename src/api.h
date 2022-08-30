#ifndef SPACEGLIDER_SRC_API_H_
#define SPACEGLIDER_SRC_API_H_

#pragma once

#include "macro.h"
#include "vector.h"

#include <string>

namespace API
{
	enum TEAM
	{
		UNKNOWN = 0,
		PURPLE	= 1,
		RED		= 2
	};

	struct LocalPlayer
	{
		PTR address								= 0x0;
		float attack_speed						= 0.0f;
		float total_ad							= 0.0f;
		float armor_penetration					= 0.0f;
		float lethality							= 0.0f;
		bool is_alive							= false;
		TEAM team								= TEAM::UNKNOWN;
		Vector::Vector3<float> world_position	= { 0.0f, 0.0f, 0.0f };
		Vector::Vector2<float> screen_position	= { 0.0f, 0.0f };
	};

	// For the sole purpose of performance, we are not using
	// UnknownPlayer or AllyPlayer, only EnemyPlayer

	struct EnemyPlayer
	{
		PTR address								= 0x0;
		std::string champion_name				= "";
		float health							= 0.0f;
		float armor								= 0.0f;
		bool is_alive							= false;
		bool is_targetable						= false;
		bool is_visible							= false;
		bool is_vulnerable						= false;
		TEAM team								= TEAM::UNKNOWN;
		Vector::Vector3<float> world_position	= { 0.0f, 0.0f, 0.0f };
		Vector::Vector2<float> screen_position	= { 0.0f, 0.0f };
	};

	void LoadLocalPlayer(LocalPlayer &local_player);
	void LoadEnemyPlayer(EnemyPlayer &enemy_player);

	void UpdateLocalPlayer(LocalPlayer& local_player);
	void UpdateEnemyPlayer(EnemyPlayer& enemy_player);

}

#endif