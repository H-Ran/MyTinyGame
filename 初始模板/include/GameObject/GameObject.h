// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include <GameMain/Game.h>
#include<GameObject/ActorState.h>	
#include <Math/math.h>
#include <vector>
#include <cstdint>

class GameObject
{
private:
	// GameObject's state
	ActorState mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;

	std::vector<class Component*> mComponents;
	class Game* mGame;
public:

	GameObject(class Game* game);
	virtual ~GameObject();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the GameObject (not overridable)
	void UpdateComponents(float deltaTime);
	// Any GameObject-specific update code (overridable)
	virtual void UpdateGameObject(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any GameObject-specific input code (overridable)
	virtual void GameObjectInput(const uint8_t* keyState);

	// Getters/Setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	//Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	ActorState GetState() const { return mState; }
	void SetState(ActorState state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

};
