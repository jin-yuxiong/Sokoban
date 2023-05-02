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
	// 总的迭代次数
	int iterNum;
	std::list <StateNode*> getSteplist();


};