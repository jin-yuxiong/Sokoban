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
	//�޸�ĳһ��λ�õ�ͼƬ
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