#include "../menu.h"

void c_menu::checkbox(std::string name, bool* item)
{
	if (groupbox_bottom <= y_offset + 16)
		return;

	if (groupbox_top >= y_offset + 16)
		return;

	int size = 12;

	static bool pressed = false;

	auto text_size = render::get().GetTextSize2(render::get().menu_font, name.c_str());

	if (c_menu::get().menu_opened) {
		if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 7, y_offset, size + text_size.right, size))
		{
			if (pressed)
				*item = !*item;
			pressed = false;
		}

		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 7, y_offset, size + text_size.right, size) && !pressed)
			pressed = true;

	}

	if (*item == true)
		render::get().draw_filled_rect(x_offset + 8, y_offset, size, size, color(195, 141, 145, MenuAlpha_Main));
	else
		render::get().draw_filled_rect(x_offset + 8, y_offset, size, size, color(50, 50, 50, MenuAlpha_Main));

	render::get().draw_outline(x_offset + 8, y_offset, size, size, color(101, 101, 101, MenuAlpha_Main));

	render::get().draw_text(x_offset + 29, y_offset - 2, render::get().menu_font, name.c_str(), false, color(185, 185, 185, MenuAlpha_Text));

	y_offset += 16;
}