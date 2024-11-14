#include "manager/coin_manager.h"
#include "manager/config_manager.h"

CoinManager::CoinManager()
{
	num_coin = ConfigManager::instance()->num_initial_coin;
}

void CoinManager::increase_coin(double val)
{
	num_coin += val;
}

void CoinManager::decrease_coin(double val)
{
	num_coin -= val;

	if (num_coin <= 0)
	{
		num_coin = 0;
	}
}
