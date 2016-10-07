#include <iostream>
#include <Windows.h>
#include "Core.h"
#include "IOLib.h"
#include "Station.h"
#include "Line.h"
#include "beijingsubway_co.h"
#include <QtWidgets/QApplication>
#include <QTextStream>

#define STATION_NUM 300
using namespace std;

int main(int argc, char *argv[])
{
	freopen("output.txt","w",stdout);

	//read in station information
	IOLib::readData("beijing-subway.txt");
	//read in position information
	IOLib::readPositionData("beijing-subway.prn");
	IOLib::readColorData("beijing-subway-color.prn");
	for (int i = 0; i < Core::stations.size(); i++) {
		Core::stations[i].setCircle();
	}
	//Core::freeLineLinkList();

	QApplication a(argc, argv);
	BeijingSubway_co w;
	w.show();
	return a.exec();
}