#include "manager/bullet_manager.h"
#include "bullet/bullet.h"
#include "bullet/bullet_type.h"
#include "vector/vector2.h"
#include "bullet/arrow_bullet.h"
#include "bullet/axe_bullet.h"
#include "bullet/shell_bullet.h"
#include <algorithm>

void BulletManager::on_update(double delta)
{
	for (auto bullet : bullet_list)
		bullet->on_update(delta);

	remove_invalid_bullet();
}

void BulletManager::on_render(SDL_Renderer* renderer)
{
	for (auto bullet : bullet_list)
		bullet->on_render(renderer);
}

BulletManager::BulletList& BulletManager::get_bullet_list()
{
	return bullet_list;
}

void BulletManager::fire_bullet(BulletType type, const Vector2& position, const Vector2& velocity, double damage)
{
	Bullet* bullet = nullptr;

	switch (type) 
	{
	case BulletType::Arrow:
		bullet = new ArrowBullet();
		break;
	case BulletType::Axe:
		bullet = new AxeBullet();
		break;
	case BulletType::Shell:
		bullet = new ShellBullet();
		break;
	default:
		bullet = new ArrowBullet();
	}

	bullet->set_position(position);
	bullet->set_velocity(velocity);
	bullet->set_damage(damage);

	bullet_list.push_back(bullet);
}

BulletManager::~BulletManager()
{
	for (auto bullet : bullet_list)
		delete bullet;
}

void BulletManager::remove_invalid_bullet()
{
	bullet_list.erase(std::remove_if(bullet_list.begin(), bullet_list.end(), 
				[&](const Bullet* bullet)
				{
					bool deleteable = bullet->can_remove();
					if (deleteable)
						delete bullet;
					return deleteable;
				}), bullet_list.end());
}
