#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

#include "IOLib.h"
#include "Core.h"
#include "Line.h"
#include "Station.h"

using namespace std;

//Require:
//	input the path of file containing subway information
//	the path should be correct
//Modified:
//	use Core.addStation to modified Core.stations and Core.lines
//	use Core.updateMatrix to modified Core.Matrix
//Effect:
//	read from file given by path
//	get the line information and station information
//	update the information in Core
void IOLib::readData(string path) {
	SLinkList p, end, head;
	string lineName;
	string station_str;
	string word;
	int stationIndex; // 车站编号
	queue<string> temp;
	ifstream fin;
		
	// 初始化邻接矩阵
	Core::initMatrix();

	//开始读文件,若文件不存在则报错退出
	fin.open(path);
	if (!fin.is_open()) {
		cout << "文件不存在" << endl;
		exit(1);
	}
	//读取一条线路的信息
	while ( getline(fin, lineName) ) {

		// 读入线路名和该线路上的所有站的站名和站号，以string的形式装入队列中
		getline(fin, station_str);
		head = end = NULL;
		stringstream ss(station_str);
		while (ss >> word) {
			temp.push(word);
		}

		// 将队列里的站名和站号取出来,更新Core.stations
		while (!temp.empty()) {

			word = temp.front();
			temp.pop();
			stationIndex = atoi(temp.front().c_str());
			temp.pop();
			Core::addStation(word, lineName, stationIndex);
				
			//初始化链表
			if (head == NULL) {
				head = new SNode;
				head->stationName = word;
				head->stationIndex = stationIndex;
				head->left = NULL;
				head->right = NULL;
				end = head;
			}
			else {
				p = new SNode;
				p->stationName = word;
				p->stationIndex = stationIndex;
				end->right = p;
				p->left = end;
				p->right = NULL;
				end = p;
			}
		}

		//处理环线
		if ( head->stationIndex == end->stationIndex ){
			end->left->right = head;
			head->left = end->left;
			free(end);
			end = head;
		}
		Core::updateLines(lineName, head, end);
	}
	fin.close();

	// 更新邻接矩阵
	Core::updateMatrix();

}


//Require:
//	input a list of id of stations illustrating a path
//	the stations should be nearby and the id should be legal
//Modified:
//	no
//Effect:
//	output the result of the path on the gui
//Exception:
//
void IOLib::GUIOutput(vector<int> r) {
		
}

//Require:
//	input a list of id of stations illustrating a path
//	the stations should be nearby and the id should be legal
//Modified:
//	no
//Effect:
//	output the result of the path on the command window
//Exception:
//
void IOLib::CommandOutput(vector<int> r) {
	cout << "共" << r.size() << "站" << endl;

	for ( unsigned int  i = 0; i < r.size(); ++i) {

		cout << Core::stations[r[i]].name;
		if (i > 0 && i < r.size() - 1 &&
			!Core::stations[r[i - 1]].isInSameLine(Core::stations[r[i + 1]]) ) {
			cout << "->换乘" 
					<< Core::stations[r[i]].getSameLineName(Core::stations[r[i + 1]])
					<< endl;
		}
		else {
			cout << endl;
		}
	}
}

