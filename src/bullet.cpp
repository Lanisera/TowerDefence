#include "bullet/bullet.h"
#include "enemy/enemy.h"
#include "manager/config_manager.h"
#include "vector/vector2.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cmath>

void Bullet::set_velocity(const Vector2& velocity)
{
	this->velocity = velocity;

	if (can_rotated)
	{
		double radians = std::atan2(velocity.y, velocity.x);
		angle_anim_rotated = radians * 180 / M_PI;
	}
}

void Bullet::set_position(const Vector2& position)
{
	this->position = position;
}

void Bullet::set_damage(double val)
{
	damage = val;
}

const Vector2& Bullet::get_size() const
{
	return size;
}

const Vector2& Bullet::get_velocity() const
{
	return velocity;
}

const Vector2& Bullet::get_position() const
{
	return position;
}

double Bullet::get_damage() const
{
	return damage;
}

double Bullet::get_damage_range() const
{
	return damage_range;
}

void Bullet::disable_collide()
{
	is_collisional = false;
}

bool Bullet::can_collision() const
{
	return is_collisional;
}

void Bullet::make_invalid()
{
	is_valid = false;
	is_collisional = false;
}

bool Bullet::can_remove() const
{
	return !is_valid;
}

void Bullet::on_update(double delta)
{
	animation.on_update(delta);
	position += velocity * delta;

	static SDL_Rect rect_tile_map =
		ConfigManager::instance()->rect_tile_map;

	if (position.x - size.x / 2 <= rect_tile_map.x
			|| position.x + size.x / 2 >= rect_tile_map.x + rect_tile_map.w
			|| position.y - size.y / 2 <= rect_tile_map.y
			|| position.y + size.y / 2 >= rect_tile_map.y + rect_tile_map.h)
	{
		is_valid = false;
	}
}

void Bullet::on_render(SDL_Renderer* renderer)
{
	static SDL_Point point;

	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);

	animation.on_render(renderer, point, angle_anim_rotated);
}

void Bullet::on_collide(Enemy* enemy)
{
	make_invalid();
}
