#include <cstdlib>
#include <fstream>
#include <sstream>
#include <queue>
#include "Core.h"

#define STATION_NUM 300

void readMap(Station *stationArr) {

	string lineName;
	string station_str;
	string word;
	int stationIndex; // 车站编号
	queue<string> temp;
	ifstream fin;
	int last_index; //上一个车站在数组里的下标值

	fin.open("beijing-subway.txt");

	//读取一条线路的信息
	while (getline(fin, lineName)) {

		// 读入线路名和该线路上的所有站的站名和站号，以string的形式装入队列中
		getline(fin, station_str);
		stringstream ss(station_str);
		while (ss >> word) {
			temp.push(word);
		}

		// 将队列里的站名和站号取出来，构建数组
		while (!temp.empty()) {
			word = temp.front();
			temp.pop();
			stationIndex = atoi(temp.front().c_str());
			temp.pop();

			// 将站点存入数组中
			if (!stationArr[stationIndex].isEmpty()) { // 已存在的站点
				stationArr[stationIndex].addLine(lineName); // 把线路加进去
			}
			else { // 未加入的站点

				stationArr[stationIndex] = Station(word, lineName);
				//st_map.insert(pair<string, int>(word, st_num));

			}

		}

		fin.close();

	}
}

int getStationNum(Station * stationArr) {

	for (int i = 0; i < STATION_NUM; ++i) {
		if (stationArr[i].name == "") {
			return i;
		}
	}

	return 0;
}
