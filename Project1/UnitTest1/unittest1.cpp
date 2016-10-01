#include "stdafx.h"
#include "CppUnitTest.h"

#include "../Project1/Core.h"
#include "../Project1/IOLib.h"
#include "../Project1/Line.h"
#include "../Project1/Station.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(test1_lp)
		{
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({237,238,123,124,125,126,127});

			//ɳ��->��Ӫ
			vector<int> r = Core::LTPath(237,127);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test1_s) {
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 237,238,123,124,125,126,127 });

			//ɳ��->��Ӫ
			vector<int> r = Core::SPath(237, 127);
			Assert::IsTrue(bool(goal == r));

		}

		TEST_METHOD(test2_lp)
		{
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 237,238,123,239,185,184,183,151,182,23,49,48,83,147,8,104 });

			//ɳ��->������վ
			vector<int> r = Core::LTPath(237, 104);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test2_s) {
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 237,238,123,239,185,184,183,151,182,23,38,84,83,147,8,104 });

			//ɳ��->������վ
			vector<int> r = Core::SPath(237, 104);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test3_lp)
		{
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 183,151,182,23,50,51,52,53,12,35,54,55,56});

			//�����->������վ
			vector<int> r = Core::LTPath(183,56);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test3_s) {
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 183,151,182,23,38,37,11,36,35,54,55,56 });

			//�����->������վ
			vector<int> r = Core::SPath(183,56);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test4_lp)
		{
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 196,144,176,145,177,7,178,81,179,180,181,148,149,45 });

			//��->�����ׯ
			vector<int> r = Core::LTPath(196, 45);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test4_s) {
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 196,144,145,146,104,8,147,83,48,47,46,45 });

			//��->�����ׯ
			vector<int> r = Core::SPath(196,45);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test5_lp)
		{
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({71,72,73,74,75,76});

			//���������Ͽ�-����ˮ��
			vector<int> r = Core::LTPath(71,76);
			Assert::IsTrue(bool(goal == r));
		}

		TEST_METHOD(test5_s) {
			string path = "C:\\Users\\��\\Documents\\Visual Studio 2015\\Projects\\Project1\\UnitTest1\\beijing-subway.txt";
			IOLib::readData(path);
			vector<int> goal({ 71,156,189,188,76 });

			//���������Ͽ�-����ˮ��
			vector<int> r = Core::SPath(71,76);
			Assert::IsTrue(bool(goal == r));
		}
	};
}