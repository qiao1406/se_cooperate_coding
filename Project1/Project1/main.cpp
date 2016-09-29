#include <iostream>
#include <Windows.h>
#include "Core.h"
#include "IO.cpp"
#include "Station.h"
#include "Line.h"


#define STATION_NUM 300

using namespace std;

int main() {
	IO::readData("beijing-subway.txt");
	/*for (unsigned int i = 0; i < Core::stations.size(); ++i) {
		cout << Core::stations[i].name << endl;
	}*/
	//IO::CommandOutput(Core::SPath(183,56));
	//IO::CommandOutput(Core::SPath(237, 104));
	IO::CommandOutput(Core::LTPath(237, 127));
	system("pause");

}