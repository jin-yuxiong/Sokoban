#pragma once
#include "TileType.h"
#include "State.h"
#include "windows.h"
#include <io.h>
#include <fcntl.h>
#include "Solver.h"
#include "Astar.h"

#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string>




class Map {
public:
	Map();
	Map(State* state);
	~Map();
	void drawMap();
	//修改某一个位置的图片
	void changeMap(int x, int y, TileType tileType);
	void showStepOneByOne(Solver* solver);
	void drawMap2(State* state);
	void init();
private:
	int width;
	int height;
	int** MapArray;
	State* mapstate;

};