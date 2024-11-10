#pragma once

#include <SDL.h>
#include <SDL_rect.h>
#include <vector>

#include <map/tile.h>

class Route
{
public:
	using IdxList = std::vector<SDL_Point>;

public:
	
	Route(const TileMap& map, const SDL_Point& idx_origin);

	Route() = default;
	~Route() = default;

	const IdxList& get_route() const;

protected:


private:
	IdxList idx_list;

private:
	bool check_duplicate_point(const SDL_Point& target);

};
