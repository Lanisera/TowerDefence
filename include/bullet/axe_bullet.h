#pragma once

#include "bullet/bullet.h"
#include "enemy/enemy.h"

class AxeBullet : public Bullet
{
public:
	AxeBullet();

	~AxeBullet() = default;

	void on_collide(Enemy* enemy) override;
};
