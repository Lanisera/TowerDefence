#pragma once

#include "bullet/bullet.h"
#include "enemy/enemy.h"

class ArrowBullet : public Bullet
{
public:
	ArrowBullet();

	~ArrowBullet() = default;

	void on_collide(Enemy* enemy) override;
};
