#pragma once
#include "AIComponent.h"

class AIState
{
public:
	AIState(AIComponent* owner) :mOwner(owner) {}

	//״̬State��Ϊ
	virtual void Update(float deltaTime);
	virtual void OnEnter() = 0;				//����״̬
	virtual void OnExit() = 0;				//״̬�˳�
	//Getter״̬��
	virtual const char* GetName()const = 0;
protected:
	AIComponent* mOwner;
};

