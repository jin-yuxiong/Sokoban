#pragma once
#include "State.h"
class StateNode {
public:
	State * currentstate = nullptr;
	StateNode * nextstate = nullptr;
	StateNode * parentstate = nullptr;
	//删除后续的全部节点
	void deleteNode();
	//当前及其后续节点是否等于state
	bool ifContain(State * state);
	//在链的尾部加入节点
	StateNode * addState(State * state);
	int depth;
};