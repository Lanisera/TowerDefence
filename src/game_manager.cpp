#include <manager/game_manager.h>

int GameManager::run(int argc, char **argv)
{
	Uint64 last_counter = SDL_GetPerformanceCounter();
	Uint64 counter_freq = SDL_GetPerformanceFrequency();

	while (!is_quit)
	{
		// 处理事件
		while (SDL_PollEvent(&event))
			on_input();

		Uint64 cur_counter = SDL_GetPerformanceCounter();
		double delta = (double)(cur_counter - last_counter) / counter_freq;
		last_counter = cur_counter;
		if (delta * 1000.0 < 1000.0 / 60)
				SDL_Delay((Uint32)((1000.0 / 60) - delta * 1000.0));

		// 更新数据

		on_update(delta);

		// 绘制画面
		SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
		SDL_RenderClear(render);

		on_render();
	}

	return 0;
}

GameManager::GameManager()
{
	init_assert(!SDL_Init(SDL_INIT_EVERYTHING), u8"SDL2 初始化失败");
	init_assert(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG), u8"SDL_image 初始化失败");
	init_assert(Mix_Init(MIX_INIT_MP3), u8"SDL_mixer 初始化失败");
	init_assert(!TTF_Init(), u8"SLD_ttf 初始化失败");
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	SDL_SetHint(SDL_HINT_IME_SHOW_UI, "-1");

	window = SDL_CreateWindow(u8"TowerDefence", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720,  SDL_WINDOW_SHOWN);
	init_assert(window, u8"创建窗口失败");

	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	init_assert(render, u8"渲染器创建失败");
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

}

void GameManager::init_assert(bool flag, const char* err_msg)
{
	if (flag) return ;
	
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, u8"游戏启动失败", err_msg, window);
	exit(-1);
}

void GameManager::on_input()
{
	if (event.type == SDL_QUIT)
	{
		is_quit = true;
	}

}

void GameManager::on_update(double delta)
{

}

void GameManager::on_render()
{

}
