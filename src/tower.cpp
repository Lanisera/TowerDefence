#include "tower/tower.h"
#include "direction/facing.h"
#include "enemy/enemy.h"
#include "manager/config_manager.h"
#include "manager/enemy_manager.h"
#include "manager/resources_manager.h"
#include "map/tile.h"
#include "tower/tower_type.h"
#include "vector/vector2.h"
#include "manager/bullet_manager.h"
#include <SDL_mixer.h>
#include <SDL_rect.h>
#include <SDL_render.h>

Tower::Tower()
{
	timer_fire.set_one_shot(true);
	timer_fire.set_on_timeout([&]()
			{
				can_fire = true;
			});

	anim_idle_up.set_loop(true);
	anim_idle_up.set_interval(0.2);
	anim_idle_down.set_loop(true);
	anim_idle_down.set_interval(0.2);
	anim_idle_left.set_loop(true);
	anim_idle_left.set_interval(0.2);
	anim_idle_right.set_loop(true);
	anim_idle_right.set_interval(0.2);

	anim_fire_up.set_loop(false);
	anim_fire_up.set_interval(0.2);
	anim_fire_up.set_on_finished([&]()
			{
				update_idle_animation();
			});
	anim_fire_down.set_loop(false);
	anim_fire_down.set_interval(0.2);
	anim_fire_down.set_on_finished([&]()
			{
				update_idle_animation();
			});
	anim_fire_left.set_loop(false);
	anim_fire_left.set_interval(0.2);
	anim_fire_left.set_on_finished([&]()
			{
				update_idle_animation();
			});
	anim_fire_right.set_loop(false);
	anim_fire_right.set_interval(0.2);
	anim_fire_right.set_on_finished([&]()
			{
				update_idle_animation();
			});
}

void Tower::on_update(double delta)
{
	timer_fire.on_update(delta);
	anim_current->on_update(delta);

	if (can_fire)
	{
		on_fire();
	}
}

void Tower::on_render(SDL_Renderer* renderer)
{
	static SDL_Point point;

	point.x = (int)(position.x - size.x / 2);
	point.y = (int)(position.y - size.y / 2);
	
	anim_current->on_render(renderer, point);

}

void Tower::set_position(const Vector2& position)
{
	this->position = position;
}

const Vector2& Tower::get_size() const
{
	return size;
}

const Vector2& Tower::get_position() const
{
	return position;
}

void Tower::update_idle_animation()
{
	switch (facing) 
	{
	case Facing::Up:
		anim_current = &anim_idle_up;
		break;
	case Facing::Down:
		anim_current = &anim_idle_down;
		break;
	case Facing::Left:
		anim_current = &anim_idle_left;
		break;
	case Facing::Right:
		anim_current = &anim_idle_right;
		break;
	}
}

void Tower::update_fire_animation()
{
	switch (facing) 
	{
	case Facing::Up:
		anim_current = &anim_fire_up;
		break;
	case Facing::Down:
		anim_current = &anim_fire_down;
		break;
	case Facing::Left:
		anim_current = &anim_fire_left;
		break;
	case Facing::Right:
		anim_current = &anim_fire_right;
		break;
	}

}

Enemy* Tower::get_target_enemy()
{
	EnemyManager::EnemyList& enemy_list = EnemyManager::instance()->get_enemy_list();

	double process = -1;
	double view_range = 0;
	Enemy* target_enemy = nullptr;

	static ConfigManager* config_instance = ConfigManager::instance();

	switch (tower_type) 
	{
	case TowerType::Archer:
		view_range = config_instance->archer_template.view_range[config_instance->level_archer];
		break;
	case TowerType::Axeman:
		view_range = config_instance->axeman_template.view_range[config_instance->level_axeman];
		break;
	case TowerType::Gunner:
		view_range = config_instance->gunner_template.view_range[config_instance->level_gunner];
		break;
	}

	for (auto enemy : enemy_list)
	{
		if ((position - enemy->get_position()).length() <= view_range * SIZE_TILE)
		{
			double route_process = enemy->get_route_progress();
			if (route_process > process)
			{
				process = route_process;
				target_enemy = enemy;
			}
		}
	}

	return target_enemy;
}

void Tower::on_fire()
{
	Enemy* target_enemy = get_target_enemy();

	if (target_enemy == nullptr) return ;

	can_fire = false;
	static ConfigManager* config_instance = ConfigManager::instance();
	static const ResourcesManager::SoundPool& sound_pool =
		ResourcesManager::instance()->get_sound_pool();

	double interval = 0, damage = 0;
	switch (tower_type) 
	{
	case TowerType::Archer:
		damage = config_instance->archer_template.damage[config_instance->level_archer];
		interval = config_instance->archer_template.interval[config_instance->level_archer];
		switch (rand() % 2) 
		{
		case 0:
			Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_ArrowFire_1)->second, 0);
			break;
		case 1:
			Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_ArrowFire_2)->second, 0);
			break;
		}
		break;
	case TowerType::Axeman:
		damage = config_instance->axeman_template.damage[config_instance->level_axeman];
		interval = config_instance->axeman_template.interval[config_instance->level_axeman];
		Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_AxeFire)->second, 0);
		break;
	case TowerType::Gunner:
		damage = config_instance->gunner_template.damage[config_instance->level_gunner];
		interval = config_instance->gunner_template.interval[config_instance->level_gunner];
		Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_ShellFire)->second, 0);
		break;
	}
	timer_fire.set_wait_time(interval);
	timer_fire.restart();

	Vector2 direction = (target_enemy->get_position() - position).normalize();
	BulletManager::instance()->fire_bullet(bullet_type, position, direction * fire_speed * SIZE_TILE, damage);

	bool is_show_x_anim = abs(direction.x) > abs(direction.y);
	if (is_show_x_anim)
		facing = direction.x > 0 ? Facing::Right : Facing::Left;
	else
		facing = direction.y > 0 ? Facing::Down : Facing::Up;

	update_fire_animation();
	anim_current->reset();
}
