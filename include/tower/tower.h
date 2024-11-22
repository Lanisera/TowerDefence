#pragma once

#include "animation/animation.h"
#include "enemy/enemy.h"
#include "tower/tower_type.h"
#include "vector/vector2.h"
#include "bullet/bullet_type.h"
#include "direction/facing.h"
#include <SDL_render.h>

class Tower
{
public:
	Tower();

	~Tower() = default;
	
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_position(const Vector2& position);

	const Vector2& get_size() const;

	const Vector2& get_position() const;

public:
	// for debug
	std::string name = "empty";

protected:
	Vector2 size;

	Animation anim_idle_up;
	Animation anim_idle_down;
	Animation anim_idle_left;
	Animation anim_idle_right;
	Animation anim_fire_up;
	Animation anim_fire_down;
	Animation anim_fire_left;
	Animation anim_fire_right;

	TowerType tower_type = TowerType::Archer;

	double fire_speed = 0;
	BulletType bullet_type = BulletType::Arrow;

private:
	void update_idle_animation();

	void update_fire_animation();

	Enemy* get_target_enemy();

	void on_fire();

private:
	Timer timer_fire;
	Vector2 position;
	bool can_fire = true;
	Facing facing = Facing::Right;
	Animation* anim_current = &anim_idle_right;
};
