#pragma once

#include "manager/manager.h"
#include "bullet/bullet.h"
#include "bullet/bullet_type.h"
#include "vector/vector2.h"
#include <SDL_render.h>
#include <vector>

class BulletManager : public Manager<BulletManager>
{
	friend class Manager<BulletManager>;
public:
	using BulletList = std::vector<Bullet*>;
public:
	void on_update(double delta);

	void on_render(SDL_Renderer* renderer);

	BulletList& get_bullet_list();

	void fire_bullet(BulletType type, const Vector2& position, const Vector2& velocity, double damage);

protected:
	BulletManager() = default;

	~BulletManager();

private:
	BulletList bullet_list;

private:
	void remove_invalid_bullet();

};
