#pragma once

#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;
	
	void restart();

	void set_wait_time(double time);

	void set_one_shot(bool flag);

	void set_on_timeout(std::function<void()>);

	void pasue();

	void resume();

	void on_update(double delta);

private:
	double pass_time = 0;
	double wait_time = 0;
	bool pasued = false;
	bool shotted = false;
	bool one_shot = false;
	std::function<void()> on_timeout;

};
