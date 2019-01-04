#include "../menu.h"

void c_menu::slider(int max, std::string name, int* item, std::string suffix, int step)
{
	if (groupbox_bottom <= y_offset + 30)
		return;

	float SliderSize = 100; // 163

	float _pixel_value = max / SliderSize;

	if (c_menu::get().menu_opened) {
		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 29, y_offset + 14, SliderSize + 1, 10))
			*item = abs(mouse_pos().x - (x_offset + 29)) * _pixel_value;


		static bool pressed_subtract = false;
		static bool pressed_add = false;

		/*
		subtract
		*/

		if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 21, y_offset + 12, 8, 10))
		{
			if (pressed_subtract)
				*item -= step;
			pressed_subtract = false;
		}

		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 21, y_offset + 12, 8, 10) && !pressed_subtract)
			pressed_subtract = true;

		/*
		add
		*/

		if (!GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 22 + SliderSize, y_offset + 12, 15, 10))
		{
			if (pressed_add)
				*item += step;
			pressed_add = false;
		}

		if (GetAsyncKeyState(VK_LBUTTON) && mouse_in_params(x_offset + 22 + SliderSize, y_offset + 12, 15, 10) && !pressed_add)
			pressed_add = true;

		if (*item > max) {
			*item = max;
		}

		if (*item < 0) {
			*item = 0;
		}

	}

		std::string namedisplay;

		namedisplay += name.c_str();

		namedisplay += " (";

		namedisplay += std::to_string(*item);

		namedisplay += ")";

		render::get().draw_text(x_offset + 29, y_offset - 3, render::get().menu_font, namedisplay.c_str(), false, color(185, 185, 185, MenuAlpha_Text));

		render::get().draw_filled_rect(x_offset + 29, y_offset + 14, SliderSize, 10, color(50, 50, 50, MenuAlpha_Main));

		if (*item)
		{
			if (*item == max) //to fix dumb math stufffff bec pixel size
				render::get().draw_filled_rect(x_offset + 29, y_offset + 14, SliderSize, 10, color(195, 141, 145, MenuAlpha_Main));
			else
				render::get().draw_filled_rect(x_offset + 29, y_offset + 14, (*item / _pixel_value), 10, color(195, 141, 145, MenuAlpha_Main));
		}

		render::get().draw_outline(x_offset + 29, y_offset + 14, SliderSize, 10, color(101, 101, 101, MenuAlpha_Main));

		render::get().draw_text(x_offset + 22, y_offset + 10, render::get().menu_font, "-", false, color(185, 185, 185, MenuAlpha_Text));
		render::get().draw_text(x_offset + 20 + SliderSize + 12, y_offset + 11, render::get().menu_font, "+", false, color(185, 185, 185, MenuAlpha_Text));

		y_offset += 30;
}