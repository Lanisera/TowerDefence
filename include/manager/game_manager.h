#pragma once

#include <SDL_events.h>
#include <SDL_hints.h>
#include <SDL_messagebox.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_video.h>
#include <cjson/cJSON.h>

#include <manager/manager.h>

class GameManager: public Manager<GameManager>
{
	friend class Manager<GameManager>;
	
public:
	int run(int argc, char **argv);

protected:
	
	GameManager();

	~GameManager();

private:
	SDL_Event event;
	bool is_quit = false;

	SDL_Window *window = nullptr;
	SDL_Renderer *renderer = nullptr; 

	SDL_Texture* tex_tile_map = nullptr;

private:
	void init_assert(bool flag, const char* err_msg);

	void on_input();

	void on_update(double delta);

	void on_render();

	bool generate_tile_map_texture();
};
