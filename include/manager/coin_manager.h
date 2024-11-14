#pragma once

#include "manager/manager.h"

class CoinManager : public Manager<CoinManager>
{
	friend class Manager<CoinManager>;

public:
	void increase_coin(double val);

	void decrease_coin(double val);

protected:
	CoinManager();

	~CoinManager() = default;

private:
	double num_coin = 0;
};
