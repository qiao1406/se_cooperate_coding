#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Core.h"
#include "Line.h"
#include "Station.h"

using namespace std;

class IO {
public:

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
	static void readData(string path) {
		SLinkList p, end, head;
		string lineName;
		string station_str;
		string word;
		int stationIndex; // ��վ���
		queue<string> temp;
		ifstream fin;
		
		// ��ʼ���ڽӾ���
		Core::initMatrix();

		//��ʼ���ļ�
		fin.open(path);
		//��ȡһ����·����Ϣ
		while ( getline(fin, lineName) ) {

			// ������·���͸���·�ϵ�����վ��վ����վ�ţ���string����ʽװ�������
			getline(fin, station_str);
			head = end = NULL;
			stringstream ss(station_str);
			while (ss >> word) {
				temp.push(word);
			}

			// ���������վ����վ��ȡ����,����Core.stations
			while (!temp.empty()) {

				word = temp.front();
				temp.pop();
				stationIndex = atoi(temp.front().c_str());
				temp.pop();
				Core::addStation(word, lineName, stationIndex);
				
				//��ʼ������
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

			//������
			if ( head->stationIndex == end->stationIndex ){
				end->left->right = head;
				head->left = end->left;
				free(end);
				end = head;
			}
			Core::updateLines(lineName, head, end);
		}
		fin.close();

		// �����ڽӾ���
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
	static void GUIOutput(vector<int> r) {
		
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
	static void CommandOutput(vector<int> r) {
		cout << "��" << r.size() << "վ" << endl;

		for ( unsigned int  i = 0; i < r.size(); ++i) {

			cout << Core::stations[r[i]].name;
			if (i > 0 && i < r.size() - 1 &&
				!Core::stations[r[i - 1]].isInSameLine(Core::stations[r[i + 1]]) ) {
				cout << "->����" 
					 << Core::stations[r[i]].getSameLineName(Core::stations[r[i + 1]])
					 << endl;
			}
			else {
				cout << endl;
			}
		}
	}

};