#include"pch.h"
#include "Map.h"
#include <iostream> 
using namespace std;



const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 768;
const int RATIO = 61;
const int START_X = 100;
const int START_Y = 150;

IMAGE images[All];

Map::Map() {

}

Map::Map(State* state) {
	//_setmode(_fileno(stdout), _O_U16TEXT);//Unicode特殊字符的输出
	mapstate = state->clone();
}

Map::~Map() {
}

//修改某一个位置的图片
void Map::changeMap(int x, int y, TileType tileType) {

	putimage(START_X + y * RATIO, START_Y + x * RATIO, &images[tileType]);

};




void Map::showStepOneByOne(Solver* solver) {

	//逐步绘制
	std::list <StateNode*> steplist = solver->getSteplist();

	while (steplist.size() > 0) {

		State * currentstate=steplist.front()->currentstate;
		for (int i = 0; i < currentstate->height; i++) {
			for (int j = 0; j < currentstate->width; j++) {
				if (*(currentstate->tiles + i * currentstate->width + j) == Character && !(currentstate->cx==j && currentstate->cy==i)) {
					*(currentstate->tiles + i * currentstate->width + j) = Floor;
				}

				if (*(currentstate->tiles + i * currentstate->width + j) == CharacterinAid && !(currentstate->cx == j && currentstate->cy == i)) {
					*(currentstate->tiles + i * currentstate->width + j) = Aid;
				}


			}
		}

		Sleep(1000);
		drawMap2(currentstate);

		steplist.pop_front();
		
		if (steplist.size() <= 0) {
			break;
		}
		State* nextstate = steplist.front()->currentstate;
		
		int boxi, boxj;
		for (int i = 0; i < currentstate->height; i++) {
			for (int j = 0; j < currentstate->width; j++) {
				if (*(nextstate->tiles + i * nextstate->width + j) == Box && *(currentstate->tiles + i * currentstate->width + j) != Box) {
					boxi = i;
					boxj = j;
				}
				else if (*(nextstate->tiles + i * nextstate->width + j) == BoxinAid && *(currentstate->tiles + i * currentstate->width + j) != BoxinAid) {
					boxi = i;
					boxj = j;
				}
			}
		}


		
		//直接移动
		if (nextstate->cy - boxi + nextstate->cy == currentstate->cy && nextstate->cx - boxj + nextstate->cx == currentstate->cx) {
			continue;
		}

		//A*寻路

		
		std::vector<std::vector<int>> map(currentstate->width);
		
		for (int i = 0; i < currentstate->height; i++) {
			
			for (int j = 0; j < currentstate->width; j++) {
				if (*(currentstate->tiles + i * currentstate->width + j) == Wall || *(currentstate->tiles + i * currentstate->width + j) == Box || *(currentstate->tiles + i * currentstate->width + j) == BoxinAid) {
					map[i].push_back(1);
				}
				else {
					map[i].push_back(0);
				}
			}
		}

		Astar astar;
		astar.InitAstar(map);

		//设置起始和结束点
		Point start(currentstate->cy, currentstate->cx);




		Point end(nextstate->cy-boxi+ nextstate->cy, nextstate->cx - boxj + nextstate->cx);

		// A*算法找寻路径
		std::list<Point*> path = astar.GetPath(start, end, false);
		
		Point* lastp=path.front();
		path.pop_front();
		for (auto& p : path) {
			Sleep(1000);
			if (*((mapstate->tiles) + (lastp->x) * (mapstate->width) + lastp->y) == Aid) {
				changeMap(lastp->x, lastp->y, Aid);
			}
			else
			{
				changeMap(lastp->x, lastp->y, Floor);
			}
			
			changeMap(p->x, p->y, Character);
			lastp = p;
		}
			
	}
}

void Map::init() {
	IMAGE bg_img;
	//搭台唱戏
	initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);
	loadimage(&bg_img, _T("blackground.bmp"), SCREEN_WIDTH,
		SCREEN_HEIGHT, true);
	putimage(0, 0, &bg_img);
	//加载道具图标
	loadimage(&images[Aid], _T("des.bmp"), RATIO, RATIO, true);
	loadimage(&images[Box], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[BoxinAid], _T("box.bmp"), RATIO, RATIO, true);
	loadimage(&images[Character], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[CharacterinAid], _T("man.bmp"), RATIO, RATIO, true);
	loadimage(&images[Wall], _T("wall.bmp"), RATIO, RATIO, true);
	loadimage(&images[Floor], _T("floor.bmp"), RATIO, RATIO, true);

	settextcolor(RGB(255, 255, 255));
	outtextxy(50, 50, "width");
	outtextxy(150, 50, "height");
	outtextxy(250, 50, "create");
	outtextxy(350, 50, "solve");
	outtextxy(450, 50, "restart");
}

void Map::drawMap() {
	
	for (int i = 0; i < mapstate->height; i++) {
		for (int j = 0; j < mapstate->width; j++) {
			putimage(START_X + j * RATIO, START_Y + i * RATIO, &images[mapstate->tiles[i * mapstate->width + j]]);
		}
	}
}
void Map::drawMap2(State * state) {

	for (int i = 0; i < state->height; i++) {
		for (int j = 0; j < state->width; j++) {
			putimage(START_X + j * RATIO, START_Y + i * RATIO, &images[state->tiles[i * state->width + j]]);
		}
	}
}

