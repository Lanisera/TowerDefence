#pragma once

#include "enemy/enemy.h"
#include "manager/config_manager.h"
#include "manager/resources_manager.h"
#include <SDL_render.h>
#include <vector>

class SkeletonEnemy : public Enemy
{
public:
	SkeletonEnemy()
	{
		static ResourcesManager::TexturePool texture_pool =
			ResourcesManager::instance()->get_texture_pool();
		static SDL_Texture* skeleton_texture = texture_pool.find(ResID::Tex_Skeleton)->second;
		static SDL_Texture* skeleton_sketch_texture = texture_pool.find(ResID::Tex_SkeletonSketch)->second;
		static ConfigManager::EnemyTemplate& skeleton_template = ConfigManager::instance()->skeleton_template;

		const std::vector<int> idx_down = {0, 1, 2, 3, 4, 5};
		const std::vector<int> idx_up = {6, 7, 8, 9, 10, 11};
		const std::vector<int> idx_right = {12, 13, 14, 15, 16, 17};
		const std::vector<int> idx_left = {18, 19, 20, 21, 22, 23};

		anim_up.set_loop(true);
		anim_up.set_interval(0.1);
		anim_up.set_frame_date(skeleton_texture, 6, 4, idx_up);
		anim_down.set_loop(true);
		anim_down.set_interval(0.1);
		anim_down.set_frame_date(skeleton_texture, 6, 4, idx_down);
		anim_left.set_loop(true);
		anim_left.set_interval(0.1);
		anim_left.set_frame_date(skeleton_texture, 6, 4, idx_left);
		anim_right.set_loop(true);
		anim_right.set_interval(0.1);
		anim_right.set_frame_date(skeleton_texture, 6, 4, idx_right);

		anim_up.set_loop(true);
		anim_up.set_interval(0.1);
		anim_up.set_frame_date(skeleton_sketch_texture, 6, 4, idx_up);
		anim_down.set_loop(true);
		anim_down.set_interval(0.1);
		anim_down.set_frame_date(skeleton_sketch_texture, 6, 4, idx_down);
		anim_left.set_loop(true);
		anim_left.set_interval(0.1);
		anim_left.set_frame_date(skeleton_sketch_texture, 6, 4, idx_left);
		anim_right.set_loop(true);
		anim_right.set_interval(0.1);
		anim_right.set_frame_date(skeleton_sketch_texture, 6, 4, idx_right);

		max_hp = skeleton_template.hp;
		max_speed = skeleton_template.speed;
		damage = skeleton_template.damage;
		reward_ratio = skeleton_template.damage;
		recover_interval = skeleton_template.recover_interval;
		recover_range = skeleton_template.recover_range;
		recover_intensity = skeleton_template.recover_intensity;

		size.x = 48, size.y = 48;
		hp = max_hp, speed = max_speed;
	}
	
	~SkeletonEnemy() = default;
};
