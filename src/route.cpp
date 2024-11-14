#include <map/route.h>
#include <iostream>


Route::Route(const TileMap& map, const SDL_Point& idx_origin)
{
	size_t map_width = map[0].size();
	size_t map_height = map.size();
	SDL_Point idx_next = idx_origin;

	while (true)
	{
		if (idx_next.x >= map_width || idx_next.y >= map_height)
			break;

		if (check_duplicate_point(idx_next))
			break;
		else
			idx_list.push_back(idx_next);

		bool is_next_dir_exist = true;
		const Tile& tile = map[idx_next.y][idx_next.x];

		// update next point
		switch (tile.direction) 
		{
		case Tile::Direction::Up:
			idx_next.y--;
			break;
		case Tile::Direction::Down:
			idx_next.y++;
			break;
		case Tile::Direction::Left:
			idx_next.x--;
			break;
		case Tile::Direction::Right:
			idx_next.x++;
			break;
		default:
			is_next_dir_exist = false;
			break;
		}

		if (!is_next_dir_exist)
			break;

	}
}

const Route::IdxList& Route::get_route() const
{
	return idx_list;
}

bool Route::check_duplicate_point(const SDL_Point& target)
{
	for (const auto& point : idx_list)
		if (point.x == target.x && point.y == target.y)
			return true;

	return false;
}
