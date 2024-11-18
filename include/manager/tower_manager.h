#pragma once

#include "manager/manager.h"
#include "tower/tower.h"
#include "tower/tower_type.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>

class TowerManager : public Manager<TowerManager>
{
	friend class Manager<TowerManager>;

public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	double get_place_cost(TowerType type) const;

	double get_upgrade_cost(TowerType type) const;

	double get_damage_range(TowerType type) const;

	void place_tower(TowerType type, const SDL_Point& idx);

	void upgrade_tower(TowerType type);

protected:
	TowerManager() = default;

	~TowerManager() = default;

private:
	std::vector<Tower*> tower_list;
};
