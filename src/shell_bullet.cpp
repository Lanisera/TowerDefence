#include "bullet/shell_bullet.h"
#include "enemy/enemy.h"
#include "manager/resources_manager.h"
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <iostream>

ShellBullet::ShellBullet()
{
	static SDL_Texture* tex_shell = 
		ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_BulletShell)->second;
	static SDL_Texture* explode_tex_shell = 
		ResourcesManager::instance()->get_texture_pool().find(ResID::Tex_EffectExplode)->second;
	static const std::vector<int>& idx_list = {0, 1};
	static const std::vector<int>& explode_idx_list = {0, 1, 2, 3, 4};

	// init for normal shell
	animation.set_loop(true);
	animation.set_interval(0.1);
	animation.set_frame_date(tex_shell, 2, 1, idx_list);

	size.x = 48, size.y = 48;

	//init for explode shell
	explode_animation.set_loop(false);
	explode_animation.set_interval(0.1);
	explode_animation.set_frame_date(explode_tex_shell, 5, 1, explode_idx_list);
	explode_animation.set_on_finished(
			[&]()
			{
				make_invalid();
			});

	damage_range = 96;
	explode_size.x = 96, explode_size.y = 96;

}

void ShellBullet::on_collide(Enemy* enemy)
{
	static const ResourcesManager::SoundPool& sound_pool = 
		ResourcesManager::instance()->get_sound_pool();

	Mix_PlayChannel(-1, sound_pool.find(ResID::Sound_ShellHit)->second, 0);

	disable_collide();
}

void ShellBullet::on_update(double delta)
{
	if (can_collision())
	{
		Bullet::on_update(delta);
		return ;
	}

	explode_animation.on_update(delta);

}

void ShellBullet::on_render(SDL_Renderer* renderer)
{
	if (can_collision())
	{
		Bullet::on_render(renderer);
		return ;
	}
	
	static SDL_Point point;

	point.x = (int)(position.x - explode_size.x / 2);
	point.y = (int)(position.y - explode_size.y / 2);
	
	explode_animation.on_render(renderer, point);

}
