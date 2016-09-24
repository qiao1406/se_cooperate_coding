#pragma once
#include "Station.h"

// 从地图文件中读取站点的信息，建立站点的数组
extern "C" _declspec(dllimport) void __stdcall readMap(Station *stationArr );
// 获取当前一共的站点的数量
extern "C" _declspec(dllimport) int __stdcall getStationNum(Station *stationArr);

