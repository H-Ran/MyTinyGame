#pragma once
#include <Math/math.h>
#include<GameObject/GameObject.h>
#include<Component/Component.h>

class MoveComponent :public Component
{
public:

	MoveComponent(class GameObject* owner,int updateOrder = 100) :
		Component(owner, updateOrder) {}

	virtual void Update(float deltaTime) override;
	virtual void ProcessInput(const uint8_t* keyState) {}
	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
private:
	// Controls rotation (radians/second)
	float mAngularSpeed;
	// Controls forward movement (units/second)
	float mForwardSpeed;
};