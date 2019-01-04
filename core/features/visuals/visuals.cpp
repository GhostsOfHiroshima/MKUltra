#include "../../../dependencies/common_includes.hpp"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <intrin.h>

void c_visuals::run() {

	run_viewmodel();
	force_crosshair();

	int screen_width, screen_height;
	interfaces::engine->get_screen_size(screen_width, screen_height);
	for (int i = 1; i <= interfaces::globals->max_clients; i++) {

		auto player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		if (player && player->is_valid(local_player, true, true, false) && c_config::get().visuals_enabled) {
			int x, y, w, h;

			player_info_t player_info;

			interfaces::engine->get_player_info(i, &player_info);

			vec3_t top, down, air, s[2];

			vec3_t adjust = vec3_t(0, 0, -18) * player->duck_amount();

			if (!(player->flags() & fl_onground) && (player->move_type() != movetype_ladder))
				air = vec3_t(0, 0, 10);
			else
				air = vec3_t(0, 0, 0);

			down = player->abs_origin() + air;

			if ((player->flags() & fl_ducking))
			{
				top = down + vec3_t(0, 0, 58) + adjust;
			}
			else {
				top = down + vec3_t(0, 0, 72) + adjust;
			}

			if (c_math::get().world_to_screen(top, s[1]) && c_math::get().world_to_screen(down, s[0])) {
				vec3_t delta = s[1] - s[0];

				h = static_cast<int>(fabs(delta.y));
				w = static_cast<int>(h / 2.0f);

				x = static_cast<int>(s[1].x - (w / 2));
				y = static_cast<int>(s[1].y);


				if (c_config::get().player_name) {
					RECT name_text_size = render::get().GetTextSize2(render::get().esp_font, player_info.name);
					render::get().draw_text(x + (w / 2) - (name_text_size.right / 2), y - 16, render::get().esp_font, player_info.name, false, color(255, 255, 255, 255));
				}

				if (c_config::get().player_box) {
					render::get().draw_outline(x, y, w, h, color(255, 255, 255, 255));
					render::get().draw_outline(x - 1, y - 1, w + 2, h + 2, color(0, 0, 0, 255));
					render::get().draw_outline(x + 1, y + 1, w - 2, h - 2, color(0, 0, 0, 255));
				}

				if (c_config::get().player_health) {
					auto health = player->health();

					if (health > 100) { // basic clamping cuz of stupid battle royale gamemode
						health = 100;
					}

					render::get().draw_filled_rect(x - 6, y, 4, h, color(0, 0, 0, 125));
					render::get().draw_filled_rect(x - 6, y, 4, (h / 100.f) * health, color(0, 185, 0, 255));
					render::get().draw_outline(x - 6, y, 4, h, color(0, 0, 0, 255));
				}

				if (c_config::get().player_weapon) {
					auto weapon = player->active_weapon();
					c_client_class* clientclass = weapon->client_class();
					render::get().draw_text(x + (w / 2), (y + h) + 1, render::get().esp_font, clientclass->network_name, true, color(255, 255, 255, 255));
				}

				if (c_config::get().player_armor) {
					auto armor = player->armor();
					render::get().draw_filled_rect((x + w) + 2, y, 4, h, color(0, 0, 0, 125));
					render::get().draw_filled_rect((x + w) + 2, y, 4, (h / 100.f) * armor, color(14, 117, 142, 255));
					render::get().draw_outline((x + w) + 2, y, 4, h, color(0, 0, 0, 255));
				}
			}
			else {  // watch your 6 g
			}
		}

	}
}


void c_visuals::run_viewmodel()
{
	interfaces::console->get_convar("viewmodel_offset_x")->set_value(c_config::get().viewmodel_x);
	interfaces::console->get_convar("viewmodel_offset_y")->set_value(c_config::get().viewmodel_y);
	interfaces::console->get_convar("viewmodel_offset_z")->set_value(c_config::get().viewmodel_z - 10);
}

void c_visuals::force_crosshair()
{
	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	static convar* weapon_debug_spread_show = interfaces::console->get_convar("weapon_debug_spread_show");

	weapon_debug_spread_show->flags &= ~fcvar_cheat;

	if (local_player && local_player->health() > 0)
	{
		weapon_debug_spread_show->set_value( local_player->is_scoped() || !c_config::get().force_crosshair ? 0 : 3);
	}
}

