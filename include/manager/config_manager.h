#pragma once

#include <SDL_rect.h>
#include <manager/manager.h>
#include <map/map.h>
#include <wave/wave.h>

#include <SDL.h>
#include <string>
#include <cjson/cJSON.h>

class ConfigManager : public Manager<ConfigManager>
{
	friend class Manager<ConfigManager>;

public:

	struct BasicTemplate
	{
		std::string window_title = u8"TowerDefence";
		int window_width = 1280;
		int window_height = 720;
	};

	struct PlayerTemplate
	{
		double speed = 5;
		double normal_attack_interval = 0.5;
		double normal_attack_damage = 10;
		double skill_interval = 10;
		double skill_damage = 5;
	};

	struct TowerTemplate
	{
		double interval[10] = {1};
		double damage[10] = {25};
		double view_range[10] = {3};
		double cost[10] = {10};
		double upgrade_cost[9] = {10};
	};

	struct EnemyTemplate
	{
		double hp = 20;
		double speed = 1;
		double damage = 1;
		double reward_ratio = 0.8;
		double recover_interval = 100;
		double recover_range = -1;
		double recover_intensity = 10;
	};

public:
	Map map;
	std::vector<Wave> wave_list;

	int level_archer = 0;
	int level_axeman = 0;
	int level_gunner = 0;

	bool is_game_win = true;
	bool is_game_over = false;
	SDL_Rect rect_tile_map = {0};

	BasicTemplate basic_template;
	
	PlayerTemplate player_template;

	TowerTemplate archer_template;
	TowerTemplate axeman_template;
	TowerTemplate gunner_template;

	EnemyTemplate slim_template;
	EnemyTemplate king_slim_template;
	EnemyTemplate skeleton_template;
	EnemyTemplate goblin_template;
	EnemyTemplate goblin_priest_template;

	const double num_initial_hp = 10;
	const double num_initial_coin = 100;
	const double num_coin_prop = 10;

public:
	// 加载关卡配置信息(波次信息 -- level.json)
	bool load_level_config(const std::string& path);

	// 加载玩家以及敌人相关数据 -- config.json
	bool load_game_config(const std::string& path);

protected:
	ConfigManager() = default;
	~ConfigManager() = default;

private:
	void parse_basic_template(BasicTemplate& tpl, cJSON* json_root);
	void parse_player_template(PlayerTemplate& tpl, cJSON* json_root);
	void parse_tower_template(TowerTemplate& tpl, cJSON* json_root);
	void parse_enemy_template(EnemyTemplate& tpl, cJSON* json_root);
	
	void parse_number_array(double *ary, int max_len, cJSON* json_root);

};
