#pragma once

#include "animation/animation.h"
#include "bullet/bullet.h"
#include "enemy/enemy.h"
#include <SDL_render.h>

class ShellBullet : public Bullet
{
public:
	ShellBullet();

	~ShellBullet() = default;

	void on_collide(Enemy* enemy) override;

	void on_update(double delta) override;

	void on_render(SDL_Renderer* renderer) override;

private:
	Animation explode_animation;
	Vector2 explode_size;
};
