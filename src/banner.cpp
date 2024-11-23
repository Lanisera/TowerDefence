#include "ui/banner.h"
#include "manager/coin_manager.h"
#include "manager/config_manager.h"
#include "manager/resources_manager.h"
#include "vector/vector2.h"
#include <SDL_render.h>

Banner::Banner()
{
	size_foreground = {646, 215};
	size_background = {1282, 209};


	timer_end_display.set_one_shot(true);
	timer_end_display.set_wait_time(5);
	timer_end_display.set_on_timeout([&]()
			{
				is_end_display = true;
			});
}

void Banner::set_center_position(const Vector2& position)
{
	center_pos = position;
}

bool Banner::check_end_display() const
{
	return is_end_display;
}

void Banner::on_update(double delta)
{
	timer_end_display.on_update(delta);

	static const ResourcesManager::TexturePool& texture_pool =
		ResourcesManager::instance()->get_texture_pool();
	static SDL_Texture* tex_win_text = texture_pool.find(ResID::Tex_UIWinText)->second;
	static SDL_Texture* tex_loss_text = texture_pool.find(ResID::Tex_UILossText)->second;

	tex_foreground = ConfigManager::instance()->is_game_win ? tex_win_text : tex_loss_text;
	tex_background = texture_pool.find(ResID::Tex_UIGameOverBar)->second;
	
}

void Banner::on_render(SDL_Renderer* renderer)
{
	static SDL_Rect rect_dst;
	static const ResourcesManager::TexturePool& texture_pool =
		ResourcesManager::instance()->get_texture_pool();
	static SDL_Texture* tex_win_text = texture_pool.find(ResID::Tex_UIWinText)->second;
	static SDL_Texture* tex_loss_text = texture_pool.find(ResID::Tex_UILossText)->second;


	rect_dst.x = (int)(center_pos.x - size_background.x / 2);
	rect_dst.y = (int)(center_pos.y - size_background.y / 2);
	rect_dst.w = (int)size_background.x, rect_dst.h = (int)size_background.y;
	SDL_RenderCopy(renderer, tex_background, nullptr, &rect_dst);

	rect_dst.x = (int)(center_pos.x - size_foreground.x / 2);
	rect_dst.y = (int)(center_pos.y - size_foreground.y / 2);
	rect_dst.w = (int)size_foreground.x, rect_dst.h = (int)size_foreground.y;
	SDL_RenderCopy(renderer, tex_foreground, nullptr, &rect_dst);
}
