#pragma once

#include "animation/animation.h"
#include "direction/facing.h"
#include "manager/manager.h"
#include "timer/timer.h"
#include "vector/vector2.h"
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>

class PlayerManager : public Manager<PlayerManager>
{
	friend class Manager<PlayerManager>;
public:
	void on_input(const SDL_Event& event);

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	double get_current_mp() const;

protected:
	PlayerManager();

	~PlayerManager() = default;

private:
	Vector2 size;
	Vector2 position;
	Vector2 velocity;

	SDL_Rect rect_hitbox_flash = {0};
	SDL_Rect rect_hitbox_impact = {0};

	double mp = 100;

	double speed = 0;

	bool can_release_flash = true;
	bool is_releasing_flash = false;
	bool is_releasing_impact = false;

	bool is_move_up = false;
	bool is_move_down = false;
	bool is_move_left = false;
	bool is_move_right = false;

	Animation anim_idle_up;
	Animation anim_idle_down;
	Animation anim_idle_left;
	Animation anim_idle_right;
	Animation anim_attack_up;
	Animation anim_attack_down;
	Animation anim_attack_left;
	Animation anim_attack_right;
	Animation* anim_current = &anim_idle_right;

	Animation anim_effect_flash_up;
	Animation anim_effect_flash_down;
	Animation anim_effect_flash_left;
	Animation anim_effect_flash_right;
	Animation* anim_effect_flash_current = nullptr;

	Animation anim_effect_impact_up;
	Animation anim_effect_impact_down;
	Animation anim_effect_impact_left;
	Animation anim_effect_impact_right;
	Animation* anim_effect_impact_current = nullptr;

	Timer timer_release_flash_cd;
	Timer timer_auto_increase_mp;

	Facing facing = Facing::Right;

private:
	void on_release_flash();

	void on_release_impact();
};
