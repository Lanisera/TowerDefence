#pragma once

#include <enemy/enemy_type.h>

#include <vector>

struct Wave
{
	struct SpawnEvent
	{
		double interval = 0;
		int spawn_point = 1;
		EnemyType type = EnemyType::Slim;
	};

	double interval = 0;
	double rewards = 100;
	std::vector<SpawnEvent> spawn_event_list;
	
};
