#pragma once

#include "ui/panel.h"
#include <SDL_pixels.h>
#include <SDL_render.h>

class PlacePanel : public Panel
{
public:
	PlacePanel();

	~PlacePanel() = default;

	void on_update(SDL_Renderer* renderer) override;

	void on_render(SDL_Renderer* renderer) override;

protected:
	void on_click_top_area() override;

	void on_click_left_area() override;

	void on_click_right_area() override;

private:
	int reg_top = 0;
	int reg_left = 0;
	int reg_right = 0;
	const SDL_Color color_region_frame = {30, 80, 162, 175};
	const SDL_Color color_region_content = {0, 149, 217, 75};
};
