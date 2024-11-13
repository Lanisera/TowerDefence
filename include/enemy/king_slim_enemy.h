#pragma once

#include "enemy/enemy.h"
#include "manager/config_manager.h"
#include "manager/resources_manager.h"
#include <SDL_render.h>
#include <vector>

class KingSlimEnemy : public Enemy
{
public:
	KingSlimEnemy()
	{
		static ResourcesManager::TexturePool texture_pool =
			ResourcesManager::instance()->get_texture_pool();
		static SDL_Texture* king_slime_texture = texture_pool.find(ResID::Tex_KingSlime)->second;
		static SDL_Texture* king_slime_sketch_texture = texture_pool.find(ResID::Tex_KingSlimeSketch)->second;
		static ConfigManager::EnemyTemplate& king_slime_template = ConfigManager::instance()->king_slim_template;

		const std::vector<int> idx_down = {0, 1, 2, 3, 4, 5};
		const std::vector<int> idx_left = {6, 7, 8, 9, 10, 11};
		const std::vector<int> idx_right = {12, 13, 14, 15, 16, 17};
		const std::vector<int> idx_up = {18, 19, 20, 21, 22, 23};

		anim_up.set_loop(true);
		anim_up.set_interval(0.1);
		anim_up.set_frame_date(king_slime_texture, 6, 4, idx_up);
		anim_down.set_loop(true);
		anim_down.set_interval(0.1);
		anim_down.set_frame_date(king_slime_texture, 6, 4, idx_down);
		anim_left.set_loop(true);
		anim_left.set_interval(0.1);
		anim_left.set_frame_date(king_slime_texture, 6, 4, idx_left);
		anim_right.set_loop(true);
		anim_right.set_interval(0.1);
		anim_right.set_frame_date(king_slime_texture, 6, 4, idx_right);

		anim_up.set_loop(true);
		anim_up.set_interval(0.1);
		anim_up.set_frame_date(king_slime_sketch_texture, 6, 4, idx_up);
		anim_down.set_loop(true);
		anim_down.set_interval(0.1);
		anim_down.set_frame_date(king_slime_sketch_texture, 6, 4, idx_down);
		anim_left.set_loop(true);
		anim_left.set_interval(0.1);
		anim_left.set_frame_date(king_slime_sketch_texture, 6, 4, idx_left);
		anim_right.set_loop(true);
		anim_right.set_interval(0.1);
		anim_right.set_frame_date(king_slime_sketch_texture, 6, 4, idx_right);

		max_hp = king_slime_template.hp;
		max_speed = king_slime_template.speed;
		damage = king_slime_template.damage;
		reward_ratio = king_slime_template.damage;
		recover_interval = king_slime_template.recover_interval;
		recover_range = king_slime_template.recover_range;
		recover_intensity = king_slime_template.recover_intensity;

		size.x = 48, size.y = 48;
		hp = max_hp, speed = max_speed;
	}
	
	~KingSlimEnemy() = default;
};
