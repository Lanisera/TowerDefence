#pragma once

#include "ui/panel.h"
#include <SDL_render.h>

class UpgradePanel : public Panel
{
public:
	UpgradePanel();

	~UpgradePanel() = default;

	void on_update(SDL_Renderer* renderer) override;

protected:
	void on_click_top_area() override;

	void on_click_left_area() override;

	void on_click_right_area() override;

};
