#pragma once
#include "AIComponent.h"

class AIState
{
public:
	AIState(AIComponent* owner) :mOwner(owner) {}

	//状态State行为
	virtual void Update(float deltaTime);
	virtual void OnEnter() = 0;				//进入状态
	virtual void OnExit() = 0;				//状态退出
	//Getter状态名
	virtual const char* GetName()const = 0;
protected:
	AIComponent* mOwner;
};

