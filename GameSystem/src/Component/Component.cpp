 // ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <Component/Component.h>
#include <GameObject/GameObject.h>

Component::Component(GameObject* owner, int updateOrder)
	:mOwner(owner)
	,mUpdateOrder(updateOrder)
{
	// Add to GameObject's vector of components
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
