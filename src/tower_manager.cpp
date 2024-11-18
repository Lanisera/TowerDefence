#include "manager/tower_manager.h"
#include "manager/config_manager.h"
#include "manager/resources_manager.h"
#include "map/tile.h"
#include "tower/tower.h"
#include "tower/tower_type.h"
#include "tower/archer_tower.h"
#include "tower/axeman_tower.h"
#include "tower/gunner_tower.h"
#include "vector/vector2.h"
#include <SDL_mixer.h>

void TowerManager::on_update(double delta)
{
	for (auto tower : tower_list)
		tower->on_update(delta);
}

void TowerManager::on_render(SDL_Renderer* renderer)
{
	for (auto tower : tower_list)
		tower->on_render(renderer);
}

double TowerManager::get_place_cost(TowerType type) const
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type) 
	{
	case TowerType::Archer:
		return instance->archer_template.cost[instance->level_archer];
		break;
	case TowerType::Axeman:
		return instance->axeman_template.cost[instance->level_axeman];
		break;
	case TowerType::Gunner:
		return instance->gunner_template.cost[instance->level_gunner];
		break;
	}

	return 0;
}

double TowerManager::get_upgrade_cost(TowerType type) const
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type) 
	{
	case TowerType::Archer:
		return instance->level_archer == 9 ? -1 : instance->archer_template.upgrade_cost[instance->level_archer];
		break;
	case TowerType::Axeman:
		return instance->level_axeman == 9 ? -1 : instance->axeman_template.upgrade_cost[instance->level_axeman];
		break;
	case TowerType::Gunner:
		return instance->level_gunner == 9 ? -1 : instance->gunner_template.upgrade_cost[instance->level_gunner];
		break;
	}

	return 0;
}

double TowerManager::get_damage_range(TowerType type) const
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type) 
	{
	case TowerType::Archer:
		return instance->archer_template.view_range[instance->level_archer];
		break;
	case TowerType::Axeman:
		return instance->axeman_template.view_range[instance->level_axeman];
		break;
	case TowerType::Gunner:
		return instance->gunner_template.view_range[instance->level_gunner];
		break;
	}

	return 0;
}

void TowerManager::place_tower(TowerType type, const SDL_Point& idx)
{
	Tower* tower = nullptr;

	switch (type) 
	{
	case TowerType::Archer:
		tower = new ArcherTower();
		break;
	case TowerType::Axeman:
		tower = new AxemanTower();
		break;
	case TowerType::Gunner:
		tower = new GunnerTower();
		break;
	default:
		tower = new ArcherTower();
		break;
	}

	static Vector2 position;
	static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;

	position.x = rect_tile_map.x + idx.x * SIZE_TILE + SIZE_TILE / 2;
	position.y = rect_tile_map.y + idx.y * SIZE_TILE + SIZE_TILE / 2;

	tower->set_position(position);
	tower_list.push_back(tower);

	ConfigManager::instance()->map.place_tower(idx);

	static const ResourcesManager::SoundPool& sound_pool =
		ResourcesManager::instance()->get_sound_pool();

	Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_PlaceTower)->second, 0);
	
}

void TowerManager::upgrade_tower(TowerType type)
{
	static ConfigManager* instance = ConfigManager::instance();

	switch (type) 
	{
	case TowerType::Archer:
		instance->level_archer = instance->level_archer >= 9 ? 9 : instance->level_archer + 1;
		break;
	case TowerType::Axeman:
		instance->level_axeman = instance->level_axeman >= 9 ? 9 : instance->level_axeman + 1;
		break;
	case TowerType::Gunner:
		instance->level_gunner = instance->level_gunner >= 9 ? 9 : instance->level_gunner + 1;
		break;
	}

	static const ResourcesManager::SoundPool& sound_pool =
		ResourcesManager::instance()->get_sound_pool();

	Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_TowerLevelUp)->second, 0);
}
