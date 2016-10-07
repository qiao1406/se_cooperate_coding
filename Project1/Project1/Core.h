#pragma once
#include "Station.h"
#include "Line.h"
#include <vector>

#define STATION_NUM 300

class Core {
public:

	//use vector to store the information of stations
	static vector<Station> stations;
	//use vector to store the information of lines
	static vector<Line> lines;
	//a 2d int matrix as to store the nearby information of stations
	static int matrix[STATION_NUM][STATION_NUM];
	static vector<int> SPath(int StationId1, int StationId2);
	static vector<int> LTPath(int StationId1, int StationsId2);
	static vector<int> getLTPath(int StationId1, int StationsId2);
	static void addStation(string name, string lineName, int index);
	static void updateLines(string name, SLinkList head, SLinkList end);
	static void initMatrix();
	static void updateMatrix();
	static int findMinDist(int*s, int*dist);
	static int findLineIndex(string name);
	static void freeLineLinkList();
};

