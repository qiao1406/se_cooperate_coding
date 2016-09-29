#include "Station.h"



Station::Station() {
	name = "";
}

Station::Station (string name, string lineName) {
	this->name = name;
	line.push_back(lineName);
	this->x = 0;
	this->y = 0;
}

Station::Station(string name, string lineName, double x, double y)
{
	this->name = name;
	line.push_back(lineName);
	this->x = x;
	this->y = y;
}

Station::~Station()
{
}

void Station::addLine(string lineName) {
	
	for ( unsigned int i = 0; i < line.size(); ++i) {
		if (line[i] == lineName) {
			return;
		}

	}

	line.push_back(lineName);
}

// Requires: s must be in stations
// Effects: to judge whether two stations are in the same line
bool Station::isInSameLine(Station s) {

	if (this->name == s.name) {
		return true;
	}
	else {

		unsigned int i = 0;
		unsigned int j = 0;
		bool temp = false;

		while ( i < this->line.size() ) {

			while (j < s.line.size() ) {

				if (this->line[i] == s.line[j]) {
					temp = true;
					break;
				}
				j++;
			}

			if (temp == true) {
				break;
			}
			i++;
			j = 0;
		}

		return temp;
	}
	return false;
}

// 判断这个站是否在某条线上
bool Station::isInLine(string lineName) {
	bool rst = false;

	for (unsigned int i = 0; i < line.size(); ++i) {

		if ( line[i] == lineName) {
			rst = true;
		}

	}

	return rst;
}

bool Station::isChangeStation() {
	return (line.size() > 1) ? true : false;
}

void Station::setPosition(double x, double y) {

}

//找出两个站点同处的那条线路
string Station::getSameLineName(Station s){

	string sameline = "";
	unsigned int i = 0;
	unsigned int j = 0;

	while ( i < this->line.size() ) {

		while ( j < s.line.size() ) {

			if (this->line[i] == s.line[j]) {
				sameline = this->line[i];
				break;
			}
			j++;
		}

		if (sameline != "") {
			break;
		}
		i++;
		j = 0;
	}

	return sameline;
}

