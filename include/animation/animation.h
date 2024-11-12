#pragma once

#include <SDL_rect.h>
#include <SDL_render.h>
#include <functional>

#include <timer/timer.h>
#include <vector>

class Animation
{
public:
	using PlayCallBack = std::function<void()>;

public:
	Animation();

	~Animation() = default;

	void reset();

	void set_frame_date(SDL_Texture* texture, int width, int height, const std::vector<int>& idx_list);

	void set_loop(bool flag);

	void set_interval(double interval);

	void set_on_finished(PlayCallBack on_finished);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer, const SDL_Point& pos_dst, double angle = 0) const;

private:
	Timer timer;
	bool is_loop = true;
	PlayCallBack on_finished;
	SDL_Texture* texture = nullptr;
	size_t idx_frame = 0;
	std::vector<SDL_Rect> rect_src_list;
	int height_frame, width_frame;
};
