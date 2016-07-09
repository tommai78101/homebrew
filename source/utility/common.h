#pragma once

#ifndef COMMON_HEADER
#	define COMMON_HEADER

//C++ standard headers
#include <cstring>
#include <iostream>
#include <sstream>

//3DS standard header
#include <3ds.h>
#include <citro3d.h>

std::string text(int row, int column, std::string message, int color = 37);

#endif
