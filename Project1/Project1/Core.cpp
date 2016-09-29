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

		// �ҵ�ͨ��u���Ե���ġ���δȷ�����·���ĵ�
		for ( unsigned int i = 0; i < stations.size(); ++i) {

			if (s[i] != 0) {
				continue;
			}
			else {

				// ����·������
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

	// ��ʱ��start��end��·���Ѿ��ҳ��ˣ���·��������
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
	int path[STATION_NUM][LINE_NUM]; // ��¼���˵�վ��
	int pos[STATION_NUM]; // ��¼��վ����path[] �����е�λ��
	int final_change_time = INT_MAX;//���յĻ��˴���
	int change_time[STATION_NUM]; // ���˴���,����վ���Ѿ��ҵ����յ�վ���ڵ�ʱ��Ż�����趨
	int min_dist = INT_MAX;
	int min_index = -1;
	bool st_flag[STATION_NUM];
	bool line_flag[LINE_NUM];
	bool find = false;
	queue<int> q1;//���Ҫ���ҵĻ���վ
	queue<int> q2;//��Ŷ�Ӧ�Ļ��˴���
	vector<int> route;//���Ҫ���ص�·��

	// ��ʼ��line_flag[]
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

	// ͬһ����
	if (stations[StationId1].isInSameLine(stations[StationId2])) {
		find = true;
		path[StationId2][++pos[StationId2]] = StationId2;
		change_time[StationId2] = 0;
	}
	else {

		//����ʼվ��������·�����л���վ���в���
		for ( unsigned int i = 0; i < stations[StationId1].line.size(); i++) {

			//�ó�һ������
			string lineName = stations[StationId1].line[i];
			int lineIndex = Core::findLineIndex(lineName);
			//�ж��Ƿ��ߣ����ǻ�����Ҫ�ı�����������ĵ�
			SLinkList e = (lines[lineIndex].end == lines[lineIndex].head) ?
							lines[lineIndex].head->left : lines[lineIndex].end; 

			//�������������еĻ��˵�ӽ�ȥ
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

		//��q1����Ļ���վ���в���,ֱ���ҵ�Ϊֹ
		while (!q1.empty()) {

			int temp_index = q1.front();
			q1.pop();
			int now_time = q2.front();
			q2.pop();

			//����ʱ�Ļ���վ���յ�վ���ߣ���ֹͣѰ��
			if (stations[temp_index].isInSameLine(stations[StationId2])) {
				find = true;
				//final_change_time = now_time;
				//path[temp_index][++pos[temp_index]] = temp_index;
				path[temp_index][++pos[temp_index]] = StationId2;
				change_time[temp_index] = now_time;
			}
			else {

				//���������վ������·��δ����Ѱ����·���в���
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
								// ����վ��path[]��ֵ��temp_index�ı���һ��
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

	//�ҳ����˴�����С�ķ���
	for ( unsigned int i = 0; i < stations.size(); ++i) {
		if (change_time[i] < final_change_time) {
			final_change_time = change_time[i];
		}
	}

	//�ҳ������Ѿ��ҵ���·��������������Сֵ(���˴�����С�ķ����о�����С��)
	for ( unsigned int i = 0; i < stations.size(); ++i) {

		if (path[i][pos[i]] == StationId2 && change_time[i] == final_change_time) { // �Ѿ��ҵ�·���ģ�����dist
			dist[i] = 0;
			for (int j = 0; j < pos[i]; ++j) {
				string s = stations[path[i][j]].getSameLineName(stations[path[i][j + 1]]);//��·������
				string s1 = stations[path[i][j]].name;
				string s2 = stations[path[i][j + 1]].name;
				int d = lines[Core::findLineIndex(s)].calDistance(s1, s2); //�������
				dist[i] += d;
			}

			if (min_dist > dist[i]) {
				min_dist = dist[i];
				min_index = i;
			}

		}
	}

	if ( min_index == -1 ) {
		cout << "�Ҳ�����̻���·��" << endl;
		return route;
	}
	//�ҵ����ʺϵ�·���ˣ���·���浽��������
	//�Ȱ����ӽ�ȥ
	route.push_back(path[min_index][0]);
	for (int i = 0; i < pos[min_index]; ++i) {

		string s = stations[path[min_index][i]].getSameLineName(stations[path[min_index][i + 1]]);
		string s1 = stations[path[min_index][i]].name;
		string s2 = stations[path[min_index][i + 1]].name;

		int line_index = Core::findLineIndex(s);

		//����
		//���ҵ�s1,��¼��λ�ã�Ȼ��ֱ������߻��������ߣ��ĸ��ȵ���s2��˵��Ӧ�ô��Ǹ�������
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
		else {//�ǻ���
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

			if (p2 == NULL) { // ������p1��ʱ��û�е�p2,Ӧ�ô�p1���Ҷ�

				do {
					p = p->right;
					route.push_back(p->stationIndex);
					p2 = (p->stationName == s2) ? p : p2;
				} while (p2 == NULL);
			}
			else { // ������p1��ʱ���Ѿ�����p2,Ӧ�ô�p1�����
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

	if (stations.size() > index + 1) { // �����վ�Ѿ���stations�����ˣ���������·��Ϣ
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
