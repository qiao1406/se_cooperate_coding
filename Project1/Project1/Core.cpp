#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

#include "Core.h"
#include "Line.h"


#define STATION_NUM 300
#define LINE_NUM 30

using namespace std;

vector<Line> Core::lines;
vector<Station> Core::stations;
int Core::matrix[STATION_NUM][STATION_NUM];

//Require:
//	id of two station, should be in the range of 0~stations.size()-1
//Modified:
//	no modified
//Effect:
//	find the shortest path between two station.
//	return a list of station id containing the path
//	the return is in form of vector<int>
//Exception:
//
vector<int> Core::SPath(int StationId1, int StationId2) {

	int pos[STATION_NUM];
	int dist[STATION_NUM];
	int path[STATION_NUM][STATION_NUM];
	int s[STATION_NUM];
	vector<int> route;

	for ( unsigned int i = 0; i < stations.size(); ++i) {
		s[i] = 0;
		dist[i] = matrix[StationId1][i];
		path[i][0] = StationId1;
		pos[i] = 0;
	}

	s[StationId1] = 1;

	while (s[StationId2] == 0) {
		int u = findMinDist(s, dist);
		s[u] = 1;
		path[u][++pos[u]] = u;

		// 找到通过u可以到达的、尚未确定最短路径的点
		for ( unsigned int i = 0; i < stations.size(); ++i) {

			if (s[i] != 0) {
				continue;
			}
			else {

				// 更新路径长度
				if (matrix[u][i] == 1 && dist[u] + matrix[u][i] < dist[i]) {
					dist[i] = dist[u] + matrix[u][i];
					for (int j = 0; j <= pos[u]; ++j) {
						path[i][j] = path[u][j];
					}
					pos[i] = pos[u];
				}

			}
		}

	}

	// 此时，start到end的路径已经找出了，将路径存起来
	for (int i = 0; i <= pos[StationId2]; ++i) {
		route.push_back(path[StationId2][i]);
	}

	return route;
}

//Require:
//	id of two station, should be in the range of 0~stations.size()-1
//Modified:
//	no modified
//Effect:
//	find the least transfer path between two station.
//	return a list of station id containing the path
//	the return is in form of vector<int>
//Exception:
//
vector<int> Core::LTPath(int StationId1, int StationId2) {
	int dist[STATION_NUM];
	int path[STATION_NUM][LINE_NUM]; // 记录换乘的站点
	int pos[STATION_NUM]; // 记录该站点在path[] 数组中的位置
	int final_change_time = INT_MAX;//最终的换乘次数
	int change_time[STATION_NUM]; // 换乘次数,当该站点已经找到了终点站所在的时候才会进行设定
	int min_dist = INT_MAX;
	int min_index = -1;
	bool st_flag[STATION_NUM];
	bool line_flag[LINE_NUM];
	bool find = false;
	queue<int> q1;//存放要查找的换乘站
	queue<int> q2;//存放对应的换乘次数
	vector<int> route;//存放要返回的路径

	// 初始化line_flag[]
	for ( unsigned int i = 0; i < lines.size(); ++i) {
		line_flag[i] = false;
	}
	for ( unsigned int i = 0; i < stations.size(); ++i) {
		dist[i] = INT_MAX;
		change_time[i] = INT_MAX;
		path[i][0] = StationId1;
		pos[i] = 0;
		st_flag[i] = false;
	}

	st_flag[StationId1] = true;

	// 同一条线
	if (stations[StationId1].isInSameLine(stations[StationId2])) {
		find = true;
		path[StationId2][++pos[StationId2]] = StationId2;
		change_time[StationId2] = 0;
	}
	else {

		//对起始站的所在线路的所有换乘站进行查找
		for ( unsigned int i = 0; i < stations[StationId1].line.size(); i++) {

			//拿出一条线来
			string lineName = stations[StationId1].line[i];
			int lineIndex = Core::findLineIndex(lineName);
			//判断是否环线，若是环线则要改变其遍历结束的点
			SLinkList e = (lines[lineIndex].end == lines[lineIndex].head) ?
							lines[lineIndex].head->left : lines[lineIndex].end; 

			//把这条线上所有的换乘点加进去
			SLinkList p = lines[lineIndex].head;
			do {
				int j = p->stationIndex;
				if (st_flag[j] == false &&
					stations[j].isChangeStation()) {
					st_flag[j] = true;
					q1.push(j);
					q2.push(1);
					path[j][++pos[j]] = j;
				}
				p = p->right;
			} while (p != e);
			line_flag[lineIndex] = true;

		}

		//对q1里面的换乘站进行查找,直到找到为止
		while (!q1.empty()) {

			int temp_index = q1.front();
			q1.pop();
			int now_time = q2.front();
			q2.pop();

			//若此时的换乘站和终点站共线，则停止寻找
			if (stations[temp_index].isInSameLine(stations[StationId2])) {
				find = true;
				//final_change_time = now_time;
				//path[temp_index][++pos[temp_index]] = temp_index;
				path[temp_index][++pos[temp_index]] = StationId2;
				change_time[temp_index] = now_time;
			}
			else {

				//将这个换乘站所在线路中未被搜寻的线路进行查找
				for ( unsigned int i = 0; i < stations[temp_index].line.size(); ++i) {
					string lineName = stations[temp_index].line[i];
					int lineIndex = Core::findLineIndex(lineName);

					if (line_flag[lineIndex] == false) {

						line_flag[lineIndex] = true;

						for ( unsigned int j = 0; j < stations.size(); ++j) {

							if ( st_flag[j] == false
								&& stations[j].isInLine(lineName)
								&& stations[j].isChangeStation() ) {

								st_flag[j] = true;
								q1.push(j);
								q2.push(now_time + 1);
								// 将该站的path[]的值与temp_index的保持一致
								for (int k = 1; k <= pos[temp_index]; ++k) {
									path[j][k] = path[temp_index][k];
								}
								pos[j] = pos[temp_index];
								path[j][++pos[j]] = j;
							}
						}
					}


				}

			}

		}

	}

	//找出换乘次数最小的方案
	for ( unsigned int i = 0; i < stations.size(); ++i) {
		if (change_time[i] < final_change_time) {
			final_change_time = change_time[i];
		}
	}

	//找出所有已经找到的路径，求出距离的最小值(换乘次数最小的方案中距离最小的)
	for ( unsigned int i = 0; i < stations.size(); ++i) {

		if (path[i][pos[i]] == StationId2 && change_time[i] == final_change_time) { // 已经找到路径的，计算dist
			dist[i] = 0;
			for (int j = 0; j < pos[i]; ++j) {
				string s = stations[path[i][j]].getSameLineName(stations[path[i][j + 1]]);//线路的名字
				string s1 = stations[path[i][j]].name;
				string s2 = stations[path[i][j + 1]].name;
				int d = lines[Core::findLineIndex(s)].calDistance(s1, s2); //计算距离
				dist[i] += d;
			}

			if (min_dist > dist[i]) {
				min_dist = dist[i];
				min_index = i;
			}

		}
	}

	if ( min_index == -1 ) {
		cout << "找不到最短换乘路径" << endl;
		return route;
	}
	//找到最适合的路径了，把路径存到队列里面
	//先把起点加进去
	route.push_back(path[min_index][0]);
	for (int i = 0; i < pos[min_index]; ++i) {

		string s = stations[path[min_index][i]].getSameLineName(stations[path[min_index][i + 1]]);
		string s1 = stations[path[min_index][i]].name;
		string s2 = stations[path[min_index][i + 1]].name;

		int line_index = Core::findLineIndex(s);

		//环线
		//先找到s1,记录其位置，然后分别向左走或者向右走，哪个先到达s2就说明应该从那个方向走
		if ( lines[line_index].head == lines[line_index].end ) {
			SLinkList p, pl, pr, target;
			p = lines[line_index].head;
			pl = NULL;
			pr = NULL;

			while (p->stationName != s1) {
				p = p->right;
			}
			pl = p;
			pr = p;
			while (pl->stationName != s2 && pr->stationName != s2) {
				pl = pl->left;
				pr = pr->right;
			}

			target = (pl->stationName == s2) ? pl : pr;
			do {
				p = (pl->stationName == s2) ? p->left : p->right;
				route.push_back(p->stationIndex);
			} while (p != target);

		}
		else {//非环线
			SLinkList p, p1, p2;
			p1 = NULL;
			p2 = NULL;

			p = lines[line_index].head;
			do {
				p2 = (p->stationName == s2) ? p : p2;
				p1 = (p->stationName == s1) ? p : p1;
				if (p1 != NULL) {
					break;
				}
				p = p->right;
			} while (p != NULL);

			if (p2 == NULL) { // 读到点p1的时候还没有到p2,应该从p1往右读

				do {
					p = p->right;
					route.push_back(p->stationIndex);
					p2 = (p->stationName == s2) ? p : p2;
				} while (p2 == NULL);
			}
			else { // 读到点p1的时候已经读到p2,应该从p1往左读
				do {
					p = p->left;
					route.push_back(p->stationIndex);
				} while (p != p2);
			}

		}
	}

	return route;
}

//Require:
//	input the station name and the name of line and the index of this station
//	the station is on the line
//Modified:
//	Stations,Lines
//Effects:
//	add one station
//	if the station already exist, station.line update the new line information
//	else create a new station and initial its information including station id
//	if the line not exist, create a new line
//	add the station onto the line
//Exception:
//
void Core::addStation(string name, string lineName, int i ) {

	unsigned int index = (unsigned int)i;

	if (stations.size() > index + 1) { // 这个车站已经在stations里面了，更新其线路信息
		stations[index].addLine(lineName);
	}
	else {
		Station s = Station(name, lineName);
		stations.push_back(s);
	}

}

void Core::updateLines(string name, SLinkList head, SLinkList end) {
	Line l = Line(name, head, end);
	lines.push_back(l);
}

//Require:
//	no
//Modified:
//	Matrix
//Effects:
//	initial the matrix at first
//Exception:
//
void Core::initMatrix() {

	for (int i = 0; i < STATION_NUM; ++i) {
		for (int j = 0; j < STATION_NUM; ++j) {
			matrix[i][j] = INT_MAX;
		}
	}
}


//Require:
//	no
//Modified:
//	Matrix
//Effects:
//	update the Matrix according to lines and stations
//Exception:
//
void Core::updateMatrix() {

	for ( unsigned int i = 0; i < lines.size(); ++i) {

		Line l = lines[i];
		SLinkList p = l.head;

		do {
			p = p->right;
			matrix[p->stationIndex][p->left->stationIndex] = 1;
			matrix[p->left->stationIndex][p->stationIndex] = 1;
		} while (p != l.end);

	}

}

//Require:
//	no
//Modified:
//	no
//Effects:
//	return the min value of the array dist[i] & s[i] == 0
//  if it cannot find this value, return -1
//Exception:
//
int Core::findMinDist(int*s, int*dist) {
	int min = INT_MAX;
	int u = -1;

	for ( unsigned int i = 0; i < stations.size(); ++i) {
		if (s[i] != 0) {
			continue;
		}
		else {
			if (min >= dist[i]) {
				min = dist[i];
				u = i;
			}
		}
	}

	return u;
}

// Requires: name must be in lines
// Effects: find the index of the line that line.name = name
int Core::findLineIndex(string name) {
	int r = -1;

	for ( unsigned int i = 0; i < lines.size(); ++i) {
		if ( lines[i].lineName == name) {
			r = i;
			break;
		}
	}

	return r;
}
