#pragma once
#include "../../dependencies/common_includes.hpp"
#include <algorithm>
#include "../menu/menu.h"
#include "../features/visuals/visuals.hpp"
std::unique_ptr<vmt_hook> hooks::client_hook;
std::unique_ptr<vmt_hook> hooks::clientmode_hook;
std::unique_ptr<vmt_hook> hooks::panel_hook;
std::unique_ptr<vmt_hook> hooks::renderview_hook;
std::unique_ptr<vmt_hook> hooks::surface_hook;
WNDPROC hooks::wndproc_original = NULL;

enum ClientFrameStage_t
{
	FRAME_UNDEFINED = -1,			// (haven't run any frames yet)
	FRAME_START,

	// A network packet is being recieved
	FRAME_NET_UPDATE_START,
	// Data has been received and we're going to start calling PostDataUpdate
	FRAME_NET_UPDATE_POSTDATAUPDATE_START,
	// Data has been received and we've called PostDataUpdate on all data recipients
	FRAME_NET_UPDATE_POSTDATAUPDATE_END,
	// We've received all packets, we can now do interpolation, prediction, etc..
	FRAME_NET_UPDATE_END,

	// We're about to start rendering the scene
	FRAME_RENDER_START,
	// We've finished rendering the scene.
	FRAME_RENDER_END
};

void hooks::initialize( ) {
	client_hook = std::make_unique<vmt_hook>( );
	clientmode_hook = std::make_unique<vmt_hook>( );
	panel_hook = std::make_unique<vmt_hook>( );
	renderview_hook = std::make_unique<vmt_hook>( );
	surface_hook = std::make_unique<vmt_hook>();

	client_hook->setup( interfaces::client );
	client_hook->hook_index( 37, reinterpret_cast< void* >( frame_stage_notify ) );

	clientmode_hook->setup( interfaces::clientmode );
	clientmode_hook->hook_index( 18, reinterpret_cast<void*>(override_view));
	clientmode_hook->hook_index( 24, reinterpret_cast< void* >( create_move ) );

	panel_hook->setup( interfaces::panel );
	panel_hook->hook_index( 41, reinterpret_cast< void* >( paint_traverse ) );

	renderview_hook->setup( interfaces::render_view );
	renderview_hook->hook_index( 9, reinterpret_cast< void* >( scene_end ) );

	surface_hook->setup(interfaces::surface);
	surface_hook->hook_index(67, reinterpret_cast<void*>(lock_cursor));

	wndproc_original = ( WNDPROC ) SetWindowLongPtrA( FindWindow( "Valve001", NULL ), GWL_WNDPROC, ( LONG ) wndproc );

	interfaces::console->get_convar( "mat_queue_mode" )->set_value( 0 );
	interfaces::console->get_convar("viewmodel_fov")->callbacks.SetSize(0);
	interfaces::console->get_convar( "viewmodel_offset_x" )->callbacks.SetSize( 0 );
	interfaces::console->get_convar( "viewmodel_offset_y" )->callbacks.SetSize(0);
	interfaces::console->get_convar("viewmodel_offset_z")->callbacks.SetSize(0);
	interfaces::console->get_convar( "mat_postprocess_enable" )->set_value( 0 );
	interfaces::console->get_convar( "crosshair" )->set_value( 1 );
	render::get( ).setup_fonts( );
}

void hooks::shutdown( ) {
	clientmode_hook->release( );
	client_hook->release( );
	panel_hook->release( );
	renderview_hook->release( );

	SetWindowLongPtrA( FindWindow( "Valve001", NULL ), GWL_WNDPROC, ( LONG ) wndproc_original );
}

bool __stdcall hooks::create_move( float frame_time, c_usercmd* user_cmd ) {
	static auto original_fn = reinterpret_cast< create_move_fn >( clientmode_hook->get_original( 24 ) )( interfaces::clientmode, frame_time, user_cmd );
	if (!user_cmd || !user_cmd->command_number)
		return original_fn;

	if (!interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()))
		return original_fn;

	static bool bPerformed = false, bLastSetting;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));


	if (interfaces::engine->is_connected() && interfaces::engine->is_in_game())
	{
	// aimbot shoot shoot pew pew
	}

	return false;
}

void __fastcall hooks::override_view(void* _this, void* _edx, c_viewsetup* setup) {
	
	reinterpret_cast<override_view_fn>(clientmode_hook->get_original(18))(interfaces::clientmode, _this, setup);

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	
	if (local_player && c_config::get().fov > 0 && c_config::get().visuals_enabled) {
		auto weapon = local_player->active_weapon();
		if (!weapon)
			return;

		static int subtraction = 0;
	
		if (weapon->is_sniper()) {
			subtraction = weapon->zoom_level() * 40;
		}
		else {
			subtraction = 0;
		}

		setup->fov = c_config::get().fov - subtraction;
	}
		
}

void synchronize_animations() {

}

void __stdcall hooks::frame_stage_notify( int frame_stage ) {
	reinterpret_cast< frame_stage_notify_fn >( client_hook->get_original( 37 ) )( interfaces::client, frame_stage );

	
}
void __stdcall hooks::paint_traverse( unsigned int panel, bool force_repaint, bool allow_force ) {
	std::string panel_name = interfaces::panel->get_panel_name( panel );

	reinterpret_cast< paint_traverse_fn >( panel_hook->get_original( 41 ) )( interfaces::panel, panel, force_repaint, allow_force );

	static unsigned int _panel = 0;
	static bool once = false;

	if ( !once ) {
		PCHAR panel_char = ( PCHAR ) interfaces::panel->get_panel_name( panel );
		if ( strstr( panel_char, "MatSystemTopPanel" ) ) {
			_panel = panel;
			once = true;
		}
	}
	else if ( _panel == panel ) {
			render::get().draw_text(1, 1, render::get().main_font, "Project MKUltra", false, color(255, 255, 255));
			render::get().draw_text(1, 16, render::get().main_font, "Start Date: Nov 16 2018", false, color(255, 255, 255));
			render::get().draw_text(1, 31, render::get().main_font, "Current Build: " __DATE__, false, color(255, 255, 255));

			c_visuals::get().run();

			c_menu::get().draw();
	}
}
#define TEXTURE_GROUP_LIGHTMAP						"Lightmaps"
#define TEXTURE_GROUP_WORLD							"World textures"
#define TEXTURE_GROUP_MODEL							"Model textures"
#define TEXTURE_GROUP_VGUI							"VGUI textures"
#define TEXTURE_GROUP_PARTICLE						"Particle textures"
#define TEXTURE_GROUP_DECAL							"Decal textures"
#define TEXTURE_GROUP_SKYBOX						"SkyBox textures"
#define TEXTURE_GROUP_CLIENT_EFFECTS				"ClientEffect textures"
#define TEXTURE_GROUP_OTHER							"Other textures"
#define TEXTURE_GROUP_PRECACHED						"Precached"				// TODO: assign texture groups to the precached materials
#define TEXTURE_GROUP_CUBE_MAP						"CubeMap textures"
#define TEXTURE_GROUP_RENDER_TARGET					"RenderTargets"
#define TEXTURE_GROUP_UNACCOUNTED					"Unaccounted textures"	// Textures that weren't assigned a texture group.
//#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER		"Static Vertex"
#define TEXTURE_GROUP_STATIC_INDEX_BUFFER			"Static Indices"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_DISP		"Displacement Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_COLOR	"Lighting Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_WORLD	"World Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_MODELS	"Model Verts"
#define TEXTURE_GROUP_STATIC_VERTEX_BUFFER_OTHER	"Other Verts"
#define TEXTURE_GROUP_DYNAMIC_INDEX_BUFFER			"Dynamic Indices"
#define TEXTURE_GROUP_DYNAMIC_VERTEX_BUFFER			"Dynamic Verts"
#define TEXTURE_GROUP_DEPTH_BUFFER					"DepthBuffer"
#define TEXTURE_GROUP_VIEW_MODEL					"ViewModel"
#define TEXTURE_GROUP_PIXEL_SHADERS					"Pixel Shaders"
#define TEXTURE_GROUP_VERTEX_SHADERS				"Vertex Shaders"
#define TEXTURE_GROUP_RENDER_TARGET_SURFACE			"RenderTarget Surfaces"
#define TEXTURE_GROUP_MORPH_TARGETS					"Morph Targets"

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	//	MATERIAL_VAR_UNUSED					  = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17), // OBSOLETE
//	MATERIAL_VAR_UNUSED					  = (1 << 18),
MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19), // OBSOLETE
MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
MATERIAL_VAR_TRANSLUCENT = (1 << 21),
MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23), // OBSOLETE
MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
MATERIAL_VAR_ENVMAPMODE = (1 << 25), // OBSOLETE
MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
MATERIAL_VAR_HALFLAMBERT = (1 << 27),
MATERIAL_VAR_WIREFRAME = (1 << 28),
MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
MATERIAL_VAR_ALPHA_MODIFIED_BY_PROXY = (1 << 30),
MATERIAL_VAR_VERTEXFOG = (1 << 31),

// NOTE: Only add flags here that either should be read from
// .vmts or can be set directly from client code. Other, internal
// flags should to into the flag enum in IMaterialInternal.h
};


void __stdcall hooks::scene_end( ) {
	reinterpret_cast< scene_end_fn >( renderview_hook->get_original( 9 ) )( interfaces::render_view );

	
	for (int i = 1; i < interfaces::globals->max_clients; ++i) {
		auto ent = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(i));
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
		if (ent && ent->is_valid(local_player)) {
			i_material *mat = NULL;
			switch (c_config::get().cham_material) {
			case 0: mat = interfaces::material_system->find_material("models/player/ct_fbi/ct_fbi_glass", TEXTURE_GROUP_OTHER); break;
			case 1: mat = interfaces::material_system->find_material("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER); break;
			case 2: mat = interfaces::material_system->find_material("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER); break;
			case 3: mat = interfaces::material_system->find_material("models/inventory_items/trophy_majors/gold", TEXTURE_GROUP_OTHER); break;
			case 4: mat = interfaces::material_system->find_material("models/gibs/glass/glass", TEXTURE_GROUP_OTHER); break;
			case 5: mat = interfaces::material_system->find_material("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER); break;
			case 6: mat = interfaces::material_system->find_material("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER); break;
			}
			
			if (mat && c_config::get().chams && c_config::get().visuals_enabled) {
				mat->set_flag(MATERIAL_VAR_IGNOREZ, true);
				interfaces::model_render->override_material(mat);
				ent->draw_model(0x1, 255);
				interfaces::model_render->override_material(nullptr);
			}
		}
	}
	
}

LRESULT __stdcall hooks::wndproc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) {
	return CallWindowProcA( wndproc_original, hwnd, message, wparam, lparam );
}

void __stdcall hooks::lock_cursor() {
	if (c_menu::get().menu_opened) {
		interfaces::surface->unlock_cursor();
		return;
	}

	reinterpret_cast<lock_cursor_fn>(surface_hook->get_original(67))(interfaces::surface);
}