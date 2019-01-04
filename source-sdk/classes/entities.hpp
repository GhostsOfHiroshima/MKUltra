#pragma once
#include <array>
#include "collideable.hpp"
#include "client_class.hpp"
template<typename FuncType>
__forceinline static FuncType call_virtual(void* ppClass, int index) { // ;p;
	int* pVTable = *(int**)ppClass;
	int dwAddress = pVTable[index];
	return (FuncType)(dwAddress);
}

enum move_type {
	movetype_none = 0,
	movetype_isometric,
	movetype_walk,
	movetype_step,
	movetype_fly,
	movetype_flygravity,
	movetype_vphysics,
	movetype_push,
	movetype_noclip,
	movetype_ladder,
	movetype_observer,
	movetype_custom,
	movetype_last = movetype_custom,
	movetype_max_bits = 4,
	max_movetype
};

enum entity_flags {
	fl_onground = (1 << 0),
	fl_ducking = (1 << 1),
	fl_waterjump = (1 << 2),
	fl_ontrain = (1 << 3),
	fl_inrain = (1 << 4),
	fl_frozen = (1 << 5),
	fl_atcontrols = (1 << 6),
	fl_client = (1 << 7),
	fl_fakeclient = (1 << 8),
	fl_inwater = (1 << 9),
	fl_fly = (1 << 10),
	fl_swim = (1 << 11),
	fl_conveyor = (1 << 12),
	fl_npc = (1 << 13),
	fl_godmode = (1 << 14),
	fl_notarget = (1 << 15),
	fl_aimtarget = (1 << 16),
	fl_partialground = (1 << 17),
	fl_staticprop = (1 << 18),
	fl_graphed = (1 << 19),
	fl_grenade = (1 << 20),
	fl_stepmovement = (1 << 21),
	fl_donttouch = (1 << 22),
	fl_basevelocity = (1 << 23),
	fl_worldbrush = (1 << 24),
	fl_object = (1 << 25),
	fl_killme = (1 << 26),
	fl_onfire = (1 << 27),
	fl_dissolving = (1 << 28),
	fl_transragdoll = (1 << 29),
	fl_unblockable_by_player = (1 << 30)
};
enum item_definition_indexes {
	WEAPON_NONE = 0,
	WEAPON_DEAGLE,
	WEAPON_ELITE,
	WEAPON_FIVESEVEN,
	WEAPON_GLOCK,
	WEAPON_AK47 = 7,
	WEAPON_AUG,
	WEAPON_AWP,
	WEAPON_FAMAS,
	WEAPON_G3SG1,
	WEAPON_GALILAR = 13,
	WEAPON_M249,
	WEAPON_M4A1 = 16,
	WEAPON_MAC10,
	WEAPON_P90 = 19,
	WEAPON_MP5SD = 23,
	WEAPON_UMP45,
	WEAPON_XM1014,
	WEAPON_BIZON,
	WEAPON_MAG7,
	WEAPON_NEGEV,
	WEAPON_SAWEDOFF,
	WEAPON_TEC9,
	WEAPON_TASER,
	WEAPON_HKP2000,
	WEAPON_MP7,
	WEAPON_MP9,
	WEAPON_NOVA,
	WEAPON_P250,
	WEAPON_SCAR20 = 38,
	WEAPON_SG556,
	WEAPON_SSG08,
	WEAPON_KNIFEGG,
	WEAPON_KNIFE,
	WEAPON_FLASHBANG,
	WEAPON_HEGRENADE,
	WEAPON_SMOKEGRENADE,
	WEAPON_MOLOTOV,
	WEAPON_DECOY,
	WEAPON_INCGRENADE,
	WEAPON_C4,
	WEAPON_HEALTHSHOT = 57,
	WEAPON_KNIFE_T = 59,
	WEAPON_M4A1_SILENCER,
	WEAPON_USP_SILENCER,
	WEAPON_CZ75A = 63,
	WEAPON_REVOLVER,
	WEAPON_TAGRENADE = 68,
	WEAPON_FISTS,
	WEAPON_BREACHCHARGE,
	WEAPON_TABLET = 72,
	WEAPON_MELEE = 74,
	WEAPON_AXE,
	WEAPON_HAMMER,
	WEAPON_SPANNER = 78,
	WEAPON_KNIFE_GHOST = 80,
	WEAPON_FIREBOMB,
	WEAPON_DIVERSION,
	WEAPON_FRAG_GRENADE,
	WEAPON_BAYONET = 500,
	WEAPON_KNIFE_FLIP = 505,
	WEAPON_KNIFE_GUT,
	WEAPON_KNIFE_KARAMBIT,
	WEAPON_KNIFE_M9_BAYONET,
	WEAPON_KNIFE_TACTICAL,
	WEAPON_KNIFE_FALCHION = 512,
	WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
	WEAPON_KNIFE_BUTTERFLY,
	WEAPON_KNIFE_PUSH,
	WEAPON_KNIFE_URSUS = 519,
	WEAPON_KNIFE_GYPSY_JACKKNIFE,
	WEAPON_KNIFE_STILETTO = 522,
	WEAPON_KNIFE_WIDOWMAKER
};

class entity_t {
public:
	void* animating() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x4);
	}
	void* networkable() {
		return reinterpret_cast<void*>(uintptr_t(this) + 0x8);
	}
	collideable_t* collideable() {
		using original_fn = collideable_t * (__thiscall*)(void*);
		return (*(original_fn**)this)[3](this);
	}
	c_client_class* client_class() {
		using original_fn = c_client_class * (__thiscall*)(void*);
		return (*(original_fn**)networkable())[2](networkable());
	}
	int index() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)networkable())[10](networkable());
	}
	bool is_player() {
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn**)this)[153](this);
	}
	bool is_weapon() {
		using original_fn = bool(__thiscall*)(entity_t*);
		return (*(original_fn**)this)[160](this);
	}
	bool setup_bones(matrix_t* out, int max_bones, int mask, float time) {
		if (!this) {
			return false;
		}

		using original_fn = bool(__thiscall*)(void*, matrix_t*, int, int, float);
		return (*(original_fn**)animating())[13](animating(), out, max_bones, mask, time);
	}
	model_t* model() {
		using original_fn = model_t * (__thiscall*)(void*);
		return (*(original_fn**)animating())[8](animating());
	}
	void update() {
		using original_fn = void(__thiscall*)(entity_t*);
		(*(original_fn**)this)[218](this);
	}
	int draw_model(int flags, uint8_t alpha) {
		using original_fn = int(__thiscall*)(void*, int, uint8_t);
		return (*(original_fn**)animating())[9](animating(), flags, alpha);
	}
	void set_angles(vec3_t angles) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&);
		static original_fn set_angles_fn = (original_fn)((DWORD)utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1"));
		set_angles_fn(this, angles);
	}
	void set_position(vec3_t position) {
		using original_fn = void(__thiscall*)(void*, const vec3_t&);
		static original_fn set_position_fn = (original_fn)((DWORD)utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8"));
		set_position_fn(this, position);
	}
	vec3_t &get_world_space_center() {
		vec3_t vec_origin = origin();

		vec3_t min = this->collideable()->mins() + vec_origin;
		vec3_t max = this->collideable()->maxs() + vec_origin;

		vec3_t size = max - min;
		size /= 2.f;
		size += min;

		return size;
	}

	netvar_fn(int, flags, "DT_BasePlayer->m_fFlags");
	netvar_fn(unsigned long, owner_handle, "DT_BaseEntity->m_hOwnerEntity");
	offset_fn(bool, dormant, 0xED);
	netvar_fn(float, simulation_time, "DT_BaseEntity->m_flSimulationTime");
	offset_fn(vec3_t, origin, 0x134);
	offset_fn(vec3_t, view_offset, 0x104);
	netvar_fn(int, team, "DT_BaseEntity->m_iTeamNum");
	netvar_fn(bool, spotted, "DT_BaseEntity->m_bSpotted");
};

class viewmodel_t : public entity_t {
public:
	netvar_ptr_fn(int, model_index, "DT_BaseViewModel->m_nModelIndex");
	netvar_ptr_fn(int, viewmodel_index, "DT_BaseViewModel->m_nViewModelIndex");
};

class weapon_t : public entity_t {
public:
	netvar_fn(float, next_primary_attack, "DT_BaseCombatWeapon->m_flNextPrimaryAttack");
	netvar_fn(float, next_secondary_attack, "DT_BaseCombatWeapon->m_flNextSecondaryAttack");
	netvar_fn(int, clip1_count, "DT_BaseCombatWeapon->m_iClip1");
	netvar_fn(int, clip2_count, "DT_BaseCombatWeapon->m_iClip2");
	netvar_fn(int, primary_reserve_ammo_acount, "DT_BaseCombatWeapon->m_iPrimaryReserveAmmoCount");
	netvar_fn(float, recoil_index, "DT_WeaponCSBase->m_flRecoilIndex");
	netvar_fn(short, item_definition_index, "DT_BaseAttributableItem->m_iItemDefinitionIndex");
	netvar_fn(int, zoom_level, "DT_WeaponCSBaseGun->m_zoomLevel");

	float get_innacuracy() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[471](this);
	}

	float get_spread_alternative()
	{
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[436](this);
	}


	float get_spread() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[436](this);
	}

	void update_accuracy_penalty() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[472](this);
	}
	weapon_info_t* get_weapon_data() {
		using original_fn = weapon_info_t * (__thiscall*)(void*);
		static original_fn return_func = (original_fn)((DWORD)utilities::pattern_scan(GetModuleHandleA("client_panorama.dll"), "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B"));

		return return_func(this);
	}

	bool is_knife() {
		return client_class()->class_id == CKnife || client_class()->class_id == CKnifeGG;
	}

	bool is_sniper() {
		return client_class()->class_id == CWeaponSSG08 || client_class()->class_id == CWeaponSCAR20 || client_class()->class_id == CWeaponG3SG1 || client_class()->class_id == CWeaponAug || client_class()->class_id == CWeaponSG556;
	}
};

class econ_view_item_t {
public:
	netvar_offset_fn(bool, is_initialized, "DT_ScriptCreatedItem->m_bInitialized", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
	netvar_offset_fn(short, item_definition_index, "DT_ScriptCreatedItem->m_iItemDefinitionIndex", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
	netvar_offset_fn(int, entity_level, "DT_ScriptCreatedItem->m_iEntityLevel", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
	netvar_offset_fn(int, account_id, "DT_ScriptCreatedItem->m_iAccountID", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
	netvar_offset_fn(int, item_id_low, "DT_ScriptCreatedItem->m_iItemIDLow", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
	netvar_offset_fn(int, item_id_high, "DT_ScriptCreatedItem->m_iItemIDHigh", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
	netvar_offset_fn(int, entity_quality, "DT_ScriptCreatedItem->m_iEntityQuality", netvar_manager::get().get_offset(fnv_hash("DT_AttributeContainer->m_Item")) + netvar_manager::get().get_offset(fnv_hash("DT_BaseAttributableItem->m_AttributeManager")));
};

class attributable_item_t : public entity_t {
public:
	netvar_fn(unsigned long, original_owner_xuid, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow");
	netvar_fn(int, original_owner_xuid_low, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow");
	netvar_fn(int, original_owner_xuid_high, "DT_BaseAttributableItem->m_OriginalOwnerXuidHigh");
	netvar_fn(int, fallback_stattrak, "DT_BaseAttributableItem->m_nFallbackStatTrak");
	netvar_fn(int, fallback_paint_kit, "DT_BaseAttributableItem->m_nFallbackPaintKit");
	netvar_fn(int, fallback_seed, "DT_BaseAttributableItem->m_nFallbackSeed");
	netvar_fn(float, fallback_wear, "DT_BaseAttributableItem->m_flFallbackWear");
	netvar_fn(unsigned long, world_model_handle, "DT_BaseCombatWeapon->m_hWeaponWorldModel");

	econ_view_item_t& item() {
		return *(econ_view_item_t*)this;
	}
};

class player_t : public entity_t {
public:
	netvar_fn(bool, has_defuser, "DT_CSPlayer->m_bHasDefuser");
	netvar_fn(bool, has_gun_game_immunity, "DT_CSPlayer->m_bGunGameImmunity");
	netvar_fn(int, shots_fired, "DT_CSPlayer->m_iShotsFired");
	netvar_fn(vec3_t, eye_angles, "DT_CSPlayer->m_angEyeAngles[0]");
	netvar_fn(int, armor, "DT_CSPlayer->m_ArmorValue");
	netvar_fn(bool, has_helmet, "DT_CSPlayer->m_bHasHelmet");
	netvar_fn(bool, is_scoped, "DT_CSPlayer->m_bIsScoped");;
	netvar_fn(float, lower_body_yaw, "DT_CSPlayer->m_flLowerBodyYawTarget");
	netvar_fn(float, next_attack, "DT_CSPlayer->m_flNextAttack");
	netvar_fn(float, flash_duration, "DT_CSPlayer->m_flFlashDuration");
	netvar_fn(float, flash_alpha, "DT_CSPlayer->m_flFlashMaxAlpha");
	netvar_fn(float, m_bHasNightVision, "DT_CSPlayer->m_bHasNightVision");
	netvar_fn(float, m_bNightVisionOn, "DT_CSPlayer->m_bNightVisionOn");
	netvar_fn(int, health, "DT_BasePlayer->m_iHealth");
	netvar_fn(int, life_state, "DT_BasePlayer->m_lifeState");
	netvar_fn(int, flags, "DT_BasePlayer->m_fFlags");
	netvar_fn(int, tick_base, "DT_BasePlayer->m_nTickBase");
	netvar_fn(vec3_t, punch_angle, "DT_BasePlayer->m_viewPunchAngle");
	netvar_fn(vec3_t, aim_punch_angle, "DT_BasePlayer->m_aimPunchAngle");
	netvar_fn(vec3_t, velocity, "DT_BasePlayer->m_vecVelocity[0]");
	netvar_fn(float, max_speed, "DT_BasePlayer->m_flMaxspeed");
	netvar_fn(float, m_flFOVTime, "DT_BaseEntity->m_flShadowCastDistance");
	netvar_fn(unsigned long, observer_target, "DT_BasePlayer->m_hObserverTarget");
	netvar_fn(unsigned long, active_weapon_handle, "DT_BaseCombatCharacter->m_hActiveWeapon");
	netvar_fn(int, hitbox_set, "DT_BaseAnimating->m_nHitboxSet");
	netvar_fn(float, duck_amount, "DT_CSPlayer->m_flDuckAmount");
	netvar_fn(bool, has_heavy_armor, "DT_CSPlayer->m_bHasHeavyArmor");

	void update_client_side_animations() {
		using original_fn = void(__thiscall*)(void*);
		(*(original_fn**)this)[218](this);
	}
	std::array<float, 24> & pose_parameter() {
		return *(std::array<float, 24>*)((uintptr_t)this + netvar_manager::get().get_offset(fnv_hash("DT_BaseAnimating->m_flPoseParameter")));
	}

	vec3_t & abs_origin() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[10](this);;
	}
	vec3_t & abs_angles() {
		using original_fn = vec3_t & (__thiscall*)(void*);
		return (*(original_fn**)this)[11](this);;
	}
	int	move_type() {
		return *reinterpret_cast<int*> (reinterpret_cast<uintptr_t>(this) + 0x258);
	}
	vec3_t eye_pos() {
		vec3_t ret;
		call_virtual<void(__thiscall*)(void*, vec3_t&)>(this, 279)(this, ret); // this is the real eye pos
		return ret;
	}
	matrix_t GetBoneMatrix(int BoneID)
	{
		matrix_t matrix;

		auto offset = *reinterpret_cast<uintptr_t*>(uintptr_t(this) + 0x2698);
		if (offset)
			matrix = *reinterpret_cast<matrix_t*>(offset + 0x30 * BoneID);

		return matrix;
	}
	weapon_t* active_weapon(void) {
		uintptr_t handle = active_weapon_handle();
		return reinterpret_cast<weapon_t*>(interfaces::entity_list->get_client_entity(handle));
	}
	int* weapons() {
		return reinterpret_cast<int*> (uintptr_t(this) + 0x2DE8);
	}
	bool is_valid(player_t* local_player = nullptr, bool is_player = true, bool dormant = true, bool team_check = true) {
		if (!this)
			return false;

		if (dormant)
			if (this->dormant())
				return false;

		if (team_check && local_player)
			if (this->team() == local_player->team())
				return false;

		if (is_player)
			if (!this->is_player())
				return false;

		if (this->health() <= 0)
			return false;

		return true;
	}
};