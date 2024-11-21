#pragma once

#include "enemy/enemy_type.h"
#include "manager/manager.h"
#include "enemy/enemy.h"
#include <SDL_render.h>

class EnemyManager : public Manager<EnemyManager>
{
	friend class Manager<EnemyManager>;
public:
	using EnemyList = std::vector<Enemy*>;

public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void spawn_enemy(EnemyType type, int spawn_point);

	bool check_cleared() const;

	EnemyList& get_enemy_list();

protected:
	EnemyManager() = default;

	~EnemyManager();

private:
	EnemyList enemy_list;

private:
	void process_home_collision();

	void process_bullet_collision();

	void remove_invalid_enemy();

	void try_spawn_coin_prop(const Vector2& position, double ratio);

};
