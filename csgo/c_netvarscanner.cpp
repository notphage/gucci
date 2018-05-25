// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "includes.hpp"

void C_NetVarScanner::hook_prop(uint64_t table_hash, uint64_t prop_hash, RecvVarProxyFn function)
{
	auto client_data = G::interfaces.client->get_all_classes();

	std::function<void(RecvTable*, uint64_t, RecvVarProxyFn)> recursive_table_scan = [&](RecvTable* table, uint64_t _prop_hash, RecvVarProxyFn func) -> void
			{
				for (auto i = 0; i < table->m_nProps; ++i)
				{
					auto current_prop = &table->m_pProps[i];
					auto current_child = current_prop->m_pDataTable;

					if (current_child != nullptr && current_child->m_nProps > 0)
						recursive_table_scan(current_child, _prop_hash, func);

					if (Crypto::CRC::crc(current_prop->m_pVarName) == _prop_hash)
					{
						current_prop->m_ProxyFn = func;
						break;
					}
				}
			};

	for (auto data = client_data; data != nullptr; data = data->m_pNext)
	{
		if (Crypto::CRC::crc(data->m_pRecvTable->m_pNetTableName) != table_hash)
			continue;

		for (auto i = 0; i < data->m_pRecvTable->m_nProps; ++i)
		{
			recursive_table_scan(data->m_pRecvTable, prop_hash, function);
		}
	}
}

/*
 * store_props
 * Stores props in m_recvVars
 */
void C_NetVarScanner::store_props(uint64_t table_hash, RecvTable* table, int child_offset)
{
	for (auto i = 0; i < table->m_nProps; ++i)
	{
		auto current_prop = &table->m_pProps[i];
		auto current_child = current_prop->m_pDataTable;

		if (current_child != nullptr && current_child->m_nProps > 0)
			store_props(table_hash, current_child, current_prop->m_Offset);

		if (G::netvars.m_NetVars[table_hash][Crypto::CRC::crc(current_prop->m_pVarName)] <= 0)
		{
			G::netvars.m_NetVars[table_hash][Crypto::CRC::crc(current_prop->m_pVarName)] = current_prop->m_Offset + child_offset;
			m_iDumpedNetvars++;
		}
	}
}

/*
 * dump_props
 * Dumps all prop data
 */
void C_NetVarScanner::dump_props()
{
	auto pClientData = G::interfaces.client->get_all_classes();

	for (auto pData = pClientData; pData != nullptr; pData = pData->m_pNext)
	{
		store_props(Crypto::CRC::crc(pData->m_pRecvTable->m_pNetTableName), pData->m_pRecvTable);
		m_iDumpedTables++;
	}
}

/*
 * start
 * Starts netvar scanning
 */
void C_NetVarScanner::start()
{
	G::console.print("\n-> Dump Networked Variables\n\n");

	dump_props();

	G::console.print("Dumped %i Netvars in %i Tables.\n", m_iDumpedNetvars, m_iDumpedTables);
}
