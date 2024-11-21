#include "manager/coin_manager.h"
#include "manager/config_manager.h"
#include "prop/coin_prop.h"
#include "vector/vector2.h"
#include <algorithm>

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

void CoinManager::on_update(double delta)
{
	for (auto coin_prop : coin_prop_list)
		coin_prop->on_update(delta);
		
	remove_invalid_coin_prop();
}

void CoinManager::on_render(SDL_Renderer* renderer)
{
	for (auto coin_prop : coin_prop_list)
		coin_prop->on_render(renderer);
}

void CoinManager::spawn_coin_prop(const Vector2& position)
{
	CoinProp *coin_prop = new CoinProp();
	coin_prop->set_position(position);

	coin_prop_list.push_back(coin_prop);
}

CoinManager::CoinPropList& CoinManager::get_coin_prop_list()
{
	return coin_prop_list;
}

double CoinManager::get_current_coin_num()
{
	return num_coin;
}

CoinManager::CoinManager()
{
	num_coin = ConfigManager::instance()->num_initial_coin;
}

CoinManager::~CoinManager()
{
	for (auto coin_prop : coin_prop_list)
		delete  coin_prop;
}

void CoinManager::remove_invalid_coin_prop()
{
	coin_prop_list.erase(std::remove_if(coin_prop_list.begin(), coin_prop_list.end(), 
				[&](const CoinProp* coin_prop)
				{
					bool deletebale = coin_prop->can_remove();
					if (deletebale)
						delete coin_prop;
					return deletebale;
				}), coin_prop_list.end());
}
