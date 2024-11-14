#include <timer/timer.h>

void Timer::restart()
{
	pass_time = 0;
	shotted = false;
}

void Timer::set_wait_time(double time)
{
	wait_time = time;
}

void Timer::set_one_shot(bool flag)
{
	one_shot = flag;
}

void Timer::set_on_timeout(std::function<void()> on_timeout)
{
	this->on_timeout = on_timeout;
}

void Timer::pasue()
{
	pasued = true;
}

void Timer::resume()
{
	pasued = false;
}

void Timer::on_update(double delta)
{
	if (pasued)
		return ;

	pass_time += delta;
	if (pass_time >= wait_time)
	{
		bool can_shot = (!one_shot || (one_shot && !shotted));
		shotted = true;
		if (can_shot && on_timeout)
			on_timeout();
		pass_time -= wait_time;
	}
}
