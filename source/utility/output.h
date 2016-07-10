#pragma once

#ifndef OUTPUT_HEADER
#	define OUTPUT_HEADER

#include "common.h"

static const int OUTPUT_MAX_ROW = 29;

static inline std::string text(int row, int column, std::string message, u8 color = 37) {
	std::stringstream ss;
	ss << "\x1b[" << row << ";" << column << "H";
	ss << "\x1b[" << color << "m";
	ss << message;
	ss << "\x1b[" << 37 << "m";
	std::cout << ss.str() << std::endl;
	return ss.str();
}

typedef struct {
	std::string text;
	u8 color;
} Message;

class Output {
private:
	std::vector<Message> messageLog;
	bool inReverse;
	
public:
	Output();
	~Output();
	void Print(std::string message);
	void Error(std::string message);
	void Clear();
	void PrintAll();
	void SetReverseFlag(const bool value);
	bool GetReverseFlag() const;
};

#endif
