#pragma once
#include "../../dependencies/utilities/singleton.hpp"
class c_config : public singleton< c_config > {
private:

public:
	/*--------------------------------------*/
	bool visuals_enabled = false;	// VISUAL SETTINGS
	/*--------------------------------------*/
	bool player_name = false;
	bool player_box = false;
	bool player_health = false;
	bool player_weapon = false;
	bool player_armor = false;
	bool flash_indicator = false;
	bool chams = false;
	int cham_material = 0;
	int box_red = 255, box_blue = 255, box_green = 255, box_alpha = 255;

	int viewmodel_x = 2;
	int viewmodel_y = 3;
	int viewmodel_z = 9;
	int fov = 0;
	bool force_crosshair = false;
	/*--------------------------------------*/
												// MISC SETTINGS
	/*--------------------------------------*/

	bool misc_save_config = false;
	bool misc_load_config = false;
};