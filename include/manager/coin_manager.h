#pragma once

#include "manager/manager.h"
#include "prop/coin_prop.h"
#include <SDL_render.h>
#include <vector>

class CoinManager : public Manager<CoinManager>
{
	friend class Manager<CoinManager>;
public:
	using CoinPropList = std::vector<CoinProp*>;

public:
	void increase_coin(double val);

	void decrease_coin(double val);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void spawn_coin_prop(const Vector2& position);
		
	CoinPropList& get_coin_prop_list();

	double get_current_coin_num();
	
protected:
	CoinManager();

	~CoinManager();

private:
	double num_coin = 0;

	CoinPropList coin_prop_list;

private:
	void remove_invalid_coin_prop();
};
