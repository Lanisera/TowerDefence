#include "manager/enemy_manager.h"
#include "manager/config_manager.h"
#include "manager/home_manager.h"
#include "map/tile.h"
#include "vector/vector2.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <algorithm>

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
