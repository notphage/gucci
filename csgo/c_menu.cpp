// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * handle
 * Handles the menu
 */
void C_Menu::handle()
{
	m_pProcess = FindWindowA(nullptr, "Counter-Strike: Global Offensive");
	m_bIsInGame = GetActiveWindow() == m_pProcess;

	setup();
	render();
}

/*
 * setup
 * Sets up the menu
 */
void C_Menu::setup()
{
	if (m_bSetup)
		return;

	int SCREEN_X, SCREEN_Y;
	G::interfaces.engine->get_screen_size(SCREEN_X, SCREEN_Y);

	auto MENU_W = 630;
	auto MENU_H = 510;

	auto window = new C_Element_Window("", SCREEN_X / 2 - MENU_W / 2, SCREEN_Y / 2 - MENU_H / 2, MENU_W, MENU_H, true);
	auto tab_container = new C_Element_Tab_Container(5, 55, MENU_W - 10, MENU_H - 60, window);
	auto tab_panel = new C_Element_Tab_Panel(5, 5, MENU_W - 10, 50, {"Legit", "Rage", "Visuals", "Misc"}, 1, tab_container, window);

	// Window Addons

	///// Spectators
	//auto spectators = new C_Element_Window("Spectators", 100, 100, 250, 100, false);
	//spectators->set_enabled(false);

	//new C_Element_Spectators(10, 100, 0, 0, spectators);

	//add_root_element(spectators);

	tab_panel->set_current_tab(1);

	// Legit Tab
	tab_container->reset_item_offsets(30);
	tab_container->add(0, new C_Element_Group_Box(9, 11, MENU_W / 2 - 19, (MENU_H - 52) / 2 - 19, "Box 1"), true);
	tab_container->add(0, new C_Element_Group_Box(MENU_W / 2, 11, MENU_W / 2 - 19, (MENU_H - 52) / 2 - 19, "Box 2"), true);
	tab_container->add(0, new C_Element_Group_Box(9, (MENU_H - 54) / 2 + 3, MENU_W / 2 - 19, (MENU_H - 52) / 2 - 19, "Box 3"), true);
	tab_container->add(0, new C_Element_Group_Box(MENU_W / 2, (MENU_H - 54) / 2 + 3, MENU_W / 2 - 19, (MENU_H - 52) / 2 - 19, "Box 4"), true);

	// Rage Tab
	tab_container->reset_item_offsets(30);
	tab_container->add(1, new C_Element_Group_Box(9, 11, MENU_W / 2 - 19, MENU_H - 61 - 19, "Aimbot"), true);
	tab_container->add(1, new C_Element_Group_Box(MENU_W / 2, 11, MENU_W / 2 - 19, (MENU_H - 62) / 2 - 19, "Accuracy"), true);
	tab_container->add(1, new C_Element_Group_Box(MENU_W / 2, (MENU_H - 54) / 2 + 3, MENU_W / 2 - 19, (MENU_H - 52) / 2 - 19, "Anti-Aim"), true);

	/// Aimbot Group box
	tab_container->add(1, new C_Element_CheckBox(25, 0, 12, 12, "Enabled", &G::settings.rage_aimbot));
	tab_container->add(1, new C_Element_CheckBox(25, 0, 12, 12, "Auto-Fire", &G::settings.rage_autofire));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Silent-Aim", {"None", "Client", "Server"}, &G::settings.rage_silent_aim));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Target", {"Everyone", "My Team", "Enemy Team"}, &G::settings.rage_target));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Target By", {"Proximity", "Random"}, &G::settings.rage_method));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Hitbox", {"Head", "Neck", "Lower Neck", "Pelvis", "Body", "Thorax", "Chest"}, &G::settings.rage_hitbox));
	tab_container->add(1, new C_Element_CheckBox(25, 0, 12, 12, "Smart-Aim", &G::settings.rage_smart_aim));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Hitscan", {"Disabled", "Full Upper", "Full Upper + Lower"}, &G::settings.rage_hitscan));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Multipoint", {"Disabled", "Head", "Full"}, &G::settings.rage_multipoint));
	tab_container->add(1, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Penetration", {"Disabled", "Progressive", "Selective"}, &G::settings.rage_autowall));
	tab_container->add(1, new C_Element_SlideBar(25, 0, MENU_W / 2 - 51, 16, "Penetration Damage", "hp", &G::settings.rage_minpenetration, 1, 100));
	tab_container->add(1, new C_Element_SlideBar(25, 0, MENU_W / 2 - 51, 16, "Pointscale", "%", &G::settings.rage_pointscale, 1, 100));

	//rage_positionadjustment_optimize

	/// Accuracy Group box
	tab_container->reset_item_offsets(30);
	tab_container->add(1, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Resolver", {"Disabled", "Partial", "Full"}, &G::settings.rage_resolver));
	tab_container->add(1, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Position-Adjustment", {"Disabled", "Enabled", "History"}, &G::settings.rage_positionadjustment));
	tab_container->add(1, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Position-Adjustment History", "ms", &G::settings.rage_positionadjustment_max_history, 1, 200));
	tab_container->add(1, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Optimize Position-Adjustment", &G::settings.rage_positionadjustment_optimize));
	tab_container->add(1, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Hitchance", "%", &G::settings.rage_hitchance, 0, 100));
	tab_container->add(1, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "No-Spread", &G::settings.rage_nospread));
	tab_container->add(1, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "No-Recoil", &G::settings.rage_norecoil));

	/// Anti Aim Group Box
	tab_container->reset_item_offsets((MENU_H - 54) / 2 + 3 + 19);
	tab_container->add(1, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Enabled", &G::settings.rage_antiaim));
	tab_container->add(1, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "At Targets", &G::settings.rage_antiaim_followtargets));
	tab_container->add(1, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Pitch", {"None", "Down", "Up", "Flip Down", "Flip Up", "Fake Down", "Fake Up", "Emotion", "Jitter"}, &G::settings.rage_antiaim_pitch));

	std::vector<std::string> anti_aim_yaws = {"None", "Backward", "45 Backward", "Backward 45 Jitter", "Forward Jitter", "Sideways Jitter", "Backwards Jitter", "Sideways", "Slow Spin", "Fast Spin", "Lower-Body", "Custom"};

	tab_container->add(1, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Yaw Send", anti_aim_yaws, &G::settings.rage_antiaim_yaw_send));
	tab_container->add(1, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Custom Yaw", "°", &G::settings.rage_antiaim_custom_yaw_send, 0, 360));
	tab_container->add(1, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Yaw Choke", anti_aim_yaws, &G::settings.rage_antiaim_yaw_choke));
	tab_container->add(1, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Custom Yaw", "°", &G::settings.rage_antiaim_custom_yaw_choke, 0, 360));
	tab_container->add(1, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Edge", {"Disabled", "Away", "Fake"}, &G::settings.rage_antiaim_edge_aa));

	// Visuals Tab
	tab_container->reset_item_offsets(30);
	tab_container->add(2, new C_Element_Group_Box(9, 11, MENU_W / 2 - 19, (MENU_H - 62) / 2 - 19, "ESP"), true);
	tab_container->add(2, new C_Element_Group_Box(9, (MENU_H - 54) / 2 + 3, MENU_W / 2 - 19, (MENU_H - 62) / 2 - 19, "Chams"), true);
	tab_container->add(2, new C_Element_Group_Box(MENU_W / 2, 11, MENU_W / 2 - 19, (MENU_H - 62) / 2 - 19, "Removals / Modifications"), true);

	/// Esp Settings Group box
	tab_container->add(2, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Render", {"Nobody", "Everyone", "My Team", "Enemy Team"}, &G::settings.visuals_render));
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Box", &G::settings.visuals_box));
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Outlines", &G::settings.visuals_outlines));
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Health-bar", &G::settings.visuals_healthbar));
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Armor-bar", &G::settings.visuals_armorbar));
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Information", &G::settings.visuals_information));

	// Chams
	tab_container->reset_item_offsets((MENU_H - 54) / 2 + 3 + 19);
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Enabled", &G::settings.visuals_chams_enabled));
	tab_container->add(2, new C_Element_CheckBox(25, 0, 12, 12, "Flat", &G::settings.visuals_chams_flat));

	/// Removals / Modifications Group box
	tab_container->reset_item_offsets(30);
	tab_container->add(2, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "No-Visual Recoil", &G::settings.visuals_novisrecoil));
	tab_container->add(2, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Optimise Graphics", &G::settings.visuals_optimisegraphics));
	tab_container->add(2, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Fast-Reload", &G::settings.visuals_fastreload));
	tab_container->add(2, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Network-Information", &G::settings.visuals_networkinformation));
	tab_container->add(2, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Thirdperson", &G::settings.visuals_thirdperson));
	tab_container->add(2, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Thirdperson Distance", "units", &G::settings.visuals_thirdperson_distance, 50, 200));
	tab_container->add(2, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Day-Time", "%", &G::settings.visuals_daytime, 0, 100));
	//tab_container->add(2, new C_Element_CheckBox(MENU_W / 2 + 16, 0, 12, 12, "Show Spectators", &spectators->m_bPanelEnabled));

	// Misc Tab
	tab_container->reset_item_offsets(30);
	tab_container->add(3, new C_Element_Group_Box(9, 11, MENU_W / 2 - 19, (MENU_H - 62) / 2 - 19, "Main"), true);
	tab_container->add(3, new C_Element_Group_Box(9, (MENU_H - 54) / 2 + 3, MENU_W / 2 - 19, (MENU_H - 62) / 2 - 19, "Anti-Ban"), true);
	tab_container->add(3, new C_Element_Group_Box(MENU_W / 2, (MENU_H - 54) / 2 + 3, MENU_W / 2 - 19, (MENU_H - 52) / 2 - 19, "FakeLag"), true);

	/// Misc Main Group Box
	tab_container->add(3, new C_Element_CheckBox(25, 0, 12, 12, "Auto-hop", &G::settings.misc_autohop));
	tab_container->add(3, new C_Element_CheckBox(25, 0, 12, 12, "Circle-Strafer", &G::settings.misc_circlestrafer));
	tab_container->add(3, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Auto-Strafer", {"Disabled", "Silent"}, &G::settings.misc_autostrafer));
	tab_container->add(3, new C_Element_DropDown(25, 0, MENU_W / 2 - 51, 20, "Buy Kit", { "No Kit", "Full", "AK47 Full", "Negev Full", "Auto Full", "AWP Full" }, &G::settings.misc_autobuy));

	/// Fakelag Group Box
	tab_container->reset_item_offsets((MENU_H - 54) / 2 + 3 + 19);
	tab_container->add(3, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Type", {"None", "Factorial", "Adaptive"}, &G::settings.misc_fakelag_type));
	tab_container->add(3, new C_Element_DropDown(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 20, "Lag Jump", {"None", "Break", "Take off"}, &G::settings.misc_fakelag_lagjump));
	tab_container->add(3, new C_Element_SlideBar(MENU_W / 2 + 16, 0, MENU_W / 2 - 51, 16, "Choke", "ticks", &G::settings.misc_fakelag_choke, 0, 14));

	/// Anti Ban Group Box
	tab_container->reset_item_offsets((MENU_H - 54) / 2 + 3 + 19);
	tab_container->add(3, new C_Element_CheckBox(25, 0, 12, 12, "Enabled", &G::settings.antiban_enabled));
	tab_container->add(3, new C_Element_CheckBox(25, 0, 12, 12, "Safe Snaps", &G::settings.antiban_safesnaps));
	tab_container->add(3, new C_Element_CheckBox(25, 0, 12, 12, "Safe Packets", &G::settings.antiban_safepackets));
	tab_container->add(3, new C_Element_SlideBar(25, 0, MENU_W / 2 - 51, 16, "Maximum Snap", "°", &G::settings.antiban_max_snap, 0, 180));

	// Setup configuration data
	//G::interfaces.data->register_data("test_option", (DWORD*)G::settings.rage_aimbot);
	//G::interfaces.data->save_data("gucci_data.dat");

	window1 = window;
	add_root_element(window);

	m_bSetup = true;
}

/*
 * render
 * Renders the entire menu
 */
void C_Menu::render()
{
	m_bInsertDown1 = m_bInsertDown2;
	m_bInsertDown2 = GetAsyncKeyState(0x2D);

	if (!m_bInsertDown1 && m_bInsertDown2)
	{
		m_bOpen = !m_bOpen;

		G::interfaces.input->input_enabled(!m_bOpen);
		G::interfaces.engine->client_cmd(m_bOpen ? "cl_mouseenable 0" : "cl_mouseenable 1");
	}

	window1->set_enabled(m_bOpen);

	if (window1->get_enabled())
	{
		G::interfaces.input->input_enabled(false);
		G::interfaces.engine->client_cmd("cl_mouseenable 0");
	}

	auto paint_id = 0;

	for (auto pElement : pBaseElements)
		if (pElement != nullptr && pElement->get_enabled())
		{
			pElement->handle_paint(paint_id);
			pElement->handle_think();

			//auto pWindow = static_cast<C_Element_Window*>(pElement);

			//if (pWindow != nullptr && pWindow->get_focused_element() != nullptr)
			//{
			//	pWindow->get_focused_element()->handle_paint();
			//	pWindow->get_focused_element()->handle_think();
			//	pWindow->draw_cursor();
			//}

			paint_id++;
		}
}

/*
 * add_root_element
 * Adds the element to a root drawing table
 */
void C_Menu::add_root_element(C_Element_Base* element)
{
	if (element != nullptr)
		pBaseElements.push_back(element);
}
