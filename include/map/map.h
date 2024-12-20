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

	// 地图用csv文件定义，按照csv格式读取地图
	bool load(const std::string& path);

	size_t get_height() const;

	size_t get_width() const;

	const TileMap& get_tile_map() const;

	const SDL_Point& get_idx_home() const;

	const SpawnerRoutePool& get_spawner_route_pool() const;

	void place_tower(const SDL_Point& idx_tile);

private:
	TileMap tile_map;
	SDL_Point idx_home {0};
	SpawnerRoutePool spawner_route_pool;

private:
	std::string trim_str(const std::string& str);

	void load_tile_from_string(Tile& tile, std::string& str);

	void generate_map_cache();
};
