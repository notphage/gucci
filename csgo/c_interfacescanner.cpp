// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * get_interface
 * Returns the pointer to the specifc interface given
 */
template <typename T>
T C_InterfaceScanner::get_interface(const char* chModule, const char* chInterface) const
{
	static_assert(std::is_pointer<T>::value, "Type T must be a pointer type!");

	G::console.print("%s", chInterface);

	char chBuffer[0x1000];
	HINSTANCE__* pModule;

	do
		pModule = GetModuleHandleA(chModule);
	while (pModule == nullptr);

	auto fnCreateInterface = reinterpret_cast<void* (*)(const char* p1, int* p2)>(GetProcAddress(pModule, "CreateInterface"));

	for (auto i = 100; i > 0; i--)
	{
		void* pInterface;
		sprintf_s(chBuffer, "%s%03i", chInterface, i);

		if ((pInterface = fnCreateInterface(chBuffer, nullptr)) != nullptr)
		{
			G::console.print("%i = ", i);
			G::console.print(eColour::GREEN, "0x%X\n", pInterface);
			return static_cast<T>(pInterface);
		}
	}

	G::console.print(" = ");
	G::console.print(eColour::RED, "nullptr\n");

	return nullptr;
}

/*
* find_interface
* Returns the pointer to the specifc interface given using the linked list
*/
template <typename T>
T C_InterfaceScanner::find_interface(std::string chInterface)
{
	static_assert(std::is_pointer<T>::value, "Type T must be a pointer type!");
	void* Object = nullptr;

	auto version_highest = -1;

	for (auto entry : m_InterfaceList)
	{
		/*
		> Copys the cleaned interface name into a buffer
		> ex. VClient001 -> VClient
		*/
		auto tmp(entry.first);
		tmp.resize(tmp.size() - 3);

		if (chInterface != tmp)
			continue;

		/*
		> Extracts the interface version number
		*/
		auto interface_version_buffer(entry.first.substr(entry.first.length() - 3));
		auto interface_version = atoi(interface_version_buffer.c_str());

		if (interface_version > version_highest)
		{
			Object = entry.second;
			version_highest = interface_version;
		}
	}

	G::console.print("%s", chInterface.c_str());

	if (!Object)
	{
		G::console.print(" = ");
		G::console.print(eColour::RED, "nullptr\n");
	}
	else
	{
		G::console.print("%i = ", version_highest);
		G::console.print(eColour::GREEN, "0x%X\n", Object);
	}

	return static_cast<T>(Object);
}

/*
* push_back_interfaces
* Adds every interface into a map
*/
void C_InterfaceScanner::push_back_interfaces()
{
	for (auto module : G::modules.get_loaded_modules())
	{
		auto fnCreateInterface = G::modules.get_export(module.second, "CreateInterface");

		if (!fnCreateInterface)
			continue;

		m_iModules++;

		auto fnCreateInterfaceLocation = fnCreateInterface + 0x4;

		auto fnCreateInterfaceInternal = fnCreateInterfaceLocation + *reinterpret_cast<size_t*>(fnCreateInterfaceLocation + 0x1) + 0x5;
		interface_first = **reinterpret_cast<InterfaceReg***>(fnCreateInterfaceInternal + 0x6);

		if (!interface_first)
			continue;

		while (interface_first)
		{
			if (!interface_first)
				return;

			m_InterfaceList.insert_or_assign(interface_first->m_pName, interface_first->m_CreateFn());

			interface_first = interface_first->m_pNext;
		}
	}

	m_iInterfaces = m_InterfaceList.size();
}

/*
* start
* Dumps all interfaces and stores them to there respective memory
*/
void C_InterfaceScanner::start()
{
	G::console.print("\n-> Scan Interfaces\n\n");

	G::interfaces.scanner.push_back_interfaces();

	// Client Interfaces
	G::interfaces.client = G::interfaces.scanner.find_interface<C_Client*>("VClient");
	G::interfaces.prediction = G::interfaces.scanner.get_interface<C_ClientPrediction*>("client.dll", "VClientPrediction");
	G::interfaces.movement = G::interfaces.scanner.get_interface<C_GameMovement*>("client.dll", "GameMovement");
	G::interfaces.entitylist = G::interfaces.scanner.find_interface<C_ClientEntityList*>("VClientEntityList");

	// Engine Interfaces
	G::interfaces.engine = G::interfaces.scanner.find_interface<C_EngineClient*>("VEngineClient");
	G::interfaces.vgui = G::interfaces.scanner.find_interface<C_EngineVGUI*>("VEngineVGui");
	G::interfaces.eventmanager = G::interfaces.scanner.find_interface<C_EventManager*>("GAMEEVENTSMANAGER");
	G::interfaces.trace = G::interfaces.scanner.find_interface<C_EngineTrace*>("EngineTraceClient");
	G::interfaces.modelinfo = G::interfaces.scanner.find_interface<C_ModelInfo*>("VModelInfoClient");
	G::interfaces.scanner.find_interface<void*>("VEngineEffects");
	G::interfaces.modelrender = G::interfaces.scanner.find_interface<C_ModelRender*>("VEngineModel");
	G::interfaces.renderview = G::interfaces.scanner.get_interface<C_RenderView*>("engine.dll", "VEngineRenderView");
	G::interfaces.studiorender = G::interfaces.scanner.get_interface<C_StudioRender*>("studiorender.dll", "VStudioRender");

	// VSTDLIB Interfaces
	G::interfaces.cvar = G::interfaces.scanner.find_interface<C_EngineCvar*>("VEngineCvar");

	// MaterialSystem Interfaces
	G::interfaces.materialsystem = G::interfaces.scanner.get_interface<C_MaterialSystem*>("materialsystem.dll", "VMaterialSystem");

	// VGUIMatSurface Interfaces
	G::interfaces.surface = G::interfaces.scanner.get_interface<C_VGUISurface*>("vguimatsurface.dll", "VGUI_Surface");

	// VGUI2 Interfaces
	G::interfaces.panel = G::interfaces.scanner.find_interface<C_Panel*>("VGUI_Panel");

	// Physics Interfaces
	G::interfaces.physicssurface = G::interfaces.scanner.get_interface<C_PhysicsSurface*>("vphysics.dll", "VPhysicsSurfaceProps");

	// InputSystem
	G::interfaces.input = G::interfaces.scanner.get_interface<C_InputSystem*>("inputsystem.dll", "InputSystemVersion");

	// MatchMaking
	G::interfaces.matchframework = G::interfaces.scanner.get_interface<C_MatchFramework*>("matchmaking.dll", "MATCHFRAMEWORK_");

	do
	{
		G::console.print("Fetching Other data...\n");
		G::interfaces.globaldata = **reinterpret_cast<C_GlobalData***>((*reinterpret_cast<uintptr_t**>(G::interfaces.client))[0] + 27);
		G::interfaces.clientmode = **reinterpret_cast<C_ClientMode***>((*reinterpret_cast<uintptr_t**>(G::interfaces.client))[10] + 5);
		G::interfaces.cmdinput = *reinterpret_cast<C_CmdInput**>((*reinterpret_cast<uintptr_t**>(G::interfaces.client))[15] + 1);
		G::interfaces.clientstate = *reinterpret_cast<C_EnginePointerToClientState**>((*reinterpret_cast<uintptr_t**>(G::interfaces.engine))[20] + 1);
	}
	while (/*G::interfaces.globaldata == nullptr || */G::interfaces.clientmode == nullptr || G::interfaces.cmdinput == nullptr || G::interfaces.clientstate == nullptr);

	G::console.print("\nDumped %i interfaces from %i modules\n", G::interfaces.scanner.m_iInterfaces, G::interfaces.scanner.m_iModules);
}
