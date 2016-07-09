#include "common.h"

std::string text(int row, int column, std::string message, int color) {
	std::stringstream ss;
	ss << "\x1b[" << row << ";" << column << "H";
	ss << "\x1b[" << color << "m";
	ss << message;
	ss << "\x1b[" << 37 << "m";
	std::cout << ss.str() << std::endl;
	return ss.str();
}
