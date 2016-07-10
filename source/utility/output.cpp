#include "output.h"

Output::Output() : inReverse(false) {
	this->Clear();
}

Output::~Output() {
	this->Clear();
}

void Output::Print(std::string message){
	Message m = {message, 37};
	this->messageLog.push_back(m);
	if (this->messageLog.size() > 29){
		this->messageLog.erase(this->messageLog.begin());
	}
	this->PrintAll();
}

void Output::Error(std::string message){
	Message m = {message, 31};
	this->messageLog.push_back(m);
	if (this->messageLog.size() > OUTPUT_MAX_ROW){
		this->messageLog.erase(this->messageLog.begin());
	}
	this->PrintAll();
}

void Output::Clear() {
	while (!this->messageLog.empty()){
		this->messageLog.erase(this->messageLog.begin());
	}
}

void Output::PrintAll(){
	//Max rows count = 29.
	consoleClear();
	if (this->inReverse){
		for (size_t i = 0; i < this->messageLog.size(); i++){
			text(i, 0, this->messageLog[this->messageLog.size() - i - 1].text, this->messageLog[this->messageLog.size() - i - 1].color);
		}
	}
	else {
		for (size_t i = 0; i < this->messageLog.size(); i++){
			text(i, 0, this->messageLog[i].text, this->messageLog[i].color);
		}
	}
}

void Output::SetReverseFlag(const bool value){
	this->inReverse = value;
}

bool Output::GetReverseFlag() const {
	return this->inReverse;
}
