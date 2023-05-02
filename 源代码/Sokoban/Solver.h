#pragma once
#include "State.h"
#include "StateNode.h"
#include <list>
class Solver {
public:
	Solver(State* state);
	~Solver();
	int run();
	bool ifContain(State* state);
	StateNode* addState(State* state);
	int width;
	int height;
	StateNode** statenodes;
	int* statenodesamount;
	std::list <StateNode*> unexploidlist;
	std::list <StateNode*> steplist;
	// �ܵĵ�������
	int iterNum;
	std::list <StateNode*> getSteplist();


};