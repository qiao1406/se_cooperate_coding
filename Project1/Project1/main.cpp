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
	/*for (unsigned int i = 0; i < Core::stations.size(); ++i) {
		cout << Core::stations[i].name << endl;
	}*/
	//IOLib::CommandOutput(Core::SPath(183,56));
	IOLib::CommandOutput(Core::LTPath(104, 237));
	//IOLib::CommandOutput(Core::LTPath(237, 189));
	Core::freeLineLinkList();
	system("pause");
	return 0;
}