#pragma once

#include "enemy/enemy.h"
#include "manager/config_manager.h"
#include "manager/resources_manager.h"
#include <SDL_render.h>
#include <vector>

class GoblinEnemy : public Enemy
{
public:
	GoblinEnemy()
	{
		static ResourcesManager::TexturePool texture_pool =
			ResourcesManager::instance()->get_texture_pool();
		static SDL_Texture* goblin_texture = texture_pool.find(ResID::Tex_Goblin)->second;
		static SDL_Texture* goblin_sketch_texture = texture_pool.find(ResID::Tex_GoblinSketch)->second;
		static ConfigManager::EnemyTemplate& goblin_template = ConfigManager::instance()->goblin_template;

		const std::vector<int> idx_down = {0, 1, 2, 3, 4, 5};
		const std::vector<int> idx_up = {6, 7, 8, 9, 10, 11};
		const std::vector<int> idx_right = {12, 13, 14, 15, 16, 17};
		const std::vector<int> idx_left = {18, 19, 20, 21, 22, 23};

		anim_up.set_loop(true);
		anim_up.set_interval(0.1);
		anim_up.set_frame_date(goblin_texture, 6, 4, idx_up);
		anim_down.set_loop(true);
		anim_down.set_interval(0.1);
		anim_down.set_frame_date(goblin_texture, 6, 4, idx_down);
		anim_left.set_loop(true);
		anim_left.set_interval(0.1);
		anim_left.set_frame_date(goblin_texture, 6, 4, idx_left);
		anim_right.set_loop(true);
		anim_right.set_interval(0.1);
		anim_right.set_frame_date(goblin_texture, 6, 4, idx_right);

		anim_up.set_loop(true);
		anim_up.set_interval(0.1);
		anim_up.set_frame_date(goblin_sketch_texture, 6, 4, idx_up);
		anim_down.set_loop(true);
		anim_down.set_interval(0.1);
		anim_down.set_frame_date(goblin_sketch_texture, 6, 4, idx_down);
		anim_left.set_loop(true);
		anim_left.set_interval(0.1);
		anim_left.set_frame_date(goblin_sketch_texture, 6, 4, idx_left);
		anim_right.set_loop(true);
		anim_right.set_interval(0.1);
		anim_right.set_frame_date(goblin_sketch_texture, 6, 4, idx_right);

		max_hp = goblin_template.hp;
		max_speed = goblin_template.speed;
		damage = goblin_template.damage;
		reward_ratio = goblin_template.damage;
		recover_interval = goblin_template.recover_interval;
		recover_range = goblin_template.recover_range;
		recover_intensity = goblin_template.recover_intensity;

		size.x = 48, size.y = 48;
		hp = max_hp, speed = max_speed;
	}
	
	~GoblinEnemy() = default;
};
