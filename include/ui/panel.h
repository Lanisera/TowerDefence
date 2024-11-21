#pragma once

#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
class Panel
{
public:
	Panel();

	~Panel();

	void show();

	void set_idx_tile(const SDL_Rect& idx);

	void set_center_pos(const SDL_Rect& pos);

	void on_input(const SDL_Event& event);

	virtual void on_update(SDL_Renderer* renderer);

	virtual void on_render(SDL_Renderer* renderer);

protected:
	enum class HoveredTarget
	{
		None,
		Top,
		Left,
		Right
	};

protected:
	virtual void on_click_top_area() = 0;
	
	virtual void on_click_left_area() = 0;

	virtual void on_click_right_area() = 0;

protected:
	bool visible = false;
	SDL_Rect idx_tile_selected;
	SDL_Rect center_pos = {0};
	SDL_Texture* tex_idle = nullptr;
	SDL_Texture* tex_hovered_top = nullptr;
	SDL_Texture* tex_hovered_left = nullptr;
	SDL_Texture* tex_hovered_right = nullptr;
	SDL_Texture* tex_select_cursor = nullptr;
	int val_top = 0, val_left = 0, val_right = 0;
	HoveredTarget hovered_target = HoveredTarget::None;

private:
	const int size_button = 48;
	const int width = 144, height = 144;
	const SDL_Rect offset_top = {48, 6};
	const SDL_Rect offset_left = {8, 80};
	const SDL_Rect offset_right = {90, 80};
	const SDL_Rect offset_shadow = {3, 3};
	const SDL_Color color_text_background = {175, 175, 175, 255};
	const SDL_Color color_text_foreground = {255, 255, 255, 255};

	int width_text = 0, height_text = 0;
	SDL_Texture* tex_text_background = nullptr;
	SDL_Texture* tex_text_foreground = nullptr;
};
