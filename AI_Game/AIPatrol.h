#pragma once
#include "AIState.h"
class AIPatrol :
    public AIState
{
	//״̬State��Ϊ
	void Update(float deltaTime);
	void OnEnter();				//����״̬
	void OnExit();				//״̬�˳�
	//Getter״̬��
	virtual const char* GetName()const {
		return "Patrol";
	};
};

