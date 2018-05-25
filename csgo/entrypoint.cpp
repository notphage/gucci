// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

/*
 * entrypoint
 * Thread call (just before peheader erased)
 */
HMODULE pModulePtr;

unsigned __stdcall entrypoint(void*)
{
	if (pModulePtr == nullptr)
		return 0x1;

	THREAD_MAIN_CALL();

	return 0x0;
}

/*
 * DllMain
 * Module Entry Point
 */
int __stdcall DllMain(HMODULE hModule, DWORD dwCallReason, void*)
{
	/*
	 * erase_pe_headers
	 * Erases all PE Headers for the specfic module given
	 */
	auto erase_pe_headers = [](HMODULE hModule)
			{
				if (hModule == nullptr)
					return false;

				auto DOS_HEADERS = reinterpret_cast<_IMAGE_DOS_HEADER*>(hModule);
				auto NT_HEADERS = reinterpret_cast<_IMAGE_NT_HEADERS*>(reinterpret_cast<long>(DOS_HEADERS) + DOS_HEADERS->e_lfanew);
				DWORD dwProtectionFlags;

				// Clear DOS Headers
				if (DOS_HEADERS != nullptr)
				{
					if (VirtualProtect(DOS_HEADERS, sizeof _IMAGE_DOS_HEADER, 0x04, &dwProtectionFlags))
					{
						for (auto i = 0x0; i < sizeof _IMAGE_DOS_HEADER; i++)
							*reinterpret_cast<DWORD*>(reinterpret_cast<DWORD*>(DOS_HEADERS) + i) = 0x0;

						VirtualProtect(DOS_HEADERS, sizeof _IMAGE_DOS_HEADER, dwProtectionFlags, &dwProtectionFlags);
					}
				}

				// Clear NT Headers
				if (NT_HEADERS != nullptr)
				{
					if (VirtualProtect(NT_HEADERS, sizeof _IMAGE_NT_HEADERS, 0x04, &dwProtectionFlags))
					{
						for (auto i = 0x0; i < sizeof _IMAGE_NT_HEADERS; i++)
							*reinterpret_cast<DWORD*>(reinterpret_cast<DWORD*>(NT_HEADERS) + i) = 0x0;

						VirtualProtect(NT_HEADERS, sizeof _IMAGE_NT_HEADERS, dwProtectionFlags, &dwProtectionFlags);
					}
				}

				return true;
			};

	DisableThreadLibraryCalls(hModule);

	switch (dwCallReason)
	{
		case DLL_PROCESS_ATTACH:
			{
				pModulePtr = hModule;
				CloseHandle(reinterpret_cast<void*>(_beginthreadex(nullptr, 0x0, &entrypoint, nullptr, 0x0, nullptr)));

				break;
			}
		case DLL_THREAD_ATTACH:
			erase_pe_headers(hModule);
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			_endthreadex(0x0);
			break;
		default:
			break;
	}

	return 1;
}
