// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <Component/MoveBehavior/InputBehavior/InputBehaviorComponent.h>
#include <GameObject/GameObject.h>

InputComponent::InputComponent(class GameObject* owner)
:MoveComponent(owner)
,mForwardKey(0)
,mBackKey(0)
,mClockwiseKey(0)
,mCounterClockwiseKey(0)
{
	
}

void InputComponent::ProcessInput(const uint8_t* keyState)
{
	// Calculate forward speed for MoveComponent
	float forwardSpeed = 0.0f;
	if (keyState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyState[mBackKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[mClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyState[mCounterClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
