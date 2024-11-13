#pragma once

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

protected:
	EnemyManager() = default;

	~EnemyManager();

private:
	EnemyList enemy_list;

private:
	void process_home_collision();

	void process_bullet_collision();

	void remove_invalid_enemy();

};
