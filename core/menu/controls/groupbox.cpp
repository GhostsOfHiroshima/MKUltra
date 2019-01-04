#include "../menu.h"

void c_menu::groupbox(int x, int y, int w, int h, std::string name)
{
	render::get().draw_outline(_pos.x + x, _pos.y + y, w, h, color(20, 20, 20, MenuAlpha_Main / 2));
	render::get().draw_outline(_pos.x + (x + 1), _pos.y + (y + 1), w - 2, h - 2, color(70, 70, 70, MenuAlpha_Main));

	RECT text_size = render::get().GetTextSize2(render::get().menu_font, name.c_str());
	render::get().draw_filled_rect((((_pos.x + x) + (w / 2)) - (text_size.right / 2)) - 3, _pos.y + y, text_size.right + 6, 2, color(44, 44, 44, MenuAlpha_Main));

	render::get().draw_text((((_pos.x + x) + (w / 2)) - (text_size.right / 2)), (_pos.y + y - 6), render::get().menu_font, name.c_str(), false, color(185, 185, 185, MenuAlpha_Text));

	/*
		Make scrollable!
	*/

	y_offset = (_pos.y + (y + 12));
	x_offset = _pos.x + x;
	groupbox_bottom = (_pos.y + (y + h));
	groupbox_top = (_pos.y + y);
	groupbox_width = (_pos.x + (x + w));
}