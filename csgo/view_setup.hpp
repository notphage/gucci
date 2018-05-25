// *********************************
// *             GUCCI             *
// *           Framework           *
// *********************************
// Project By: Senator & Phage
// Project Started: 18/02/2017D
// *********************************

#pragma once

class C_ViewSetup
{
public:
	int x;
	int x_old;
	int y;
	int y_old;
	int width;
	int width_old;
	int height;
	int height_old;
	bool m_bOrtho;
	float m_OrthoLeft;
	float m_OrthoTop;
	float m_OrthoRight;
	float m_OrthoBottom;
	bool m_bCustomViewMatrix;
	Matrix3x4 m_matCustomViewMatrix;
	PAD(0x48)
	float fov;
	float fovViewmodel;
	Vector3 origin;
	Angle angles;
	float zNear;
	float zFar;
	float zNearViewmodel;
	float zFarViewmodel;
	float m_flAspectRatio;
	float m_flNearBlurDepth;
	float m_flNearFocusDepth;
	float m_flFarFocusDepth;
	float m_flFarBlurDepth;
	float m_flNearBlurRadius;
	float m_flFarBlurRadius;
	int m_nDoFQuality;
	int m_nMotionBlurMode;
	float m_flShutterTime;
	Vector3 m_vShutterOpenPosition;
	Angle m_shutterOpenAngles;
	Vector3 m_vShutterClosePosition;
	Angle m_shutterCloseAngles;
	float m_flOffCenterTop;
	float m_flOffCenterBottom;
	float m_flOffCenterLeft;
	float m_flOffCenterRight;
	int m_EdgeBlur;
};
