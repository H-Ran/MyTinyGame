#pragma once
#include "math.h"
#include"Actor.h"
#include"Component.h"

class MoveComponent :public Component
{
public:

	MoveComponent(class Actor* owner,int updateOrder = 100) :
		Component(owner, updateOrder) {}

	virtual void Update(float deltaTime) override;
	virtual void ProcessInput(const uint8_t* keyState) {}
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	// Controls rotation (radians/second)
	//绕原点旋转的速度
	float mAngularSpeed;
	// Controls forward movement (units/second)
	//朝前向向量前进速度
	float mForwardSpeed;
};