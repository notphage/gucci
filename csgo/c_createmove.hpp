// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

#include "c_predictionsystem.hpp"
#include "c_antiban.hpp"
#include "c_miscellaneous.hpp"
#include "c_movement.hpp"
#include "c_autowall.hpp"
#include "c_ragebot.hpp"
#include "c_legitbot.hpp"

class C_CreateMove
{
public:
	C_PredictionSystem* prediction;
	C_AntiBan* antiban;
	C_Miscellaneous* misc;
	C_Movement* movement;
	C_RageBot* ragebot;
	C_LegitBot* legitbot;

	void createmove(float sequence, C_UserCmd* cmd, bool& send_packet) const;
};
