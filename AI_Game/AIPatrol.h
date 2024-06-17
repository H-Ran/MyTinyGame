#pragma once
#include "AIState.h"
class AIPatrol :
    public AIState
{
	//状态State行为
	void Update(float deltaTime);
	void OnEnter();				//进入状态
	void OnExit();				//状态退出
	//Getter状态名
	virtual const char* GetName()const {
		return "Patrol";
	};
};

