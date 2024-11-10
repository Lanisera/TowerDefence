#pragma once

#include <SDL.h>
#include <SDL_rect.h>
#include <string>
#include <unordered_map>

#include <map/tile.h>
#include <map/route.h>

class Map
{
public:
	using SpawnerRoutePool = std::unordered_map<int, Route>;

public:
	Map() = default;
	~Map() = default;

	bool load(const std::string& path);

	size_t get_height();

	size_t get_width();

private:
	TileMap tile_map;
	SDL_Point idx_home {0};
	SpawnerRoutePool spawner_route_pool;

private:
	std::string trim_str(const std::string& str);

	void load_tile_from_string(Tile& tile, std::string& str);

	void generate_map_cache();
};
