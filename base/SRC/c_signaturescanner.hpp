// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_SignatureScanner
{
public:
	static DWORD find_signature(DWORD dwAddress, DWORD dwLength, const char* szPattern, int iOffset = 0);
	static DWORD find_signature(const char* szModuleName, char* szPattern, int iOffset = 0);
};
