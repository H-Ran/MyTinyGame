// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include <GameObject/GameObject.h>
#include <Component/Component.h>
#include <Math/math.h>
#include <algorithm>

GameObject::GameObject(Game* game)
	:mState(EActive)
	, mPosition{0,0}
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	mGame->AddGameObject(this);
}

GameObject::~GameObject()
{
	mGame->RemoveGameObject(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void GameObject::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateGameObject(deltaTime);
	}
}

void GameObject::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::UpdateGameObject(float deltaTime)
{
}

void GameObject::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		GameObjectInput(keyState);
	}
}

void GameObject::GameObjectInput(const uint8_t* keyState)
{
}

void GameObject::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void GameObject::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
