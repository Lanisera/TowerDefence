#pragma once

#include "animation/animation.h"
#include "enemy/enemy.h"
#include "vector/vector2.h"
#include <SDL_render.h>

#define M_PI 3.14159265358979323846

class Bullet
{
public:
	Bullet() = default;

	~Bullet() = default;
	
	void set_velocity(const Vector2& velocity);

	void set_position(const Vector2& position);

	void set_damage(double val);

	const Vector2& get_size() const;

	const Vector2& get_velocity() const;
	
	const Vector2& get_position() const;

	double get_damage() const;

	double get_damage_range() const;

	void disable_collide();

	bool can_collision() const;

	void make_invalid();

	bool can_remove() const;

	virtual void on_update(double delta);

	virtual void on_render(SDL_Renderer* renderer);

	virtual void on_collide(Enemy* enemy);

protected:
	Vector2 size;
	Vector2 position;
	Vector2 velocity;

	Animation animation;
	bool can_rotated = false;

	double damage = 0;
	double damage_range = -1;

private:
	bool is_valid = true;
	bool is_collisional = true;
	double angle_anim_rotated = 0;

};
