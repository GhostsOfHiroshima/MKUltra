#include "menu.h"
#include "config saving/config saving.h"
/*
	Menu framework credits to stickrpg
*/

vec2_t c_menu::mouse_pos()
{
	POINT mouse_position;
	GetCursorPos(&mouse_position);
	ScreenToClient(FindWindow(0, "Counter-Strike: Global Offensive"), &mouse_position);
	return { static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y) };
}
bool c_menu::mouse_in_params(int x, int y, int x2, int y2) {
	if (mouse_pos().x > x && mouse_pos().y > y && mouse_pos().x < x2 + x && mouse_pos().y < y2 + y)
		return true;
	return false;
}

enum TABS {
	Aimbot = 0,
	Visuals = 1,
	Misc = 2
};

bool test = false;
int testcombo = 0;
int test_slider;
void c_menu::draw()
{
	static bool _pressed = true;

	if (!_pressed && GetAsyncKeyState(VK_INSERT))
		_pressed = true;
	else if (_pressed && !GetAsyncKeyState(VK_INSERT))
	{
		_pressed = false;
		menu_opened = !menu_opened;

		interfaces::inputsystem->enable_input(!menu_opened);
	}
	interfaces::engine->get_screen_size(screen_width, screen_width);
	static vec2_t _mouse_pos;

	static int _drag_x = 300;
	static int _drag_y = 300;
	static int _width = 480;
	static int _height = 340;

	static bool _dragging = false;
	bool _click = false;
	static bool _resizing = false;
	if (menu_opened)
	{
		MenuAlpha_Main = min(MenuAlpha_Main + 15, 255);
		MenuAlpha_Text = min(MenuAlpha_Text + 5, 255);

		if (GetAsyncKeyState(VK_LBUTTON))
			_click = true;

		vec2_t _mouse_pos = mouse_pos();

		if (_dragging && !_click)
			_dragging = false;

		if (_resizing && !_click)
			_resizing = false;

		if (_dragging && _click)
		{
			_pos.x = _mouse_pos.x - _drag_x;
			_pos.y = _mouse_pos.y - _drag_y;
		}

		
		//if (_resizing && _click) {
		//	_width = _mouse_pos.x - _pos.x;
		//	_height = _mouse_pos.y - _pos.y;

		//	if (_width < 480) _width = 480;
		//	if (_height < 340) _height = 340;

		//	if (_width > 960) _width = 960;
		//	if (_height > 680) _height = 680;
		//}
		

		if (mouse_in_params(_pos.x, _pos.y, _width, _height) && !(mouse_in_params(_pos.x + 20, _pos.y + 20, _width - 10, _height - 10)))
		{
			_dragging = true;
			_drag_x = _mouse_pos.x - _pos.x;
			_drag_y = _mouse_pos.y - _pos.y;
		}

	//	if (mouse_in_params(_pos.x + 20, _pos.y + 20, _width - 10, _height - 10))
	//	{
	//		_resizing = true;
	//	}
	}
	else {
		MenuAlpha_Main = max(MenuAlpha_Main - 15, 0);
		MenuAlpha_Text = max(MenuAlpha_Text - 25, 0);
	}

		render::get().draw_filled_rect(_pos.x, _pos.y, _width, _height, color(50, 50, 50, MenuAlpha_Main));

		render::get().draw_filled_rect(_pos.x, _pos.y + 21, 100, _height - 21, color(46, 46, 46, MenuAlpha_Main));

		render::get().draw_filled_rect(_pos.x, _pos.y + 20, _width, 1, color(195, 141, 145, MenuAlpha_Main));

		render::get().draw_filled_rect(_pos.x + 100, _pos.y + 21, 1, _height - 21, color(37, 37, 37, MenuAlpha_Main));

		render::get().draw_outline(_pos.x, _pos.y, _width, _height, color(0, 0, 0, MenuAlpha_Main / 3));

		render::get().draw_text(_pos.x + 10, _pos.y + 2, render::get().menu_font, "project mkultra",  false, color(180, 180, 180, MenuAlpha_Text));

		int in_sizew = _height - 32;

		static int tab_selected = 0;
		static const int tab_amount = 3;
		static std::string tab_names[tab_amount] = { "A", "B", "C" };
		
		for (int i = 0; i < tab_amount; i++)
		{
			RECT text_size = render::get().GetTextSize2(render::get().tab_font, tab_names[i].c_str());

			int tab_area[4] = { _pos.x, _pos.y + 20 + i * (in_sizew / tab_amount), 100, (in_sizew / tab_amount) };

			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(tab_area[0], tab_area[1], tab_area[2], tab_area[3]))
				tab_selected = i;

			if (tab_selected == i)
				render::get().draw_text(tab_area[0] + (tab_area[2] / 2) - (text_size.right / 2), tab_area[1] + (tab_area[3] / 2) - (text_size.bottom / 2), render::get().tab_font, tab_names[i].c_str(), false, color(185, 185, 185, MenuAlpha_Text));
			else
				render::get().draw_text(tab_area[0] + (tab_area[2] / 2) - (text_size.right / 2), tab_area[1] + (tab_area[3] / 2) - (text_size.bottom / 2), render::get().tab_font, tab_names[i].c_str(), false, color(125, 125, 125, MenuAlpha_Text));
		}

		if (tab_selected == Visuals) {
			groupbox(106, 31, 180, 300, "players");
			checkbox("active", &c_config::get().visuals_enabled);
			checkbox("name", &c_config::get().player_name);
			checkbox("box", &c_config::get().player_box);
			checkbox("health", &c_config::get().player_health);
			checkbox("weapon", &c_config::get().player_weapon);
			checkbox("armor", &c_config::get().player_armor);
			checkbox("chams", &c_config::get().chams);
			static std::string test_combobox[7] = { "platinum", "glass", "crystal clear", "gold", "chrome", "plastic", "crystal blue" };

			if (c_config::get().chams) {
				combobox(7, "cham material", test_combobox, &c_config::get().cham_material);
			}
			

			groupbox(294, 31, 180, 300, "effects");
			checkbox("force crosshair", &c_config::get().force_crosshair);
			slider(10, "viewmodel x", &c_config::get().viewmodel_x, "%", 1);
			slider(10, "viewmodel y", &c_config::get().viewmodel_y, "%", 1);
			slider(20, "viewmodel z", &c_config::get().viewmodel_z, "%", 1);
			slider(135, "field of view", &c_config::get().fov, "%", 1);
		}
		else if (tab_selected == Misc) {
			groupbox(106, 31, 180, 300, "Main");

			groupbox(294, 31, 180, 300, "Config");
			checkbox("save", &c_config::get().misc_save_config);
			checkbox("load", &c_config::get().misc_load_config);
		}
		
		if (c_config::get().misc_save_config) {
			Config->Save();
			c_config::get().misc_save_config = false;
		}

		if (c_config::get().misc_load_config) {
			Config->Load();
			c_config::get().misc_load_config = false;
		}

}

void c_menu::draw_radar()
{


	static int _drag_x = 300;
	static int _drag_y = 300;
	static int _width = 200;
	static int _height = 200;

	static bool _dragging = false;
	bool _click = false;
	static bool _resizing = false;


		if (GetAsyncKeyState(VK_LBUTTON))
			_click = true;

		vec2_t _mouse_pos = mouse_pos();

		if (_dragging && !_click)
			_dragging = false;

		if (_resizing && !_click)
			_resizing = false;

		if (_dragging && _click)
		{
			_pos_radar.x = _mouse_pos.x - _drag_x;
			_pos_radar.y = _mouse_pos.y - _drag_y;
		}

		if (mouse_in_params(_pos_radar.x, _pos_radar.y, _width, _height) && !(mouse_in_params(_pos_radar.x + 20, _pos_radar.y + 20, _width - 10, _height - 10)))
		{
			_dragging = true;
			_drag_x = _mouse_pos.x - _pos_radar.x;
			_drag_y = _mouse_pos.y - _pos_radar.y;
		}

	//

	render::get().draw_filled_rect(_pos_radar.x, _pos_radar.y, _width, _height, color(50, 50, 50, 255));

	render::get().draw_filled_rect(_pos_radar.x, _pos_radar.y + 20, _width, _height - 20, color(46, 46, 46, 255));

	render::get().draw_filled_rect(_pos_radar.x, _pos_radar.y + 20, _width, 1, color(195, 141, 145, 255));

	render::get().draw_outline(_pos_radar.x, _pos_radar.y, _width, _height, color(0, 0, 0, 255 / 3));

	render::get().draw_text(_pos_radar.x + 10, _pos_radar.y + 2, render::get().menu_font, "radar", false, color(180, 180, 180, 255));
}