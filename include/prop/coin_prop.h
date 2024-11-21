#pragma once

#include "timer/timer.h"
#include "vector/vector2.h"
#include <SDL_render.h>

class CoinProp
{
public:
	CoinProp();

	~CoinProp() = default;

	void set_position(const Vector2& position);

	const Vector2& get_position() const;

	const Vector2& get_size() const;

	void make_invalid();

	bool can_remove() const;

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

private:
	Vector2 position;
	Vector2 velocity;

	Timer timer_jump;
	Timer timer_disappear;

	bool is_jumping = true;
	double jumping_interval = 0.75;
	bool is_valid = true;
	double disappear_interval = 10;

	double gravity = 490;
	Vector2 size = {16, 16};
};
