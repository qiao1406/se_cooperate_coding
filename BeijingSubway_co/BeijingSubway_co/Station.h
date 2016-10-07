#pragma once

# include <string>
# include <vector>
# include <QGraphicsItem>

using namespace std;

class Station
{
public:
	//the name of the station
	string name;
	//the line of the station
	vector<string> line;
	//the physical position of the station
	double x, y;
	static double ave_x, ave_y;
	//the graphic circle of station
	QGraphicsEllipseItem *station_circle;

	Station(string name, string lineName);
	Station(string name, string lineName, double x, double y);
	Station();
	~Station();
	void addLine(string lineName); 
	bool isInSameLine(Station s);
	bool isInLine(string lineName);
	bool isChangeStation();
	void setPosition(double x, double y);
	void setCircle();
	static void setAvePosition(double x, double y);
	string getSameLineName(Station s);

};

