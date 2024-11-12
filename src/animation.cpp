#include <SDL_rect.h>
#include <SDL_render.h>
#include <animation/animation.h>
#include <vector>

Animation::Animation()
{
	timer.set_one_shot(false);
	timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				if (idx_frame >= rect_src_list.size())
				{
					idx_frame = is_loop ? 0 : rect_src_list.size() - 1;
					if (!is_loop && on_finished)
						on_finished();
				}
			}
		);
}

void Animation::reset()
{
	idx_frame = 0;
	timer.restart();
}

void Animation::set_frame_date(SDL_Texture* texture, int width, int height, const std::vector<int>& idx_list)
{
	this->texture = texture;
	
	int width_tex, height_tex;
	SDL_QueryTexture(texture, nullptr, nullptr, &width_tex, &height_tex);
	width_frame = width_tex / width;
	height_frame = height_tex / height;

	rect_src_list.resize(idx_list.size());
	for (int i = 0; i < idx_list.size(); i++)
	{
		int idx = idx_list[i];
		SDL_Rect& rect_src = rect_src_list[i];

		rect_src.x = idx % width * width_frame;
		rect_src.y = idx / width * height_frame;
		rect_src.w = width_frame, rect_src.h = height_frame;
	}
}

void Animation::set_loop(bool flag)
{
	is_loop = flag;
}

void Animation::set_interval(double interval)
{
	timer.set_wait_time(interval);
}

void Animation::set_on_finished(PlayCallBack on_finished)
{
	this->on_finished = on_finished;
}

void Animation::on_update(double delta)
{
	timer.on_update(delta);
}

void Animation::on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle) const
{
	static SDL_Rect rect_dst;
	rect_dst.x = pos_dst.x, rect_dst.y = pos_dst.y;
	rect_dst.w = width_frame, rect_dst.h = height_frame;

	SDL_RenderCopyEx(renderer, texture, &rect_src_list[idx_frame], &rect_dst, angle, nullptr, SDL_FLIP_NONE);
}
