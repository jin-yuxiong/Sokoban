#include "pch.h"
#include "Solver.h"
#include <iostream>
Solver::Solver(State* state)
{
	width = state->width;
	height = state->height;
	statenodes = new StateNode * [height * width];
	statenodesamount = new int[height * width];
	State* newstate = state->clone();
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			statenodes[i * width + j] = new StateNode();
			statenodesamount[i * width + j] = 0;
		}
	}
	newstate->charFloodFill();
	unexploidlist.push_back(addState(newstate));
}
Solver::~Solver() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			statenodes[i * width + j]->deleteNode();
			delete statenodes[i * width + j];
		}
	}
	delete statenodes;
	delete statenodesamount;
}

StateNode* Solver::addState(State* state) {
	int code = 0;
	// ��������Ϊ1����������Ϊ0
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (state->tiles[i * width + j] == Box || state->tiles[i * width + j] == BoxinAid) {
				code += i * width + j;
			}
		}
	}
	code = code % (height * width);
	statenodesamount[code]++;
	// std::wcout << code << "\n";
	return statenodes[code]->addState(state);
}
bool Solver::ifContain(State* state) {
	int code = 0;
	// ��������Ϊ1����������Ϊ0
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (state->tiles[i * width + j] == Box || state->tiles[i * width + j] == BoxinAid) {
				code += i * width + j;
			}
		}
	}
	code = code % (height * width);
	// std::wcout << code << "\n";
	if (statenodes[code]->ifContain(state)) {
		return true;
	}

	return false;
}

// �Զ����
int Solver::run() {
	iterNum = 0;
	while (true) {
		iterNum++;

		if (unexploidlist.size() == 0) {
			return -1;
		}
		StateNode* orisn = unexploidlist.front();
		int depth = orisn->depth;

		unexploidlist.pop_front();
		State* oristate = orisn->currentstate;

		// map.drawMap(oristate);

		State* tempstate = oristate->clone();
		// ���������ϵ�ÿһ��Box
		Direction alldirection[4] = { D_UP, D_DOWN, D_LEFT,  D_RIGHT };
		for (int i = 0; i < oristate->height; i++) {
			for (int j = 0; j < oristate->width; j++) {
				if (tempstate->tiles[i * oristate->width + j] == Box || tempstate->tiles[i * oristate->width + j] == BoxinAid) {
					for (int k = 0; k < 4; k++) {
						State* newstate = tempstate->boxPushed(i, j, alldirection[k]);
						if (newstate != nullptr) {
							newstate->charFloodFill();
							if (newstate->ifDead()) {
								delete newstate;
							}
							else if (ifContain(newstate)) {
								delete newstate;
							}
							else {
								StateNode* sn = addState(newstate);
								sn->depth = depth + 1;
								sn->parentstate = orisn;
								unexploidlist.push_back(sn);

								if (newstate->ifWin()) {
									StateNode* tempsn = sn;
									while (tempsn != nullptr) {
										steplist.push_front(tempsn);
										tempsn = tempsn->parentstate;
									}
									return 1;
								}
							}
						}
					}
				}
			}
		}
		delete tempstate;
	}
}

std::list <StateNode*> Solver::getSteplist() {
	return steplist;
}