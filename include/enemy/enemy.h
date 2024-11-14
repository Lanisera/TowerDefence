#pragma once

#include <SDL_render.h>
#include <functional>
#include <string>
#include <timer/timer.h>
#include <vector/vector2.h>
#include <animation/animation.h>
#include <map/route.h>

class Enemy
{
public:
	using SkillCallBack = std::function<void(Enemy*)>;
public:
	Enemy();

	~Enemy() = default;

	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	void set_on_skill_released(SkillCallBack on_skill_released);

	void increase_hp(double hp);

	void decrease_hp(double hp);

	void slow_down();

	void set_position(Vector2& vec);

	void set_route(const Route* route);

	void make_invalid();

	double get_hp() const;

	const Vector2& get_size() const;

	const Vector2& get_position() const;

	const Vector2& get_velocity() const;

	double get_damage() const;

	double get_reward_ratio() const;

	double get_recover_radius() const;

	double get_recover_intensity() const;

	bool can_remove() const;

	double get_route_progress() const;


protected:
	Vector2 size;

	Timer timer_skill;
	
	Animation anim_up;
	Animation anim_down;
	Animation anim_left;
	Animation anim_right;

	Animation anim_sketch_up;
	Animation anim_sketch_down;
	Animation anim_sketch_left;
	Animation anim_sketch_right;

	double hp = 0;
	double max_hp = 0;
	double speed = 0;
	double max_speed = 0;
	double damage = 0;
	double reward_ratio = 0;
	double recover_interval = 0;
	double recover_range = 0;
	double recover_intensity = 0;

	// for debug
	std::string name;
	
private:
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;

	bool is_valid = true;

	Timer timer_sketch;
	bool is_show_sketch = false;

	Animation* anim_current = nullptr;

	Timer timer_restore_speed;
	
	SkillCallBack on_skill_released;

	const Route* route = nullptr;
	int idx_target = 0;
	Vector2 position_target;

private:
	void refresh_target_position();

};
