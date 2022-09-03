// Has function definitions for api.h

#include "cobject.h"
#include "api.h"


void CObject::LoadLocalPlayer(LocalPlayer& local_player)
{
	local_player.champion_name = API->GetChampionName(local_player.address);
	local_player.attack_speed = API->GetAttackSpeed();
	local_player.total_ad = API->GetTotalAD();
	local_player.armor_penetration = API->GetTotalAD();
	local_player.lethality = API->GetLethality();
	local_player.ping = API->GetPing();
	local_player.is_alive = API->IsAlive(local_player.address);
	local_player.team = API->GetTeam(local_player.address);
	local_player.world_position = API->GetWorldPosition(local_player.address);
	local_player.screen_position = API->GetScreenPosition(local_player.world_position);
}

void CObject::LoadEnemyPlayer(EnemyPlayer& enemy_player)
{
	enemy_player.champion_name = API->GetChampionName(enemy_player.address);
	enemy_player.health = API->GetHealth(enemy_player.address);
	enemy_player.armor = API->GetArmor(enemy_player.address);
	enemy_player.is_alive = API->IsAlive(enemy_player.address);
	enemy_player.is_targetable = API->IsVulnerable(enemy_player.address);
	enemy_player.is_visible = API->IsVisible(enemy_player.address);
	enemy_player.is_vulnerable = API->IsVulnerable(enemy_player.address);
	enemy_player.team = API->GetTeam(enemy_player.address);
	enemy_player.world_position = API->GetWorldPosition(enemy_player.address);
	enemy_player.screen_position = API->GetScreenPosition(enemy_player.world_position);
}

void CObject::UpdateLocalPlayer(LocalPlayer& local_player)
{

}

void CObject::UpdateEnemyPlayer(EnemyPlayer& enemy_player)
{

}
