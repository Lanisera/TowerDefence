#include <map/map.h>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iostream>


bool Map::load(const std::string& path)
{
	std::ifstream file(path);
	if (!file.good()) return false;

	TileMap tile_map_temp;

	int idx_x = -1, idx_y = -1;
	
	std::string str_line;
	while (std::getline(file, str_line))
	{

		str_line = trim_str(str_line);
		if (str_line.empty())
			continue;

		idx_x++, idx_y = -1;
		tile_map_temp.emplace_back();

		std::string str_tile;
		std::stringstream str_stream(str_line);
		while (std::getline(str_stream, str_tile, ','))
		{
			idx_y++;
			tile_map_temp[idx_x].emplace_back();
			Tile& tile = tile_map_temp[idx_x].back();
			load_tile_from_string(tile, str_tile);
		}
	}

	file.close();

	if (tile_map_temp.empty() || tile_map_temp[0].empty())
		return false;

	tile_map = tile_map_temp;

	generate_map_cache();

	return true;
}


size_t Map::get_height() const
{
	return tile_map.size();
}

size_t Map::get_width() const
{
	return tile_map.empty() ? 0 : tile_map[0].size();
}

const TileMap& Map::get_tile_map() const
{
	return tile_map;	
}

const SDL_Point& Map::get_idx_home() const
{
	return idx_home;
}

const Map::SpawnerRoutePool& Map::get_spawner_route_pool() const
{
	return spawner_route_pool;
}

void Map::place_tower(const SDL_Point& idx_tile)
{
	tile_map[idx_tile.y][idx_tile.x].has_tower = true;
}

/// help function ///
std::string Map::trim_str(const std::string& str)
{
	size_t begin_idx = str.find_first_not_of(" \t");
	if (begin_idx == std::string::npos)
		return "";
	size_t end_idx = str.find_last_not_of(" \t");
	size_t str_size = end_idx - begin_idx + 1;

	return str.substr(begin_idx, str_size);
}

void Map::load_tile_from_string(Tile& tile, std::string& str)
{
	str = trim_str(str);

	std::vector<int> values;
	std::string string_value;
	std::stringstream tile_stream(str);
	while (std::getline(tile_stream, string_value, '\\'))
	{
		int value;
		try
		{
			value = std::stoi(string_value);
		}
		catch (const std::invalid_argument&)
		{
			value = -1;
		}
		values.push_back(value);
	}

	tile.terrian = (values.size() < 1 || values[0] < 0) ? 0 : values[0];
	tile.decoration = (values.size() < 2) ? -1 : values[1];
	tile.direction = static_cast<Tile::Direction>((values.size() < 3 || values[2] < 0 || values[2] > 4) ? 0 : values[2]); 
	tile.special_flag = (values.size() <= 3) ? -1 : values[3];
}

void Map::generate_map_cache()
{
	for (int y = 0; y < get_height(); y++)
		for (int x = 0; x < get_width(); x++)
		{
			const Tile& tile = tile_map[y][x];
			if (tile.special_flag < 0)
				continue;

			if (tile.special_flag == 0)
			{
				idx_home.x = x;
				idx_home.y = y;
			}
			else
			{
				spawner_route_pool[tile.special_flag] = Route(tile_map, {x, y});
			}
		}
}
