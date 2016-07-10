#include "output.h"

Output::Output() : inReverse(false) {
	this->clear();
}

Output::~Output() {
	this->clear();
}

void Output::print(std::string message){
	this->messageLog.push_back(message);
	if (this->messageLog.size() > 29){
		this->messageLog.erase(this->messageLog.begin());
	}
	this->printAll();
}

void Output::clear() {
	while (!this->messageLog.empty()){
		this->messageLog.erase(this->messageLog.begin());
	}
}

void Output::printAll(){
	//Max rows count = 29.
	consoleClear();
	if (this->inReverse){
		for (size_t i = 0; i < this->messageLog.size(); i++){
			text(i, 0, this->messageLog[this->messageLog.size() - i - 1]);
		}
	}
	else {
		for (size_t i = 0; i < this->messageLog.size(); i++){
			text(i, 0, this->messageLog[i]);
		}
	}
}

void Output::setReverseFlag(const bool value){
	this->inReverse = value;
}

bool Output::getReverseFlag() const {
	return this->inReverse;
}
