#include "../menu.h"

void c_menu::combobox(int size, std::string name, std::string* itemname, int* item)
{
	if (groupbox_bottom <= y_offset + 41)
		return;

	bool pressed = false;
	bool open = false;
	static bool selected_opened = false;
	static bool click_rest;
	static bool rest;
	static std::string name_selected;

	int ComboSize = 100; // 163

	if (c_menu::get().menu_opened) {
		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 25, y_offset + 14, ComboSize, 17) && !click_rest)
		{
			name_selected = name;
			pressed = true;
			click_rest = true;
		}
		else if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 25, y_offset + 14, ComboSize, 17))
			click_rest = false;

		if (pressed)
		{
			if (!rest)
				selected_opened = !selected_opened;
			rest = true;
		}
		else
			rest = false;

		if (name_selected == name)
			open = selected_opened;

	}

	render::get().draw_text(x_offset + 29, y_offset - 2, render::get().menu_font, name.c_str(), false, color(185, 185, 185, MenuAlpha_Text));
	render::get().draw_filled_rect(x_offset + 29, y_offset + 14, ComboSize, 17, color(50, 50, 50, MenuAlpha_Main));
	render::get().draw_outline(x_offset + 29, y_offset + 14, ComboSize, 17, color(101, 101, 101, MenuAlpha_Main));

	if (open)
	{
		render::get().draw_filled_rect(x_offset + 29, y_offset + 14 + 21, ComboSize, (size * 16), color(50, 50, 50, MenuAlpha_Main));
		render::get().draw_outline(x_offset + 29, y_offset + 14 + 21, ComboSize, (size * 16), color(101, 101, 101, MenuAlpha_Main));

		for (int i = 0; i < size; i++)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 29, y_offset + 34 + i * 16, ComboSize, 16))
				*item = i;

			if (i == *item)
				render::get().draw_text(x_offset + 29 + 10, y_offset + 35 + i * 16, render::get().menu_font, itemname[i].c_str(), false, color(185, 185, 185, MenuAlpha_Text));
			else
				render::get().draw_text(x_offset + 29 + 10, y_offset + 35 + i * 16, render::get().menu_font, itemname[i].c_str(), false, color(155, 155, 155, MenuAlpha_Text));
		}
	}

	render::get().draw_line(x_offset + 29 + ComboSize - 14, y_offset + 13 + 7, x_offset + 29 + ComboSize - 7, y_offset + 13 + 7, color(101, 101, 101, MenuAlpha_Main));
	render::get().draw_line(x_offset + 29 + ComboSize - 14, y_offset + 13 + 9, x_offset + 29 + ComboSize - 7, y_offset + 13 + 9, color(101, 101, 101, MenuAlpha_Main));
	render::get().draw_line(x_offset + 29 + ComboSize - 14, y_offset + 13 + 11, x_offset + 29 + ComboSize - 7, y_offset + 13 + 11, color(101, 101, 101, MenuAlpha_Main));

	render::get().draw_text(x_offset + 38, y_offset + 15, render::get().menu_font, itemname[*item].c_str(), false, color(185, 185, 185, MenuAlpha_Text));

	if (open) // i added 1 more to 42 bec the space between the main box and the drop down
		y_offset += 42 + (size * 16);
	else
		y_offset += 41;
}