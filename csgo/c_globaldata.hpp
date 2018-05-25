// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017
// *********************************

#pragma once

class C_GlobalData
{
public:
	float realtime;
	int framecount;
	float absoluteframetime;
	float absoluteframestarttimestddev;
	float curtime;
	float frametime;
	int max_clients;
	int tickcount;
	float interval_per_tick;
	float interpolation_amount;
	int simticksthisframe;
	int network_protocol;
	void* psavedata;
private:
	bool client;
public:
	bool remote_client;
private:
	int nTimestampNetworkingBase;
	int nTimestampRandomizeWindow;
};
