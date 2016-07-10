#pragma once

#ifndef COMMON_HEADER
#	define COMMON_HEADER

//C++ standard headers
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

//3DS standard header
#include <3ds.h>
#include <citro3d.h>

static inline std::string text(int row, int column, std::string message, int color = 37) {
	std::stringstream ss;
	ss << "\x1b[" << row << ";" << column << "H";
	ss << "\x1b[" << color << "m";
	ss << message;
	ss << "\x1b[" << 37 << "m";
	std::cout << ss.str() << std::endl;
	return ss.str();
}



#endif
