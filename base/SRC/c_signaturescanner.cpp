// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#include "framework.hpp"
#include "c_signaturescanner.hpp"

DWORD C_SignatureScanner::find_signature(DWORD dwAddress, DWORD dwLength, const char* szPattern, int iOffset)
{
	if (!dwAddress || !dwLength || !szPattern)
		return 0;

	auto pPattern = szPattern;
	DWORD dwMatchData = 0;
	DWORD dwReturn = 0;

	for (auto pDataPatch = dwAddress; pDataPatch < dwLength; pDataPatch++)
	{
		if (!*pPattern)
			dwReturn = dwMatchData;

		if (*PBYTE(pPattern) == '\?' || *reinterpret_cast<BYTE*>(pDataPatch) == ((pPattern[0] >= '0' && pPattern[0] <= '9' ? pPattern[0] - '0' : (pPattern[0] & ~32) - 'A' + 10) << 4 | (pPattern[1] >= '0' && pPattern[1] <= '9' ? pPattern[1] - '0' : (pPattern[1] & ~32) - 'A' + 10)))
		{
			if (!dwMatchData)
				dwMatchData = pDataPatch;

			if (!pPattern[2])
				dwReturn = dwMatchData;

			pPattern += *PWORD(pPattern) == 16191 || *PBYTE(pPattern) != '\?' ? 3 : 2;
		}
		else
		{
			pPattern = szPattern;
			dwMatchData = 0;
		}
	}

	return dwReturn + iOffset;
}

DWORD C_SignatureScanner::find_signature(const char* szModuleName, char* szPattern, int iOffset)
{
	auto pBase = reinterpret_cast<DWORD>(GetModuleHandleA(szModuleName));
	auto pDataHeader = reinterpret_cast<PIMAGE_NT_HEADERS>(pBase + reinterpret_cast<PIMAGE_DOS_HEADER>(pBase)->e_lfanew)->OptionalHeader;

	return find_signature(pBase + pDataHeader.BaseOfCode, pBase + pDataHeader.SizeOfCode, szPattern, iOffset);
}
