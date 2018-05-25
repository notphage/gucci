// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

/*
 * C_ClientPropData
 * Contains the netvar structure for all game related prop data
 */
class C_ClientPropData
{
public:
	void* m_pCreateFn;
	void* m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	C_ClientPropData* m_pNext;
	int m_ClassID;
};

/*
 * C_NetVarScanner
 * Used for scanning netvars in the game.
 */
class C_NetVarScanner
{
	size_t m_iDumpedNetvars = 0;
	size_t m_iDumpedTables = 0;
public:
	std::unordered_map<uint64_t, std::unordered_map<uint64_t, int>> m_NetVars;

	static void hook_prop(uint64_t table_name, uint64_t prop_name, RecvVarProxyFn function);
	void store_props(uint64_t table_hash, RecvTable* table, int child_offset = 0);
	void dump_props();
	void start();
};
