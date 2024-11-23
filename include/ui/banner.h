#pragma once

#include "timer/timer.h"
#include "vector/vector2.h"
#include <SDL_render.h>

class Banner
{
public:
	Banner();

	~Banner() = default;

	void set_center_position(const Vector2& position);

	bool check_end_display() const;

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 center_pos;

	Vector2 size_foreground;
	Vector2 size_background;

	SDL_Texture* tex_foreground = nullptr;
	SDL_Texture* tex_background = nullptr;

	bool is_end_display = false;
	Timer timer_end_display;
};
