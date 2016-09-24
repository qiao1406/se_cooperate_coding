#pragma once

#include <string>

using namespace std;

class Station
{
public:
	string name;
	string line[3];
	Station(string name, string lineName);
	Station();
	~Station();
	void addLine(string lineName);
	bool isEmpty();
};

