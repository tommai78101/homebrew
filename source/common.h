#pragma once

#ifndef COMMON_HEADER
#	define COMMON_HEADER

#include <3ds.h>
#include <citro3d.h>
#include <float.h>

#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <limits>
#include <memory>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <vector>

typedef struct {
	float positions[3];
	float texcoords[2];
	float normals[3];
} Vertex;

static const Vertex vertexList[] =
{
	// First face (PZ)
	// First triangle
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { -0.5f, +0.5f, +0.5f },{ 0.0f, 1.0f },{ 0.0f, 0.0f, +1.0f } },
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, +1.0f } },

	// Second face (MZ)
	// First triangle
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { -0.5f, +0.5f, -0.5f },{ 1.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { +0.5f, +0.5f, -0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, -0.5f },{ 1.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { +0.5f, -0.5f, -0.5f },{ 0.0f, 1.0f },{ 0.0f, 0.0f, -1.0f } },
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, 0.0f, -1.0f } },

	// Third face (PX)
	// First triangle
	{ { +0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, +0.5f, -0.5f },{ 1.0f, 0.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ +1.0f, 0.0f, 0.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 0.0f, 1.0f },{ +1.0f, 0.0f, 0.0f } },
	{ { +0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ +1.0f, 0.0f, 0.0f } },

	// Fourth face (MX)
	// First triangle
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, -0.5f, +0.5f },{ 1.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },
	// Second triangle
	{ { -0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, +0.5f, -0.5f },{ 0.0f, 1.0f },{ -1.0f, 0.0f, 0.0f } },
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ -1.0f, 0.0f, 0.0f } },

	// Fifth face (PY)
	// First triangle
	{ { -0.5f, +0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { -0.5f, +0.5f, +0.5f },{ 1.0f, 0.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, +1.0f, 0.0f } },
	// Second triangle
	{ { +0.5f, +0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { +0.5f, +0.5f, -0.5f },{ 0.0f, 1.0f },{ 0.0f, +1.0f, 0.0f } },
	{ { -0.5f, +0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, +1.0f, 0.0f } },

	// Sixth face (MY)
	// First triangle
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { +0.5f, -0.5f, -0.5f },{ 1.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },
	// Second triangle
	{ { +0.5f, -0.5f, +0.5f },{ 1.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { -0.5f, -0.5f, +0.5f },{ 0.0f, 1.0f },{ 0.0f, -1.0f, 0.0f } },
	{ { -0.5f, -0.5f, -0.5f },{ 0.0f, 0.0f },{ 0.0f, -1.0f, 0.0f } },
};

static const C3D_Material material =
{
	{ 0.2f, 0.2f, 0.2f }, //ambient
	{ 0.4f, 0.4f, 0.4f }, //diffuse
	{ 0.8f, 0.8f, 0.8f }, //specular0
	{ 0.0f, 0.0f, 0.0f }, //specular1
	{ 0.0f, 0.0f, 0.0f }, //emission
};

static const int vertexListSize = (sizeof(vertexList) / sizeof(vertexList[0]));
static const float radian = std::acos(-1) / 180.0f;
static const u32 COMMON_CLEAR_COLOR = 0x68B0D8FF;
static const u32 COMMON_DISPLAY_TRANSFER_FLAGS = \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO));

static inline float degToRad(float degrees){
	return degrees * radian;
}

static inline std::string text(int row, int column, std::string message, u16 color = 37) {
	std::stringstream ss;
	ss << "\x1b[" << row << ";" << column << "H";
	ss << "\x1b[" << color << "m";
	ss << message;
	ss << "\x1b[" << 37 << "m";
	std::cout << ss.str() << std::endl;
	return ss.str();
}

static inline C3D_FQuat Quat_MyFromAxisAngle(C3D_FVec axis, float angle){
	float halfAngle = angle / 2.0f;
	float scale = std::sin(halfAngle);
	return FVec4_New(axis.x * scale, axis.y * scale, axis.z * scale, std::cos(halfAngle));
}

static inline C3D_FQuat Quat_MyLookAt(C3D_FVec source, C3D_FVec target){
	C3D_FVec forwardVector = FVec3_New(0.0f, 0.0f, 1.0f);
	C3D_FVec upVector = FVec3_New(0.0f, 1.0f, 0.0f);
	C3D_FVec forward = FVec3_Normalize(FVec3_Subtract(target, source));
	float dot = FVec3_Dot(forwardVector, forward);
	if (fabsf(dot + 1.0f) < FLT_EPSILON){
		return FVec4_New(upVector.x, upVector.y, upVector.z, 3.1415926535897932f);
	}
	if (fabsf(dot - 1.0f) < FLT_EPSILON){
		return Quat_Identity();
	}
	float rotationAngle = std::acos(dot);
	C3D_FVec rotationAxis = FVec3_Normalize(FVec3_Cross(forwardVector, forward));
	return Quat_MyFromAxisAngle(rotationAxis, rotationAngle);
}

static inline C3D_FQuat Quat_MyPitchYawRoll(float pitch, float yaw, float roll, bool bRightSide){
	float pitch_c = cosf(pitch / 2.0f);
	float pitch_s = sinf(pitch / 2.0f);
	float yaw_c = cosf(yaw / 2.0f);
	float yaw_s = sinf(yaw / 2.0f);
	float roll_c = cosf(roll / 2.0f);
	float roll_s = sinf(roll / 2.0f);

	if (bRightSide)
	{
		return Quat_New(
			pitch_s * yaw_c * roll_c - pitch_c * yaw_s * roll_s,
			pitch_c * yaw_s * roll_c + pitch_s * yaw_c * roll_s,
			pitch_c * yaw_c * roll_s - pitch_s * yaw_s * roll_c,
			pitch_c * yaw_c * roll_c + pitch_s * yaw_s * roll_s);
	}
	else
	{
		return Quat_New(
			pitch_s * yaw_c * roll_c + pitch_c * yaw_s * roll_s,
			pitch_c * yaw_s * roll_c - pitch_s * yaw_c * roll_s,
			pitch_c * yaw_c * roll_s + pitch_s * yaw_s * roll_c,
			pitch_c * yaw_c * roll_c - pitch_s * yaw_s * roll_s);
	}
}

static inline C3D_FVec Extract_CamPos(C3D_Mtx* inversedViewMatrix){
	return FVec4_New(inversedViewMatrix->r[0].w, inversedViewMatrix->r[1].w, inversedViewMatrix->r[2].w, 1.0f);
}

static inline C3D_FVec Extract_CamRight(C3D_Mtx* inversedViewMatrix){
	return FVec4_New(inversedViewMatrix->r[0].x, inversedViewMatrix->r[1].x, inversedViewMatrix->r[2].x, 0.0f);
}

static inline C3D_FVec Extract_CamUp(C3D_Mtx* inversedViewMatrix){
	return FVec4_New(inversedViewMatrix->r[0].y, inversedViewMatrix->r[1].y, inversedViewMatrix->r[2].y, 0.0f);
}

static inline C3D_FVec Extract_CamForward(C3D_Mtx* inversedViewMatrix){
	return FVec4_New(inversedViewMatrix->r[0].z, inversedViewMatrix->r[1].z, -inversedViewMatrix->r[2].z, 0.0f);
}

template <typename Type> std::string ToString(const Type& t){
	std::ostringstream os;
	os << t;
	return os.str();
}

static const u16 BOTTOM_SCREEN_WIDTH = 320;
static const u16 BOTTOM_SCREEN_HEIGHT = 240;
static const u16 TOP_SCREEN_WIDTH = 400;
static const u16 TOP_SCREEN_HEIGHT = 240;



#endif
