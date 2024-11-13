#pragma once

#include "manager/manager.h"

class HomeManager : public Manager<HomeManager>
{
	friend class Manager<HomeManager>;

public:
	double get_current_num_hp() const;

	void decrease_hp(double val);

protected:
	HomeManager();

	~HomeManager() = default;

private:
	double num_hp = 0;
};
