# include "Line.h"
# include "Station.h"

using namespace std;

Line::Line()
{
} 

Line::Line(string name, SLinkList head, SLinkList end)
{
	lineName = name;
	this->head = head;
	this->end = end;
}


Line::~Line()
{
}

//Requires: s1 and s2 are name of elements in vector stations
int Line::calDistance(string s1, string s2) {
	SLinkList p = this->head;

	//环线的情况
	if ( head == end ) {
		int case1 = 0;//模仿非环行线
		int case2 = 0;//左右开弓
		int d1 = 0;
		int d2 = 0;

		// case1
		int temp = 0;//temp记录的是当前指针所指位置与起点站的距离
		while (p->stationName != s1 && p->stationName != s2 && p != NULL) {
			p = p->right;
			temp++;
		}
		if (p->stationName == s1) {
			d1 = temp;

			do {
				temp++;
				p = p->right;
			} while (p->stationName != s2 && p != head->left);
			d2 = temp;
		}
		else {
			d2 = temp;
			do {
				temp++;
				p = p->right;
			} while (p->stationName != s1 && p != head->left);
			d1 = temp;
		}
		case1 = (d1 - d2 > 0) ? (d1 - d2) : (d2 - d1);

		// case2
		d1 = 0;
		d2 = 0;
		p = head;
		while (p->stationName != s1 && p->stationName != s2) {
			p = p->right;
			d1++;
		}


		if (p->stationName == s1) {
			p = head;
			while (p->stationName != s2) {
				p = p->left;
				d2++;
			}
		}
		else {
			p = head;
			while (p->stationName != s1) {
				p = p->left;
				d2++;
			}
		}
		case2 = d1 + d2;

		return case1 < case2 ? case1 : case2;

	}
	else {//不是环线的情况
		int d1 = 0;
		int d2 = 0;
		int temp = 0;//temp记录的是当前指针所指位置与起点站的距离

		while (p->stationName != s1 && p->stationName != s2 && p != NULL) {
			p = p->right;
			temp++;
		}
		if (p->stationName == s1) {
			d1 = temp;
			while (p->stationName != s2 && p != NULL) {
				temp++;
				p = p->right;
			}
			d2 = temp;
		}
		else {
			d2 = temp;
			while (p->stationName != s1 && p != NULL) {
				temp++;
				p = p->right;
			}
			d1 = temp;
		}

		return (d1 - d2 > 0) ? (d1 - d2) : (d2 - d1);
	}
}

void Line::freeStationNodes() {
	SLinkList e = (head == end) ? head->left : end;
	SLinkList p = head;

	do {
		p = head;
		head = head->right;
		delete p;
	} while ( head != NULL );
}

//Require:
//	a not null Station object
//Modified:
//	Line.stations
//Effect:
//	add a station object to the Line.station
//	which means the station is on the Line
//Exception:
//
//void Line::addStation(Station station) {

//}
