// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

// Include all elements first
#include "c_element_base.hpp"
#include "c_element_label.hpp"
#include "c_element_tab_container.hpp"
#include "c_element_tab_panel.hpp"
#include "c_element_group_box.hpp"
#include "c_element_checkbox.hpp"
#include "c_element_dropdown.hpp"
#include "c_element_slidebar.hpp"
#include "c_element_spectators.hpp"
#include "c_element_window.hpp"
#include "c_configurations.hpp"

class C_MenuSettings
{
public:

	// Legit Tab

	// Rage Tab

	/// Aimbot group box
	bool rage_aimbot = true;
	bool rage_autofire = false;
	int rage_silent_aim = 1;
	int rage_target = 2;
	int rage_method = 0;
	int rage_hitbox = 0;
	bool rage_smart_aim = false;
	int rage_hitscan = 0;
	int rage_multipoint = 0;
	int rage_autowall = 0;
	int rage_minpenetration = 25;
	int rage_pointscale = 90;

	/// Accuracy group box
	int rage_resolver = 0;
	int rage_positionadjustment = 1;
	int rage_positionadjustment_max_history = 200;
	bool rage_positionadjustment_optimize = true;
	int rage_hitchance = 0;
	bool rage_nospread = true;
	bool rage_norecoil = true;

	/// Anti-Aim group box
	bool rage_antiaim = true;
	bool rage_antiaim_followtargets = true;
	int rage_antiaim_pitch = 0;
	int rage_antiaim_yaw_send = 0;
	int rage_antiaim_yaw_choke = 0;
	int rage_antiaim_custom_yaw_send = 0;
	int rage_antiaim_custom_yaw_choke = 0;
	int rage_antiaim_edge_aa = 0;

	// Visuals Tab

	// ESP
	int visuals_render = 1;
	bool visuals_box = true;
	bool visuals_outlines = true;
	bool visuals_healthbar = true;
	bool visuals_armorbar = true;
	bool visuals_information = true;

	// Chams
	bool visuals_chams_enabled = true;
	bool visuals_chams_flat = false;

	// Mofications / Removals
	bool visuals_novisrecoil = true;
	bool visuals_fastreload = false;
	bool visuals_networkinformation = true;
	bool visuals_thirdperson = false;
	bool visuals_optimisegraphics = true;
	int visuals_thirdperson_distance = 150;
	int visuals_daytime = 100;

	// Misc Tab

	/// Misc Main group box
	bool misc_autohop = true;
	int misc_autostrafer = 1;
	bool misc_circlestrafer = true;
	int misc_autobuy = 0;

	/// FakeLag group box
	int misc_fakelag_type = 0;
	int misc_fakelag_lagjump = 0;
	int misc_fakelag_choke = 0;

	/// Anti-ban group box
	bool antiban_enabled = false;
	bool antiban_safesnaps = true;
	bool antiban_safepackets = true;
	int antiban_max_snap = 39;
};

class C_Menu
{
	bool m_bOpen;
	bool m_bInsertDown1, m_bInsertDown2;
	std::vector<C_Element_Base*> pBaseElements;
public:
	HWND m_pProcess;
	bool m_bIsInGame, m_bSetup;
	C_Element_Window* window1;

	void handle();
	void setup();
	void render();
	void add_root_element(C_Element_Base* element);
};
