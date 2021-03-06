#include "config saving.h"
#include "../config.h"
#include <Windows.h>
#include <Psapi.h>
#include <lmcons.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <shlobj.h>
#include <time.h>
#include <random>
#include <sstream>
#include <fstream>
#include <shlwapi.h>
#include <iomanip>
#include <ctime>

/*
Credits: A5
Side Notes: Baby you're cute for letting me use your config shit <3
*/

void CConfig::Setup()
{
	SetupValue(c_config::get().visuals_enabled, false, "Visuals", "Enabled");
	SetupValue(c_config::get().player_name, false, "Visuals", "Name");
	SetupValue(c_config::get().player_box, false, "Visuals", "Box");
	SetupValue(c_config::get().player_health, false, "Visuals", "Health");
	SetupValue(c_config::get().player_armor, false, "Visuals", "Armor");
	SetupValue(c_config::get().player_weapon, false, "Visuals", "Weapon");
	SetupValue(c_config::get().viewmodel_x, 2, "Visuals", "Viewmodel_x");
	SetupValue(c_config::get().viewmodel_y, 3, "Visuals", "Viewmodel_y");
	SetupValue(c_config::get().viewmodel_z, 9, "Visuals", "Viewmodel_z");
	SetupValue(c_config::get().force_crosshair, false, "Visuals", "Force_crosshair");
	SetupValue(c_config::get().fov, 0, "Visuals", "Fov");
	SetupValue(c_config::get().chams, false, "Visuals", "Chams");
	SetupValue(c_config::get().cham_material, 0, "Visuals", "Cham_material");
}

void CConfig::SetupValue(int& value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue< int >(category, name, &value));
}

void CConfig::SetupValue(float& value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue< float >(category, name, &value));
}

void CConfig::SetupValue(bool& value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue< bool >(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\mkultra\\";
		file = std::string(path) + "\\mkultra\\config.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\mkultra\\";
		file = std::string(path) + "\\mkultra\\config.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

CConfig* Config = new CConfig();
