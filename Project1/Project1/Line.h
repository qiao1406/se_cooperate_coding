#pragma once
# include "Station.h"

typedef struct StationNode {
	string stationName;
	int stationIndex;
	struct StationNode *left;
	struct StationNode *right;

}SNode, *SLinkList;

class Line
{
public:

	string lineName;
	SLinkList head; 
	SLinkList end;
	Line();
	Line(string name, SLinkList head, SLinkList end);
	~Line();
	int calDistance(string s1, string s2);

	// destory the linklist
	void freeStationNodes();

	//add one station onto the line
	//void addStation(Station station);

};

