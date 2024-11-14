#include "manager/coin_manager.h"
#include "manager/enemy_manager.h"
#include "manager/wave_manager.h"
#include "manager/config_manager.h"
#include <vector>
#include <iostream>

void WaveManager::on_update(double delta)
{
	static ConfigManager* config_instance = ConfigManager::instance();

	// std::cerr << config_instance->wave_list.size() << " " << config_instance->wave_list[idx_wave].spawn_event_list.size() << std::endl;

	if (config_instance->is_game_over)
		return ;

	if (!is_wave_started)
	{
		// std::cerr << "wave enter" << std::endl;
		wave_start_timer.on_update(delta);
		// std::cerr << "exit" << std::endl;
	}
	else
	{
		// std::cerr << "spawn enter" << std::endl;
		spawn_event_timer.on_update(delta);
		// std::cerr << "exit" << std::endl;
	}


	if (is_spawned_last_enemy && EnemyManager::instance()->check_cleared())
	{
		CoinManager::instance()->increase_coin(config_instance->wave_list[idx_wave].rewards);

		idx_wave++;
		if (idx_wave >= config_instance->wave_list.size())
		{
			config_instance->is_game_win = true;
			config_instance->is_game_over = true;
		}
		else
		{
			idx_spawn_event = 0;
			is_wave_started = false;
			is_spawned_last_enemy = false;

			wave_start_timer.set_wait_time(config_instance->wave_list[idx_wave].interval);
			wave_start_timer.restart();
		}

	}
}

WaveManager::WaveManager()
{
	static const std::vector<Wave> wave_list = ConfigManager::instance()->wave_list;

	wave_start_timer.set_one_shot(true);
	wave_start_timer.set_wait_time(wave_list[idx_wave].interval);
	wave_start_timer.set_on_timeout([&]()
			{
				is_wave_started = true;
				spawn_event_timer.set_wait_time(wave_list[idx_wave].spawn_event_list[0].interval);
				spawn_event_timer.restart();
			});

	spawn_event_timer.set_one_shot(true);
	spawn_event_timer.set_on_timeout([&]() 
			{
				const std::vector<Wave::SpawnEvent>& spawn_event_list = wave_list[idx_wave].spawn_event_list;
				const Wave::SpawnEvent& spawn_event = spawn_event_list[idx_spawn_event];

				// generate enemy
				EnemyManager::instance()->spawn_enemy(spawn_event.type, spawn_event.spawn_point);
				
				// prepare for next wave
				idx_spawn_event++;


				if (idx_spawn_event >= spawn_event_list.size())
				{
					is_spawned_last_enemy = true;
					return ;
				}

				spawn_event_timer.set_wait_time(spawn_event_list[idx_spawn_event].interval);
				spawn_event_timer.restart();
			});
}
