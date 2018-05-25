// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * THREAD_MAIN_CALL
 * Main Thread Call
 */
#pragma warning(disable: 4100)
void THREAD_MAIN_CALL()
{
	auto tStart = std::chrono::high_resolution_clock::now();

	G::console.create_console("");

	G::console.print(eColour::WHITE, XorStr("*********************************\n"));
	G::console.print(eColour::WHITE, XorStr("*                               *\n"));
	G::console.print(eColour::WHITE, XorStr("*             GUCCI             *\n"));
	G::console.print(eColour::WHITE, XorStr("*                               *\n"));
	G::console.print(eColour::WHITE, XorStr("*********************************\n"));

	G::modules.dump_module_list();
	G::interfaces.scanner.start();
	G::netvars.start();
	G::hooks.manager.start();

	//G::interfaces.cvar->setup_spoofable(G::interfaces.cvar->find_var("mat_postprocess_enable"))->set_value(0);

	auto tNano = std::chrono::duration_cast<std::chrono::nanoseconds, long long>(std::chrono::high_resolution_clock::now() - tStart).count();
	G::console.print("\n-> Gucci Loaded in %.2fs\n", static_cast<float>(tNano) / 1000000000.f);
}
