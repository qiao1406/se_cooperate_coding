#pragma once
# include "Station.h"
# include <QGraphicsItem>

typedef struct StationNode {
	string stationName;
	int stationIndex;
	struct StationNode *left;
	struct StationNode *right;

}SNode, *SLinkList;

class Line
{
public:
	
	int lineColor[3];
	string lineName;
	SLinkList head; 
	SLinkList end;
	Line();
	Line(string name, SLinkList head, SLinkList end);
	~Line();
	int calDistance(string s1, string s2);

	// destory the linklist
	void freeStationNodes();

	// set line color
	void setLineColor(int R, int G, int B);
};

