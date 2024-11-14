#include "map/route.h"
#include "map/tile.h"
#include "vector/vector2.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <enemy/enemy.h>
#include <manager/config_manager.h>

#include <iostream>

Enemy::Enemy()
{
	timer_skill.set_one_shot(false);
	timer_skill.set_on_timeout([&]() { on_skill_released(this); });

	timer_sketch.set_one_shot(true);
	timer_sketch.set_wait_time(0.075);
	timer_sketch.set_on_timeout([&]() { is_show_sketch = false; });

	timer_restore_speed.set_one_shot(true);
	timer_restore_speed.set_on_timeout([&]() { speed = max_speed;});
}

void Enemy::on_update(double delta)
{
	timer_skill.on_update(delta);
	timer_sketch.on_update(delta);
	timer_restore_speed.on_update(delta);
	
	Vector2 move_distance = velocity * delta;
	Vector2 target_distance = position_target - position;
	position += move_distance < target_distance ? move_distance : target_distance;

	if ((position_target - position).approx_zero())
	{
		idx_target++;
		refresh_target_position();

		direction = (position_target - position).normalize();

	}

	velocity = direction * speed * SIZE_TILE;

	bool is_show_x_anim = abs(direction.x) > abs(direction.y);
	
	if (is_show_sketch)
	{
		if (is_show_x_anim)
			anim_current = direction.x > 0 ? &anim_sketch_right : &anim_sketch_left;
		else
			anim_current = direction.y > 0 ? &anim_sketch_down : &anim_sketch_up;
	}
	else
	{
		if (is_show_x_anim)
			anim_current = direction.x > 0 ? &anim_right : &anim_left;
		else
			anim_current = direction.y > 0 ? &anim_down : & anim_up;
	}

	anim_current->on_update(delta);
}

void Enemy::on_render(SDL_Renderer* renderer)
{
	static SDL_Rect rect;
	static SDL_Point point;
	static const int offset_y = 2;
	static const Vector2 size_hp_bar = {40, 8};
	static const SDL_Color color_border = {116, 185, 124, 255};
	static const SDL_Color color_content = {226, 255, 194, 255};

	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);

	anim_current->on_render(renderer, point);

	if (hp < max_hp)
	{
		rect.x = (int)(position.x - size_hp_bar.x / 2);
		rect.y = (int)(position.y - size.y / 2 - size_hp_bar.y - offset_y);
		rect.w = (int)(size_hp_bar.x * (hp / max_hp));
		rect.h = (int)size_hp_bar.y;
		
		SDL_SetRenderDrawColor(renderer, color_content.r, color_content.g, color_content.b, color_content.a);
		SDL_RenderFillRect(renderer, &rect);

		rect.w = (int)size_hp_bar.x;
		SDL_SetRenderDrawColor(renderer, color_border.r, color_border.g, color_border.b, color_border.a);
		SDL_RenderDrawRect(renderer, &rect);
	}

}

void Enemy::set_on_skill_released(SkillCallBack on_skill_released)
{
	this->on_skill_released = on_skill_released;
}

void Enemy::increase_hp(double val)
{
	hp += val;

	if (hp > max_hp)
	{
		hp = max_hp;
	}
}

void Enemy::decrease_hp(double val)
{
	hp -= val;

	if (hp <= 0)
	{
		hp = 0;
		is_valid = false;
	}

	is_show_sketch = true;
	timer_sketch.restart();
}

void Enemy::slow_down()
{
	speed = max_speed - 0.5;
	timer_restore_speed.set_wait_time(1);
	timer_restore_speed.restart();

}

void Enemy::set_position(Vector2& vec)
{
	this->position = vec;
}

void Enemy::set_route(const Route* route)
{
	this->route = route;

	refresh_target_position();
}

void Enemy::make_invalid()
{
	is_valid = false;
}

double Enemy::get_hp() const
{
	return hp;
}

const Vector2& Enemy::get_size() const
{
	return size;
}

const Vector2& Enemy::get_position() const
{
	return position;
}

const Vector2& Enemy::get_velocity() const
{
	return velocity;
}

double Enemy::get_damage() const
{
	return damage;
}

double Enemy::get_reward_ratio() const
{
	return reward_ratio;
}

double Enemy::get_recover_radius() const
{
	return SIZE_TILE * recover_range;
}

double Enemy::get_recover_intensity() const
{
	return recover_intensity;
}

bool Enemy::can_remove() const
{
	return !is_valid;
}

double Enemy::get_route_progress() const
{
	if (route->get_route().size() == 1)
		return 1;

	return (double)idx_target / (route->get_route().size() - 1);

}

void Enemy::refresh_target_position()
{
	const Route::IdxList& idx_list = route->get_route();

	if (idx_target < idx_list.size())
	{
		const SDL_Point& point = idx_list[idx_target];
		const static SDL_Rect& rect_tile_map = ConfigManager::instance()->rect_tile_map;

		position_target.x = rect_tile_map.x + point.x * SIZE_TILE + SIZE_TILE / 2;
		position_target.y = rect_tile_map.y + point.y * SIZE_TILE + SIZE_TILE / 2;
	}
}
