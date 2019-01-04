#pragma once
#pragma once
#include <vector>
#include <memory>
#include <random>
#include <iostream>
#include <ShlObj_core.h>
#include <functional>
#include "../../dependencies/utilities/render.hpp"
#include "../../dependencies/common_includes.hpp"
class c_menu : public singleton<c_menu> {
public:
	bool menu_opened;
	vec2_t mouse_pos();
	bool mouse_in_params(int x, int y, int x2, int y2);
	void draw();
	void draw_radar();
private:
	vec3_t _pos = vec3_t(500, 200, 0);
	vec3_t _pos_radar = vec3_t(0, 0, 0);
	int screen_width;
	int screen_height;
	int y_offset;
	int x_offset;
	int MenuAlpha_Main;
	int MenuAlpha_Text;
	int groupbox_scroll_add;
	int groupbox_width;
	int groupbox_bottom;
	int groupbox_top;

	void groupbox(int x, int y, int w, int h, std::string name);
	void checkbox(std::string name, bool* item);
	void combobox(int size, std::string name, std::string *itemname, int* item);
	void color_selector(std::string name, int* red, int* blue, int* green, int* alpha);
	void slider(int max, std::string name, int * item, std::string suffix, int step);
	void keybind(int * item, std::string name);
};