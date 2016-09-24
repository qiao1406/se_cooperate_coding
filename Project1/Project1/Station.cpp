#include "Station.h"



Station::Station() {
	name = "";
}

Station::Station (string name, string lineName) {
	this->name = name;
	line[0] = lineName;
}

Station::~Station()
{
}

void Station::addLine(string lineName) {
	int i = 0;

	for (; i < 3; ++i) {
		if (line[i] == lineName) {
			return;
		}
		if (line[i] == "")
			break;
	}

	if (i < 3) {
		line[i] = lineName;
	}
}

bool Station::isEmpty() {
	return name == "";
}
