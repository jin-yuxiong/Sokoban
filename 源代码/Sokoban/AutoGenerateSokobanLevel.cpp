// AutoGenerateSokobanLevel.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "State.h"
#include "Map.h"
#include "Solver.h"
#include "GenerateLevel.h"
#include "time.h"
#include <windows.h>


/*
int main()
{
	// 以下注释掉的算法可以用来解一个推箱子谜题。

	TileType tilesample[49] = {
			Wall, Wall, Wall, Wall, Wall, Wall, Wall,
			Wall, Aid, Floor, Aid, Floor, Aid, Wall,
			Wall, Floor, Box, Box, Box, Floor, Wall,
			Wall, Aid, Box, Character, Box, Aid, Wall,
			Wall, Floor, Box, Box, Box, Floor, Wall,
			Wall, Aid, Floor, Aid, Floor, Aid, Wall,
			Wall, Wall, Wall, Wall, Wall, Wall, Wall,
	};
	TileType * tiles = new TileType[49];
	for (int i = 0; i < 49; i++) {
		tiles[i] = tilesample[i];
	}
	State * state = new State(7, 7);
	state->setLevel((TileType *)tiles);
	Map * map = new Map();
	Solver solver(state);
	map->drawMap(state);

	int res = solver.run();
	if (res == -1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "该关卡无解！！！\n";
	}
	else if (res == 1) {
		map->drawMap(state);
		int stepnum = solver.steplist.size();
		solver.drawStep();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		// std::wcout << L"该关卡有解\n";
		std::cout << "总共的迭代次数" << solver.iterNum << "\n";
		std::cout << "最短完成步数" << stepnum << "\n";
	}


	/*
	// 以下算法用来生成一个新的推箱子关卡
	GenerateLevel gl(7, 7);
	TileType * tiles = gl.tiles;

	State * state = new State(7,7);
	state->setLevel((TileType *)tiles);
	Map * map = new Map();
	Solver solver(state);
	map->drawMap(state);

	// 迭代生成关卡
	srand((unsigned)time(NULL) * 10);
	int gtime = 0;
	int trytime = 100;
	while (trytime --)
	{
		Sleep(50);
		gtime++;
		if (rand() % 2) {
			gl.generateBox();
			gl.generateAid();
		}
		else {
			gl.generateWall();
		}
		state->setLevel((TileType *)tiles);
		Solver solver(state);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		// std::wcout << L"迭代第" <<gtime << L"次生成的关卡\n";

		int res = solver.run();
		if (res == -1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			// std::wcout << L"该关卡无解！！！\n";
			gl.load();
		}
		else if (res == 1) {
			map->drawMap(state);
			trytime = 100;
			int stepnum = solver.steplist.size();
			// solver.drawStep();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
			gl.save();
			// std::wcout << L"该关卡有解\n";
			std::wcout << L"总共的迭代次数" << solver.iterNum << "\n";
			std::wcout << L"最短完成步数" << stepnum << "\n";
		}
	}
	solver.drawStep();
	getchar();

	*/


	// 以下注释掉的算法可以用来让玩家玩一局推箱子，需要给定一个关卡的初始state
	/*
	while (!state->ifWin()) {
		map->drawMap(state);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		std::wcout << L"请输入操作：w向上，s向下，a向左，d向右\n";
		char c=getchar();
		getchar();
		if (c == 'w') {
			state->up();
		}
		if (c == 's') {
			state->down();
		}
		if (c == 'a') {
			state->left();
		}
		if (c == 'd') {
			state->right();
		}
	}
	map->drawMap(state);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
	std::wcout << L"恭喜胜利！！！\n";
	*/
/*
delete state;
delete map;
}
*/

