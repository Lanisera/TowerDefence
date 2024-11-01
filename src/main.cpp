#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#define SDL_MAIN_HANDLED

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_Window* window = SDL_CreateWindow(u8"TowerDefence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,  SDL_WINDOW_SHOWN);
	SDL_Renderer* render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Surface* suf_img = IMG_Load("../resources/enemy_goblin_priest.png");
	SDL_Texture* tex_img = SDL_CreateTextureFromSurface(render, suf_img);

	TTF_Font* font = TTF_OpenFont("../resources/ipix.ttf", 32);	
	SDL_Color font_color{255, 255, 255, 255};
	SDL_Surface* suf_text = TTF_RenderText_Blended(font, u8"Test", font_color);
	SDL_Texture* tex_text = SDL_CreateTextureFromSurface(render, suf_text);

	Mix_Music* music = Mix_LoadMUS("../resources/music_bgm.mp3");
	Mix_FadeInMusic(music, -1, 1500);

	SDL_Event event;
	SDL_Point point{0, 0};
	SDL_Rect rect_img{0, 0, 0, 0}, rect_text{0, 0, 0, 0};

	rect_img.w = suf_img->w;
	rect_img.h = suf_img->h;

	rect_text.w = suf_text->w;
	rect_text.h = suf_text->h;

	int fps = 60;
	Uint64 last_counter = SDL_GetPerformanceCounter();
	Uint64 counter_freq = SDL_GetPerformanceFrequency();

	bool is_quit = false;
	while (!is_quit) 
	{
		// 窗口事件处理
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT)
			{
				is_quit = true;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				point.x = event.motion.x;
				point.y = event.motion.y;
			}
		}	

		// 数据处理
		rect_img.x = point.x;
		rect_img.y = point.y;

		rect_text.x = point.x;
		rect_text.y = point.y;

		int cur_counter = SDL_GetPerformanceCounter();
		double delta = (double)(cur_counter - last_counter)  / counter_freq;
		if (delta * 1000.0 < 1000.0 / fps)
			SDL_Delay((Uint32)(1000.0 / 60) - delta * 1000.0);
		last_counter = cur_counter;
		
		// 渲染图形
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);

		SDL_RenderCopy(render, tex_img, nullptr, &rect_img);
		SDL_RenderCopy(render, tex_text, nullptr, &rect_text);
		filledCircleRGBA(render, point.x, point.y, 50, 255, 0, 0, 125);
		SDL_RenderPresent(render);
	}

	return 0;
}
