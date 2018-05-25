// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

class C_MoveData
{
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	bool m_bNoAirControl : 1;
	void* m_nPlayerHandle;
	int m_nImpulseCommand;
	Angle m_vecViewAngles;
	Angle m_vecAbsViewAngles;
	int m_nButtons;
	int m_nOldButtons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;
	float m_flMaxSpeed;
	float m_flClientMaxSpeed;
	Vector3 m_vecVelocity;
	Vector3 m_vecOldVelocity;
	float m_unknown;
	Angle m_vecAngles;
	Angle m_vecOldAngles;
	float m_outStepHeight;
	Vector3 m_outWishVel;
	Vector3 m_outJumpVel;
	Vector3 m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	bool m_bConstraintPastRadius;

	void C_MoveData::SetAbsOrigin(const Vector3& vec)
	{
		m_vecAbsOrigin = vec;
	}

	const Vector3& GetAbsOrigin() const
	{
		return m_vecAbsOrigin;
	}

private:
	Vector3 m_vecAbsOrigin;
};

class C_PredictionSystem
{
public:
	static void setup(player_prediction_data& data);
	static void predict_engine(player_prediction_data& data, C_UserCmd* cmd);
	static void finish(player_prediction_data& data);
};
