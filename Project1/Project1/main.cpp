#include <iostream>
#include <Windows.h>
#include "Core.h"
#include "IOLib.h"
#include "Station.h"
#include "Line.h"

#define STATION_NUM 300

using namespace std;

int main() {
	IOLib::readData("beijing-subway.txt");
	//IOLib::CommandOutput(Core::LTPath(183,56));
	//IOLib::CommandOutput(Core::LTPath(151,56));
	//IOLib::CommandOutput(Core::LTPath(237,104));
	IOLib::CommandOutput(Core::LTPath(104,237));
	Core::freeLineLinkList();
	system("pause");
	return 0;
}