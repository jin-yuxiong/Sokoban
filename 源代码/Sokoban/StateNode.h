#pragma once
#include "State.h"
class StateNode {
public:
	State * currentstate = nullptr;
	StateNode * nextstate = nullptr;
	StateNode * parentstate = nullptr;
	//ɾ��������ȫ���ڵ�
	void deleteNode();
	//��ǰ��������ڵ��Ƿ����state
	bool ifContain(State * state);
	//������β������ڵ�
	StateNode * addState(State * state);
	int depth;
};