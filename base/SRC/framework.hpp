// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define CONCAT_IMPL(x, y) x##y
#define MACRO_CONCAT(x, y) CONCAT_IMPL(x, y)
#define PAD(size) byte MACRO_CONCAT(_pad, __COUNTER__)[size];

#include <windows.h>
#include <stdlib.h>
#include <process.h>
#include <assert.h>
#include <winuser.h>
#include <Wincon.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <array>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include <unordered_map>
#include <vector>
#include <deque>
#include <random>
#include <chrono>
#include <functional>
#include <future>
#include <Shlobj.h>

#undef min
#undef max

// framework includes
#include "matrix.hpp"
#include "vector.hpp"
#include "angle.hpp"
#include "colour.hpp"
#include "c_address.h"

#pragma warning(push)
#pragma warning(disable : 4244 4146)
#include "c_crypto.hpp"
#pragma warning(pop)

#include "c_module.h"
#include "c_console.hpp"
#include "c_signaturescanner.hpp"
