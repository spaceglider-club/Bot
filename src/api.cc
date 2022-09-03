// Has function definitions for api.h

#include "api.h"
#include "cobject.h"

void API::LoadLocalPlayer(LocalPlayer& local_player)
{
	local_player.champion_name = CObject->GetChampionName(local_player.address);
	local_player.total_ad = CObject->GetTotalAD();
}

void API::LoadEnemyPlayer(EnemyPlayer& enemy_player)
{

}

void API::UpdateLocalPlayer(LocalPlayer& local_player)
{

}

void API::UpdateEnemyPlayer(EnemyPlayer& enemy_player)
{

}
