#include "manager/enemy_manager.h"
#include "enemy/enemy.h"
#include "enemy/enemy_type.h"
#include "manager/config_manager.h"
#include "manager/home_manager.h"
#include "map/route.h"
#include "map/tile.h"
#include "vector/vector2.h"
#include "enemy/slim_enemy.h"
#include "enemy/king_slim_enemy.h"
#include "enemy/goblin_enemy.h"
#include "enemy/goblin_priest_enemy.h"
#include "enemy/skeleton_enemy.h"

#include <SDL_rect.h>
#include <SDL_render.h>
#include <algorithm>
#include <iostream>

void EnemyManager::on_update(double delta)
{
	for (auto enemy : enemy_list)
		enemy->on_update(delta);

	process_home_collision();
	process_bullet_collision();

	remove_invalid_enemy();
}

void EnemyManager::on_render(SDL_Renderer* renderer)
{
	for (auto enemy : enemy_list)
		enemy->on_render(renderer);

}

void EnemyManager::spawn_enemy(EnemyType type, int spawn_point)
{
	static const Map::SpawnerRoutePool& spawner_route_pool = 
		ConfigManager::instance()->map.get_spawner_route_pool();

	const auto& it = spawner_route_pool.find(spawn_point);
	if (it == spawner_route_pool.end())
		return ;

	Enemy* enemy = nullptr;
	switch (type) 
	{
	case EnemyType::Slim:
		enemy = new SlimEnemy();
		break;
	case EnemyType::KingSlim:
		enemy = new KingSlimEnemy();
		break;
	case EnemyType::Goblin:
		enemy = new GoblinEnemy();
		break;
	case EnemyType::GoblinPriest:
		enemy = new GoblinPriestEnemy();
		break;
	case EnemyType::Skeleton:
		enemy = new SkeletonEnemy();
		break;
	default:
		enemy = new SlimEnemy();
		break;
	}
	
	enemy->set_on_skill_released([&](Enemy* enemy_src)
			{
				double recover_radius = enemy_src->get_recover_radius();
				if (recover_radius < 0)
					return ;

				const Vector2& pos_src = enemy_src->get_position();
				for (const auto enemy_dst : enemy_list)
				{
					const Vector2& pos_dst = enemy_dst->get_position();
					double distance = (pos_dst - pos_src).length();
					if (distance <= recover_radius)
						enemy_dst->increase_hp(enemy_src->get_recover_intensity());
				}
			});

	static const SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;
	const Route::IdxList& idx_list = it->second.get_route();
	 
	static Vector2 position;
	position.x = rect_tile_map.x + idx_list[0].x * SIZE_TILE + SIZE_TILE / 2;
	position.y = rect_tile_map.y + idx_list[0].y * SIZE_TILE + SIZE_TILE / 2;

	enemy->set_position(position);
	enemy->set_route(&it->second);

	enemy_list.push_back(enemy);
	
}

bool EnemyManager::check_cleared() const
{
	return enemy_list.empty();
}

EnemyManager::~EnemyManager()
{
	for (auto enemy : enemy_list)
		delete enemy;
}

void EnemyManager::process_home_collision()
{
	static const SDL_Point& idx_home = ConfigManager::instance()->map.get_idx_home();
	static const SDL_Rect& rect = ConfigManager::instance()->rect_tile_map;
	static const Vector2 home_position = 
	{
		(double)rect.x + idx_home.x * SIZE_TILE,
		(double)rect.y + idx_home.y * SIZE_TILE
	};

	for (auto enemy : enemy_list) 
	{
		if (enemy->can_remove())
			continue;

		const Vector2& position = enemy->get_position();
		if (position.x >= home_position.x &&
				position.y >= home_position.y &&
				position.x <= home_position.x + SIZE_TILE &&
				position.y <= home_position.y + SIZE_TILE)
		{
			enemy->make_invalid();

			HomeManager::instance()->decrease_hp(enemy->get_damage());
		}
	}
}

void EnemyManager::process_bullet_collision()
{

}

void EnemyManager::remove_invalid_enemy()
{
	enemy_list.erase(std::remove_if(enemy_list.begin(), enemy_list.end(), [](const Enemy* enemy) {
					bool deletebale = enemy->can_remove();
					if (deletebale) delete enemy;
					return deletebale;
				}), enemy_list.end());
}
