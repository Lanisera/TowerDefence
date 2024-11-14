#pragma once

#include "manager/manager.h"
#include "timer/timer.h"

class WaveManager : public Manager<WaveManager>
{
	friend class Manager<WaveManager>;

public:
	void on_update(double delta);

protected:
	WaveManager();

	~WaveManager() = default;

private:
	int idx_wave = 0;
	int idx_spawn_event = 0;
	Timer wave_start_timer;
	Timer spawn_event_timer;
	bool is_wave_started = false;
	bool is_spawned_last_enemy = false;
};
