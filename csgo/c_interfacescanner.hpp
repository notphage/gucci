// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * C_InterfaceScanner
 * A Class used for scanning interfaces
 */
class C_InterfaceScanner
{
	std::map<std::string, void*> m_InterfaceList;
	int m_iInterfaces;
	int m_iModules;

	struct InterfaceReg
	{
		using interfaceFn = void*(*)();

		interfaceFn m_CreateFn;
		const char* m_pName;
		InterfaceReg* m_pNext;
	}* interface_first = nullptr;

public:
	C_InterfaceScanner(const std::map<std::string, void*>& pairs, int i_interfaces, int i_modules, InterfaceReg* interface_first)
		: m_InterfaceList(pairs),
		  m_iInterfaces(i_interfaces),
		  m_iModules(i_modules),
		  interface_first(interface_first)
	{
	}

	C_InterfaceScanner(): m_iInterfaces(0), m_iModules(0)
	{
	}

private:
	void push_back_interfaces();
public:
	template <class T>
	T get_interface(const char* chModule, const char* chInterface) const;
	template <typename T>
	T find_interface(std::string chInterface);
	static void start();
};
