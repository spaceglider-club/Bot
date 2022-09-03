// Has function definitions for api.h

#include "api.h"
#include "cobject.h"

void API::LoadLocalPlayer(LocalPlayer& local_player)
{
	local_player.champion_name = CObject->GetChampionName(local_player.address);
	local_player.attack_speed = CObject->GetAttackSpeed();
	local_player.total_ad = CObject->GetTotalAD();
	local_player.armor_penetration = CObject->GetTotalAD();
	local_player.lethality = CObject->GetLethality();
	local_player.ping = CObject->GetPing();
	local_player.is_alive = CObject->IsAlive(local_player.address);
	local_player.team = CObject->GetTeam(local_player.address);
	local_player.world_position = CObject->GetWorldPosition(local_player.address);
	// screen pos
}

void API::LoadEnemyPlayer(EnemyPlayer& enemy_player)
{
	enemy_player.champion_name = CObject->GetChampionName(enemy_player.address);
	enemy_player.health = CObject->GetHealth(enemy_player.address);
	enemy_player.armor = CObject->GetArmor(enemy_player.address);
	enemy_player.is_alive = CObject->IsAlive(enemy_player.address);
	enemy_player.is_targetable = CObject->IsVulnerable(enemy_player.address);
	enemy_player.is_visible = CObject->IsVisible(enemy_player.address);
	enemy_player.is_vulnerable = CObject->IsVulnerable(enemy_player.address);
	enemy_player.team = CObject->GetTeam(enemy_player.address);
	enemy_player.world_position = CObject->GetWorldPosition(enemy_player.address);
	// screen pos
}

void API::UpdateLocalPlayer(LocalPlayer& local_player)
{

}

void API::UpdateEnemyPlayer(EnemyPlayer& enemy_player)
{

}
