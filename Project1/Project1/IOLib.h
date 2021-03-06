#pragma once
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

class IOLib {
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
	static void readData(string path);

	//	output the result of the path on the gui
	static void GUIOutput(vector<int> r);

	//	output the result of the path on the command window
	static void CommandOutput(vector<int> r);
		

};