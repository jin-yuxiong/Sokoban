#include <graphics.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include "pch.h"
#include "State.h"
#include "Map.h"

#include "GenerateLevel.h"
#include "time.h"
#include <windows.h>

using namespace std;








int main(void) {


	Map stage;
	stage.init();
	MOUSEMSG m;

	

	settextcolor(RGB(255, 255, 255));
	while (1) {
		char width = _getch();
		outtextxy(100, 50, width);
		char height = _getch();
		outtextxy(200, 50, height);

		// 以下算法用来生成一个新的推箱子关卡
		GenerateLevel gl(width - '0', height - '0');

		TileType* tiles = gl.tiles;

		State* state = new State(width - '0', height - '0');
		state->setLevel((TileType*)tiles);
		Solver solver(state);

		// 迭代生成关卡
		srand((unsigned)time(NULL) * 10);
		int gtime = 0;
		int trytime = 100;
		while (trytime--)
		{
			bool flag = false;
				while (1) {
					m = GetMouseMsg();
					if (m.mkLButton && m.x > 450 && m.x < 500 && m.y>50 && m.y < 60) {
						flag = true;
						break;
					}
					if (m.mkLButton && m.x > 250 && m.x < 300 && m.y>50 && m.y < 60) {
						Sleep(50);
						gtime++;
						if (rand() % 2) {
							gl.generateBox();
							gl.generateAid();
						}
						else {
                            gl.generateWall();
						}
						state->setLevel((TileType*)tiles);
						Solver solver(state);
						int res = solver.run();
						if (res == -1) {
							gl.load();
						}
						else if (res == 1) {
							trytime = 100;
							int stepnum = solver.steplist.size();
							Map map(state);
							map.drawMap();
							while (1) {
								m = GetMouseMsg();
								if (m.mkLButton && m.x > 350 && m.x < 400 && m.y>50 && m.y < 60) {
									map.showStepOneByOne(&solver);
									break;
								}
							}
							gl.save();
						}
						break;
					}
					
				}
				if (flag) {
					break;
			    }
		}




		


	}


	/*
	TileType tilesample[7 * 7] = {
	Wall, Wall, Wall, Wall, Wall, Wall, Wall,
	Wall, Aid, Floor, Aid, Floor, Aid, Wall,
	Wall, Floor, Box, Box, Box, Floor, Wall,
	Wall, Aid, Box, Character, Box, Aid, Wall,
	Wall, Floor, Box, Box, Box, Floor, Wall,
	Wall, Aid, Floor, Aid, Floor, Aid, Wall,
	Wall, Wall, Wall, Wall, Wall, Wall, Wall,
	};
	
	//求解
	TileType* tiles = new TileType[49];
	for (int i = 0; i < 49; i++) {
		tiles[i] = tilesample[i];
	}
	State* state = new State(7, 7);
	state->setLevel((TileType*)tiles);

	Map map(state);
	map.drawMap();

	Solver solver(state);

	int res = solver.run();
	if (res == -1) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		std::cout << "该关卡无解！！！\n";
	}
	else if (res == 1) {
		int stepnum = solver.steplist.size();
		map.showStepOneByOne(&solver);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		// std::wcout << L"该关卡有解\n";
		std::cout << "总共的迭代次数" << solver.iterNum << "\n";
		std::cout << "最短完成步数" << stepnum << "\n";
	}
	*/


	system("pause");
	return 0;
}


